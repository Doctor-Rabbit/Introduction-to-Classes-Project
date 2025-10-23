#include <iostream>
#include <iomanip>
#include <random>
#include "NumberArray.h"

int main() {
    using std::cout;
    using std::fixed;
    using std::setprecision;

    cout << fixed << setprecision(1);

    // ---- Test default constructor (size = MAX_SIZE = 10) ----
    cout << "Test default constructor (size = " << NumberArray::MAX_SIZE << "):\n";
    NumberArray A; // default size (10)

    // Fill with random numbers in [-10.0, 10.0]
    std::mt19937 rng(12345); // deterministic seed for repeatable results
    std::uniform_real_distribution<double> dist(-10.0, 10.0);

    for (int i = 0; i < A.size(); ++i) {
        A.setNumber(i, dist(rng));
    }

    cout << "A contents: ";
    A.print(cout);
    cout << "\nmin(A) = " << A.min()
        << ", max(A) = " << A.max()
        << ", avg(A) = " << A.average() << "\n\n";

    // ---- Test parameterized constructor (size = 15; <= 20 as requested) ----
    cout << "Test parameterized constructor (size = 15):\n";
    NumberArray B(15);

    for (int i = 0; i < B.size(); ++i) {
        B.setNumber(i, dist(rng));
    }

    cout << "B contents: ";
    B.print(cout);
    cout << "\nmin(B) = " << B.min()
        << ", max(B) = " << B.max()
        << ", avg(B) = " << B.average() << "\n\n";

    // ---- Out-of-bounds tests ----
    cout << "Out-of-bounds tests on A:\n";
    A.setNumber(-1, 3.3);              // invalid: low
    A.setNumber(A.size(), 7.7);        // invalid: high
    double v1 = A.getNumber(-2);       // invalid: low (returns default)
    double v2 = A.getNumber(A.size()); // invalid: high (returns default)
    cout << "A.getNumber(-2) = " << v1
        << ", A.getNumber(size) = " << v2 << "\n\n";

    // ---- Show that zeros were the initial values (construct a small array and don't set it) ----
    cout << "Fresh array C (size = 5), should be all zeros:\n";
    NumberArray C(5);
    cout << "C contents: ";
    C.print(cout);
    cout << "\nmin(C) = " << C.min()
        << ", max(C) = " << C.max()
        << ", avg(C) = " << C.average() << "\n\n";

    cout << "Done. Destructors will announce themselves below.\n";
    return 0;
}
