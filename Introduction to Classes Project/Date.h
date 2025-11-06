#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>
#include <cstdint>

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

    // Operators
    Date& operator++(); // ++d  -> increment day, handle month/year rollover
    Date& operator--(); // --d  -> decrement day, handle month/year borrow

    Date operator++(int); // d++
    Date operator--(int); // d--

    long long operator - (const Date& rhs) const;     // Subtraction: absolute day difference between *this and rhs

private:
    int month;
    int day;
    int year;

    bool isValidMonth(int m) const;
    bool isValidYear(int y) const;
    bool isValidDate(int m, int d, int y) const;

    // Helpers for ++ / --
    void incrementOneDay();
    void decrementOneDay();

    // Serial day number (proleptic Gregorian) for differences
    long long serialDays() const;

    // Static helper for serial algorithm
    static long long daysFromCivil(int y, int m, int d);
};

// Stream operators
std::ostream & operator<<(std::ostream & os, const Date & d); // "April 18, 2018"
std::istream& operator>>(std::istream& is, Date& d);       // prompts & reads

#endif // DATE_H