operator!

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

    bool operator!() const
    {
        return data[0] == 0 && data[1] == 0 && data[2] == 0;
    }

private:
    std::array<double, 3> data;
};

int main()
{
    Vector3D v1(0, 0, 0);
    Vector3D v2(1, 0, 0);

    if (!v1)
    {
        std::cout << "v1 is zero\n";
    }

    if (!v2)
    {
        std::cout << "v2 is zero\n";
    }

    return 0;
}
