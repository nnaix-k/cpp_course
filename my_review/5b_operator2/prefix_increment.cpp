++  （++v）

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

    Vector3D& operator++()
    {
        data[0] += 1;
        data[1] += 1;
        data[2] += 1;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Vector3D& v)
    {
        out << "(" << v.data[0] << ", " << v.data[1] << ", " << v.data[2] << ")";
        return out;
    }

private:
    std::array<double, 3> data;
};

int main()
{
    Vector3D v(1, 2, 3);

    std::cout << ++v << "\n";

    return 0;
}
