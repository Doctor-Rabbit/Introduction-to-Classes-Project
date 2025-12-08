#include <iostream>
#include <iomanip>
#include <random>
#include "NumberArray.hpp"

int main() {
    using std::cout;
    using std::fixed;
    using std::setprecision;

    std::mt19937 rng(12345);
    std::uniform_int_distribution<int>    idist(0, 100);
    std::uniform_real_distribution<double> ddist(0.0, 100.0);

    cout << "----- Test constructors -----\n";

    NumberArray<int>    ai_default; // size 10
    NumberArray<double> ad_default; // size 10

    cout << "From default constructor: Integer array of size " << ai_default.size() << "\n";
    ai_default.print(cout);

    cout << "From default constructor: Double array of size " << ad_default.size() << "\n";
    cout << fixed << setprecision(1);
    ad_default.print(cout);

    NumberArray<int>    ai_param(15);
    NumberArray<double> ad_param(15);

    cout << "From constructor with parameters: Integer array of size " << ai_param.size() << "\n";
    cout.unsetf(std::ios::floatfield); // back to ints
    ai_param.print(cout);

    cout << fixed << setprecision(1);
    cout << "From constructor with parameters: Double array of size " << ad_param.size() << "\n";
    ad_param.print(cout);

    cout << "----- Test mutator -----\n";
    // Fill arrays
    for (std::size_t i = 0; i < ai_param.size(); ++i) {
        ai_param.setNumber(i, idist(rng));
    }
    for (std::size_t i = 0; i < ad_param.size(); ++i) {
        ad_param.setNumber(i, std::round(ddist(rng) * 10.0) / 10.0); // one decimal
    }

    cout.unsetf(std::ios::floatfield);
    cout << "Integer array filled with numbers:\n";
    ai_param.print(cout);

    cout << fixed << setprecision(1);
    cout << "Double array filled with numbers:\n";
    ad_param.print(cout);

    cout << "Trying to set a number with an out of bounds index (20):\n";
    cout << "Integer array ...\n";
    try {
        ai_param.setNumber(20, 123);
    }
    catch (const std::out_of_range& e) {
        cout << e.what() << '\n';
    }
    cout << "Double array ...\n";
    try {
        ad_param.setNumber(20, 1.23);
    }
    catch (const std::out_of_range& e) {
        cout << e.what() << '\n';
    }

    cout << "----- Test accessors _____\n";
    cout.unsetf(std::ios::floatfield);
    cout << "Access integer item at index 5: ";
    try {
        cout << ai_param.getNumber(5) << '\n';
    }
    catch (const std::out_of_range& e) {
        cout << e.what() << '\n';
    }

    cout << fixed << setprecision(1);
    cout << "Access double item at index 5: ";
    try {
        cout << ad_param.getNumber(5) << '\n';
    }
    catch (const std::out_of_range& e) {
        cout << e.what() << '\n';
    }

    cout << "Trying to access a number with an out of bounds index (20):\n";
    cout << "Integer array ...\n";
    try {
        (void)ai_param.getNumber(20);
    }
    catch (const std::out_of_range& e) {
        cout << e.what() << '\n';
    }
    cout << "Double array ...\n";
    try {
        (void)ad_param.getNumber(20);
    }
    catch (const std::out_of_range& e) {
        cout << e.what() << '\n';
    }

    cout.unsetf(std::ios::floatfield);
    cout << "The minimum value in the integer array is: " << ai_param.min() << '\n';
    cout << "The maximum value in the integer array is: " << ai_param.max() << '\n';
    cout << fixed << setprecision(1);
    cout << "The average of the values in the integer array is: " << ai_param.average() << '\n';

    cout << "The minimum value in the double array is: " << ad_param.min() << '\n';
    cout << "The maximum value in the double array is: " << ad_param.max() << '\n';
    cout << "The average of the values in the double array is: " << ad_param.average() << '\n';

    cout.unsetf(std::ios::floatfield);
    cout << "----- Print arrays -----\n";
    cout << "Integer array:\n";
    ai_param.print(cout);

    cout << fixed << setprecision(1);
    cout << "Double array:\n";
    ad_param.print(cout);

    cout.unsetf(std::ios::floatfield);
    cout << "----- Test destructor -----\n";
    cout << "Exiting program, destructor will be called to free memory.\n";
    return 0; // destructors will print messages
}
