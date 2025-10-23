#include "NumberArray.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdexcept>

const double NumberArray::DEFAULT_RETVAL = 0.0;  // definition

NumberArray::NumberArray(int size) {
    // Validate size; if invalid, fall back to default
    if (size <= 0) {
        std::cerr << "[NumberArray] Invalid size " << size
            << " — using default " << MAX_SIZE << ".\n";
        size_ = MAX_SIZE;
    }
    else {
        size_ = size;
    }

    data_ = new double[size_];
    std::fill(data_, data_ + size_, 0.0);
}

NumberArray::~NumberArray() {
    delete[] data_;
    std::cerr << "[NumberArray] Destructor called for array of size "
        << size_ << ".\n";
}

void NumberArray::setNumber(int index, double value) {
    if (!inBounds(index)) {
        std::cerr << "[setNumber] Index " << index
            << " out of bounds [0," << (size_ - 1) << "]. Value not stored.\n";
        return;
    }
    data_[index] = value;
}

double NumberArray::getNumber(int index) const {
    if (!inBounds(index)) {
        std::cerr << "[getNumber] Index " << index
            << " out of bounds [0," << (size_ - 1) << "]. Returning default "
            << DEFAULT_RETVAL << ".\n";
        return DEFAULT_RETVAL;
    }
    return data_[index];
}

double NumberArray::min() const {
    if (size_ == 0) return 0.0; // defensive (shouldn’t happen with our ctor)
    return *std::min_element(data_, data_ + size_);
}

double NumberArray::max() const {
    if (size_ == 0) return 0.0;
    return *std::max_element(data_, data_ + size_);
}

double NumberArray::average() const {
    if (size_ == 0) return 0.0;
    double sum = std::accumulate(data_, data_ + size_, 0.0);
    return sum / static_cast<double>(size_);
}

void NumberArray::print(std::ostream& os) const {
    for (int i = 0; i < size_; ++i) {
        if (i) os << ' ';
        os << data_[i];
    }
}