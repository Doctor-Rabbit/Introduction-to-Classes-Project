#include <iostream>
#include "Date.h"

int main() {
    std::cout << "---- Test Plan Start ----\n";

    // 1) Default constructor, first format
    Date A;
    std::cout << "1) Default ctor (numeric): " << A.formatNumeric() << "\n";

    // 2) Ctor with params, second format
    Date B(2, 28, 2009);
    std::cout << "2) Param ctor (Month Day, Year): " << B.formatMonthDayYear() << "\n";

    // 3) setDate + third format
    A.setDate(3, 15, 2012);
    std::cout << "3) setDate(3,15,2012) (Day Month Year): " << A.formatDayMonthYear() << "\n";

    // 4) setDate(13,45,2018) rejected -> default
    A.setDate(13, 45, 2018);
    std::cout << "4) setDate(13,45,2018) invalid -> " << A.formatNumeric() << " (expect 1/1/1900)\n";

    // 5) setDate(4,31,2000) rejected -> default
    A.setDate(4, 31, 2000);
    std::cout << "5) setDate(4,31,2000) invalid -> " << A.formatNumeric() << " (expect 1/1/1900)\n";

    // 6) setDate(2,29,2009) rejected -> default (2009 not leap)
    A.setDate(2, 29, 2009);
    std::cout << "6) setDate(2,29,2009) invalid -> " << A.formatNumeric() << " (expect 1/1/1900)\n";

    // 7) 4/10/2014 and 4/18/2014 difference = 8
    Date D1(4, 10, 2014), D2(4, 18, 2014);
    std::cout << "7) |" << D2 << " - " << D1 << "| = " << (D2 - D1) << " days (expect 8)\n";

    // 8) 2/2/2006 and 11/10/2003 difference = 815
    Date E1(2, 2, 2006), E2(11, 10, 2003);
    std::cout << "8) |" << E1 << " - " << E2 << "| = " << (E1 - E2) << " days (expect 815)\n";

    // 9) set 2/29/2008; pre-increment -> 3/1/2008; then pre-decrement -> back to 2/29/2008
    Date F(2, 29, 2008);
    std::cout << "9) Start: " << F.formatNumeric() << "\n";
    std::cout << "   ++F -> ";
    ++F;
    std::cout << F.formatNumeric() << " (expect 3/1/2008)\n";
    std::cout << "   --F -> ";
    --F;
    std::cout << F.formatNumeric() << " (expect 2/29/2008)\n";

    // 10) repeat with post-decrement and post-increment
    std::cout << "10) Post ops starting from 2/29/2008:\n";
    F.setDate(2, 29, 2008);
    std::cout << "    F++ returns " << (F++).formatNumeric() << ", F now " << F.formatNumeric()
        << " (expect returned 2/29/2008, now 3/1/2008)\n";
    std::cout << "    F-- returns " << (F--).formatNumeric() << ", F now " << F.formatNumeric()
        << " (expect returned 3/1/2008, now 2/29/2008)\n";

    // 11) 12/31/2024 post-increment -> 1/1/2025; then post-decrement back
    Date G(12, 31, 2024);
    std::cout << "11) Start: " << G.formatNumeric() << "\n";
    std::cout << "    G++ returns " << (G++).formatNumeric() << ", G now " << G.formatNumeric()
        << " (expect now 1/1/2025)\n";
    std::cout << "    G-- returns " << (G--).formatNumeric() << ", G now " << G.formatNumeric()
        << " (expect now 12/31/2024)\n";

    // 12) Repeat with pre-increment and pre-decrement
    G.setDate(12, 31, 2024);
    std::cout << "12) Pre ops from 12/31/2024:\n";
    std::cout << "    ++G -> " << (++G).formatNumeric() << " (expect 1/1/2025)\n";
    std::cout << "    --G -> " << (--G).formatNumeric() << " (expect 12/31/2024)\n";

    // 13) Use >> to read a date
    Date H;
    std::cout << "13) Input a date:\n";
    std::cin >> H;

    // 14) Use << to display it
    std::cout << "14) You entered: " << H << "\n";

    std::cout << "---- Test Plan End ----\n";
    return 0;
}
