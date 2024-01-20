/*
 * Author: Peter Arandorenko
 * Date: January 26, 2024
 */

#ifndef ADD_VALUES_H
#define ADD_VALUES_H

#include <vector>
#include <limits>
#include <stdexcept>
#include <iostream>

template <typename T>
T addValues(const std::vector<T> &values)
{
    T sum = 0;
    const auto max = std::numeric_limits<T>::max();
    const auto min = std::numeric_limits<T>::min();
    for (const T &value : values)
    {
        // Check for overflow or underflow
        if (value > 0 && sum > max - value)
        {
            throw std::overflow_error("Overflow occurred.");
        }
        if (value < 0 && sum < min - value)
        {
            throw std::underflow_error("Underflow occurred.");
        }
        sum += value;
    }
    return sum;
}

#endif // ADD_VALUES_H
