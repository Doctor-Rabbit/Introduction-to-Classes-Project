#include <iostream>
#include "Date.h"

int main() {
    // Test default constructor
    Date dDefault;
    std::cout << "Test default constructor: " << dDefault.formatNumeric() << '\n';

    // Test constructor with valid date
    Date dValid(2, 28, 2009);
    std::cout << "Test constructor with valid date: " << dValid.formatNumeric() << '\n';

    // Test constructor with invalid month => should become default
    Date dBadMonth(45, 2, 2009);
    std::cout << "Test constructor with invalid month (45, 2, 2009): Month invalid "
        << dBadMonth.formatNumeric() << '\n';

    // Test constructor with invalid day (non-leap year Feb 29) => default
    Date dBadDay(2, 29, 2009);
    std::cout << "Test constructor with invalid day (2/29/2009): Day invalid "
        << dBadDay.formatNumeric() << '\n';

    // Test setDate with bad month => default
    Date d1; // start from default
    d1.setDate(13, 1, 1900);
    std::cout << "Test setDate with bad month (13): Month invalid "
        << d1.formatNumeric() << '\n';

    // Test setDate with bad day (April has 30)
    Date d2;
    d2.setDate(4, 31, 2009);
    std::cout << "Test setDate with bad day (4, 31, 2009) Day invalid "
        << d2.formatNumeric() << '\n';

    // Test for leap year with bad date (2/29/2009) -> constructor makes it default
    Date dBadLeap(2, 29, 2009);
    std::cout << "Test for leap year with bad date (2/29/2009): Day invalid "
        << dBadLeap.formatNumeric() << '\n';

    // Test for leap year with good date (2/29/2008) -> valid
    Date dGoodLeap(2, 29, 2008);
    std::cout << "Test for leap year with good date (2/29/2008): "
        << dGoodLeap.formatNumeric() << '\n';

    // Test the print formats
    std::cout << "Test the print formats:\n";
    std::cout << dGoodLeap.formatMonthDayYear() << '\n'; // "February 29, 2008"
    std::cout << dGoodLeap.formatDayMonthYear() << '\n'; // "29 February 2008"

    // A couple of extra spot checks (optional):
    Date end31(1, 31, 2021); // Jan 31 ok
    std::cout << "Jan last day check: " << end31.formatNumeric()
        << " (lastDay=" << end31.lastDay() << ")\n";

    Date febNonLeap(2, 28, 2021);
    std::cout << "Non-leap Feb: " << febNonLeap.formatNumeric()
        << " (isLeap=" << (febNonLeap.isLeapYear() ? "true" : "false")
        << ", lastDay=" << febNonLeap.lastDay() << ")\n";

    Date febLeap(2, 29, 2020);
    std::cout << "Leap Feb: " << febLeap.formatNumeric()
        << " (isLeap=" << (febLeap.isLeapYear() ? "true" : "false")
        << ", lastDay=" << febLeap.lastDay() << ")\n";

    return 0;
}
