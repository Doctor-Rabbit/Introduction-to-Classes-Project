#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
public:
    // Constructors
    Date(int m = 1, int d = 1, int y = 1900);  // validates via setDate

    // Mutator
    void setDate(int m, int d, int y);         // invalid -> 1/1/1900

    // Accessors (kept simple & inline)
    int getMonth() const { return month; }
    int getDay()   const { return day; }
    int getYear()  const { return year; }

    // Leap year checks
    bool isLeapYear() const;
    bool isLeapYear(int y) const;

    // Last day of month
    int lastDay() const;                // uses current month/year
    int lastDay(int m, int y) const;    // uses provided month/year

    // Formatting
    std::string formatNumeric() const;         // "12/25/2021"
    std::string formatMonthDayYear() const;    // "December 25, 2021"
    std::string formatDayMonthYear() const;    // "25 December 2021"

private:
    int month;
    int day;
    int year;

    bool isValidMonth(int m) const;
    bool isValidYear(int y) const;
    bool isValidDate(int m, int d, int y) const;
};



#endif // DATE_H