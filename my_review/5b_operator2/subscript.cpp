operator[]

#include <iostream>
#include <array>

class Vector3D {
public:
    Vector3D(double x, double y, double z)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }

    double& operator[](int i)
    {
        return data[i];
    }

    const double& operator[](int i) const
    {
        return data[i];
    }

private:
    std::array<double, 3> data;
};

int main()
{
    Vector3D v(1.0, 2.0, 3.0);

    std::cout << v[0] << "\n";
    std::cout << v[1] << "\n";
    std::cout << v[2] << "\n";

    return 0;
}
