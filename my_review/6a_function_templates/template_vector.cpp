#include <iostream>
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

int main()
{
    std::vector<int> a = {1, 2, 3, 4};
    std::vector<float> b = {1.5f, 2.5f, 3.5f};
    std::vector<double> c = {10.0, 20.0, 30.0};

    std::cout << compute_mean(a) << "\n";
    std::cout << compute_mean(b) << "\n";
    std::cout << compute_mean(c) << "\n";

    return 0;
}

一个模板函数，计算 vector 的平均值
