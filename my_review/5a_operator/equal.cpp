operator==

#include <iostream>

class Point {
public:
    Point(int x_value, int y_value)
    {
        x = x_value;
        y = y_value;
    }

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }

private:
    int x;
    int y;
};

int main()
{
    Point p1(1, 2);
    Point p2(1, 2);
    Point p3(3, 4);

    if (p1 == p2)
    {
        std::cout << "p1 and p2 are equal\n";
    }

    if (p1 == p3)
    {
        std::cout << "p1 and p3 are equal\n";
    }

    return 0;
}
