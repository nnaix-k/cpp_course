operator+=

#include <iostream>

class Point {
public:
    Point(int x_value, int y_value)
    {
        x = x_value;
        y = y_value;
    }

    Point& operator+=(const Point& other)
    {
        x += other.x;
        y += other.y;
        return *this;
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

    p1 += p2;
    p1.print();

    return 0;
}
