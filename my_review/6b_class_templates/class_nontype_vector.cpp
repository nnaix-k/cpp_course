#include <iostream>
#include <array>

template <typename X, int D>
class Vector {
public:
    Vector() : data{} {}

    X& operator[](int i)
    {
        return data[i];
    }

    const X& operator[](int i) const
    {
        return data[i];
    }

private:
    std::array<X, D> data;
};

int main()
{
    Vector<double, 2> a;
    a[0] = 1.5;
    a[1] = 2.5;

    Vector<int, 4> b;
    b[0] = 10;
    b[1] = 20;
    b[2] = 30;
    b[3] = 40;

    std::cout << a[0] << " " << a[1] << "\n";
    std::cout << b[0] << " " << b[1] << " " << b[2] << " " << b[3] << "\n";

    return 0;
}



template <typename X, int D>
X 是类型参数
D 是数字参数
