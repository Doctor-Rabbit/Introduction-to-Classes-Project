#include "Date.h"
#include <array>
#include <sstream>
#include <cstdlib>
#include <cmath>

namespace {
    constexpr int DEFAULT_M = 1;
    constexpr int DEFAULT_D = 1;
    constexpr int DEFAULT_Y = 1900;

    const std::array<const char*, 13> MONTHS = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
}

Date::Date(int m, int d, int y) : month(DEFAULT_M), day(DEFAULT_D), year(DEFAULT_Y) {
    setDate(m, d, y);
}

void Date::setDate(int m, int d, int y) {
    if (isValidDate(m, d, y)) {
        month = m; day = d; year = y;
    }
    else {
        month = DEFAULT_M; day = DEFAULT_D; year = DEFAULT_Y;
    }
}

bool Date::isLeapYear() const { return isLeapYear(year); }

bool Date::isLeapYear(int y) const {
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return (y % 4 == 0);
}

int Date::lastDay() const { return lastDay(month, year); }

int Date::lastDay(int m, int y) const {
    switch (m) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
    case 4: case 6: case 9: case 11: return 30;
    case 2: return isLeapYear(y) ? 29 : 28;
    default: return 31; // guarded by validation
    }
}

std::string Date::formatNumeric() const {
    std::ostringstream out; out << month << '/' << day << '/' << year; return out.str();
}
std::string Date::formatMonthDayYear() const {
    std::ostringstream out; out << MONTHS[month] << ' ' << day << ", " << year; return out.str();
}
std::string Date::formatDayMonthYear() const {
    std::ostringstream out; out << day << ' ' << MONTHS[month] << ' ' << year; return out.str();
}

bool Date::isValidMonth(int m) const { return (m >= 1 && m <= 12); }
bool Date::isValidYear(int y) const { return (y > 0); }

bool Date::isValidDate(int m, int d, int y) const {
    if (!isValidMonth(m) || !isValidYear(y) || d < 1) return false;
    return d <= lastDay(m, y);
}

// ---------- NEW: ++ / -- and subtraction ----------

void Date::incrementOneDay() {
    if (day < lastDay(month, year)) {
        ++day;
    }
    else {
        day = 1;
        if (month < 12) {
            ++month;
        }
        else {
            month = 1;
            ++year; // next year
        }
    }
}

void Date::decrementOneDay() {
    if (day > 1) {
        --day;
    }
    else {
        if (month > 1) {
            --month;
        }
        else {
            month = 12;
            --year; // previous year (assumes year remains positive in tests)
        }
        day = lastDay(month, year);
    }
}

// prefix ++
Date& Date::operator++() { incrementOneDay(); return *this; }
// postfix ++
Date Date::operator++(int) { Date temp(*this); incrementOneDay(); return temp; }

// prefix --
Date& Date::operator--() { decrementOneDay(); return *this; }
// postfix --
Date Date::operator--(int) { Date temp(*this); decrementOneDay(); return temp; }

// Serial day number from proleptic Gregorian calendar (Howard Hinnant’s algo)
long long Date::daysFromCivil(int y, int m, int d) {
    y -= m <= 2;
    const int era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400);      // [0, 399]
    const unsigned doy = (153u * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; // [0, 365]
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;     // [0, 146096]
    return static_cast<long long>(era) * 146097LL + static_cast<long long>(doe);
}

long long Date::serialDays() const {
    return daysFromCivil(year, month, day);
}

// Absolute day difference
long long Date::operator-(const Date& rhs) const {
    long long a = serialDays();
    long long b = rhs.serialDays();
    long long diff = a - b;
    return diff < 0 ? -diff : diff; // absolute number of days
}

// ---------- Streams ----------

std::ostream& operator<<(std::ostream& os, const Date& d) {
    os << d.formatMonthDayYear(); // e.g., "April 18, 2018"
    return os;
}

std::istream& operator>>(std::istream& is, Date& d) {
    // Prompt only when reading from std::cin (per assignment)
    if (&is == &std::cin) {
        std::cout << "Enter date as MM DD YYYY: ";
    }
    int m, dd, y;
    if (is >> m >> dd >> y) {
        d.setDate(m, dd, y); // setDate enforces validation (defaults on error)
    }
    else {
        // stream error: clear and leave d unchanged
        is.clear(is.rdstate());
    }
    return is;
}

