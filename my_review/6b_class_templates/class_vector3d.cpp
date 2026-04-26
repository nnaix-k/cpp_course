#include <iostream>
#include <array>

template <typename X>
class Vector3D {
public:
    Vector3D() : data{0, 0, 0} {}

    X& operator[](int i)
    {
        return data[i];
    }

    const X& operator[](int i) const
    {
        return data[i];
    }

private:
    std::array<X, 3> data;
};

int main()
{
    Vector3D<double> a;
    a[0] = 1.1;
    a[1] = 2.2;
    a[2] = 3.3;

    std::cout << a[0] << "\n";
    std::cout << a[1] << "\n";
    std::cout << a[2] << "\n";

    return 0;
}

Vector3D 不再固定存 double
而是存 X 类型
调用时
Vector3D<double> a;
Vector3D<int> b;
Vector3D<float> c;

