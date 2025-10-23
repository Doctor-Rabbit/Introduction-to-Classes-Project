#include "Date.h"
#include <array>
#include <sstream>

namespace {
    constexpr int DEFAULT_M = 1;
    constexpr int DEFAULT_D = 1;
    constexpr int DEFAULT_Y = 1900;

    // Month names 1..12; index 0 unused for convenience
    const std::array<const char*, 13> MONTHS = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
}

Date::Date(int m, int d, int y) : month(DEFAULT_M), day(DEFAULT_D), year(DEFAULT_Y) {
    setDate(m, d, y); // centralize validation
}

void Date::setDate(int m, int d, int y) {
    if (isValidDate(m, d, y)) {
        month = m;
        day = d;
        year = y;
    }
    else {
        month = DEFAULT_M;
        day = DEFAULT_D;
        year = DEFAULT_Y;
    }
}

bool Date::isLeapYear() const {
    return isLeapYear(year);
}

bool Date::isLeapYear(int y) const {
    // Leap year if divisible by 400, or divisible by 4 but not by 100.
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return (y % 4 == 0);
}

int Date::lastDay() const {
    return lastDay(month, year);
}

int Date::lastDay(int m, int y) const {
    if (!isValidMonth(m) || !isValidYear(y)) return 31; // safe fallback

    switch (m) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return isLeapYear(y) ? 29 : 28;
    default:
        return 31; // unreachable with isValidMonth guard
    }
}

std::string Date::formatNumeric() const {
    std::ostringstream out;
    out << month << '/' << day << '/' << year;
    return out.str();
}

std::string Date::formatMonthDayYear() const {
    std::ostringstream out;
    out << MONTHS[month] << ' ' << day << ", " << year;
    return out.str();
}

std::string Date::formatDayMonthYear() const {
    std::ostringstream out;
    out << day << ' ' << MONTHS[month] << ' ' << year;
    return out.str();
}

bool Date::isValidMonth(int m) const {
    return (m >= 1 && m <= 12);
}

bool Date::isValidYear(int y) const {
    return (y > 0);
}

bool Date::isValidDate(int m, int d, int y) const {
    if (!isValidMonth(m) || !isValidYear(y)) return false;
    if (d < 1) return false;
    int ld = lastDay(m, y);
    return d <= ld;
}
