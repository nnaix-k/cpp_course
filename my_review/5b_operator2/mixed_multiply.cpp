放不同类型一起运算

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

    friend Vector3D operator*(const Vector3D& v, double x)
    {
        return Vector3D(v.data[0] * x, v.data[1] * x, v.data[2] * x);
    }

    friend Vector3D operator*(double x, const Vector3D& v)
    {
        return v * x;
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

    std::cout << v * 2.0 << "\n";
    std::cout << 2.0 * v << "\n";

    return 0;
}
