#ifndef NUMBERARRAY_TPP
#define NUMBERARRAY_TPP

#include <cstddef>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <stdexcept>
#include <type_traits>

template <typename T>
class NumberArray {
public:
    static const std::size_t MAX_SIZE = 10; // default size

    explicit NumberArray(std::size_t size = MAX_SIZE)
        : size_(size ? size : MAX_SIZE), data_(new T[size_]{}) {
        // zero-initialized via brace-init
    }

    // Rule of Five (simple, safe)
    ~NumberArray() {
        delete[] data_;
        std::cerr << "The destructor is running\n";
    }
    NumberArray(const NumberArray& other) : size_(other.size_), data_(new T[size_]) {
        std::copy(other.data_, other.data_ + size_, data_);
    }
    NumberArray& operator=(const NumberArray& other) {
        if (this != &other) {
            NumberArray tmp(other);
            swap(tmp);
        }
        return *this;
    }
    NumberArray(NumberArray&& other) noexcept : size_(other.size_), data_(other.data_) {
        other.size_ = 0; other.data_ = nullptr;
    }
    NumberArray& operator=(NumberArray&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            data_ = other.data_;
            other.size_ = 0; other.data_ = nullptr;
        }
        return *this;
    }

    // Mutator / Accessors with bounds checking (throw out_of_range)
    void setNumber(std::size_t index, const T& value) {
        checkBounds(index);
        data_[index] = value;
    }

    T getNumber(std::size_t index) const {
        checkBounds(index);
        return data_[index];
    }

    // Stats (require arithmetic T)
    T min() const {
        static_assert(std::is_arithmetic<T>::value, "min() requires arithmetic type");
        return *std::min_element(data_, data_ + size_);
    }
    T max() const {
        static_assert(std::is_arithmetic<T>::value, "max() requires arithmetic type");
        return *std::max_element(data_, data_ + size_);
    }
    // Return as double to avoid overflow / preserve precision across int/double
    double average() const {
        static_assert(std::is_arithmetic<T>::value, "average() requires arithmetic type");
        long double sum = std::accumulate(data_, data_ + size_, static_cast<long double>(0));
        return static_cast<double>(sum / static_cast<long double>(size_));
    }

    // Utility
    std::size_t size() const { return size_; }

    template <typename OS>
    void print(OS& os) const {
        for (std::size_t i = 0; i < size_; ++i) {
            if (i) os << ' ';
            os << data_[i];
        }
        os << '\n';
    }

private:
    std::size_t size_{ 0 };
    T* data_{ nullptr };

    void checkBounds(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("The index is out of the bounds of the array, number not stored");
        }
    }

    void swap(NumberArray& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }
};

#endif // NUMBERARRAY_TPP
