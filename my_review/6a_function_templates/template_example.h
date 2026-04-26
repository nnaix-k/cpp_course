#pragma once
#include <vector>

template <typename T>
double compute_mean(const std::vector<T>& data)
{
    double sum = 0.0;

    for (const auto& x : data)
    {
        sum += x;
    }

    return sum / data.size();
}
