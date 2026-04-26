operator+


#include <iostream>

class Point {
public:
    Point(int x_value, int y_value)
    {
        x = x_value;
        y = y_value;
    }

    Point operator+(const Point& other) const
    {
        return Point(x + other.x, y + other.y);
    }

    void print() const
    {
        std::cout << "(" << x << ", " << y << ")\n";
    }

private:
    int x;
    int y;
};

int main()
{
    Point p1(1, 2);
    Point p2(3, 4);

    Point p3 = p1 + p2;

    p1.print();
    p2.print();
    p3.print();

    return 0;
}
