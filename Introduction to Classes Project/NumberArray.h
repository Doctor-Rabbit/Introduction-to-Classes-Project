#ifndef NUMBERARRAY_H
#define NUMBERARRAY_H

#include <cstddef>
#include <iosfwd>

class NumberArray {
public:
    // Default size & default return value for getNumber on error
    static const int MAX_SIZE = 10;         // default array size
    static const double DEFAULT_RETVAL;     // declare only

    // Constructor / Destructor
    explicit NumberArray(int size = MAX_SIZE);
    ~NumberArray();

    // Non-copyable (to avoid double-free in this simple example)
    NumberArray(const NumberArray&) = delete;
    NumberArray& operator=(const NumberArray&) = delete;

    // Basic ops
    void   setNumber(int index, double value); // mutator with bounds check
    double getNumber(int index) const;         // accessor with bounds check & default

    // Stats (computed on demand)
    double min() const;
    double max() const;
    double average() const;

    // Utility
    void   print(std::ostream& os) const;      // prints all elements space-separated
    int    size() const { return size_; }      // simple inline accessor

private:
    int    size_{ 0 };    // positive integer size
    double* data_{ nullptr }; // dynamic array of doubles initialized to 0.0

    bool inBounds(int index) const { return index >= 0 && index < size_; }
};

#endif // NUMBERARRAY_H
