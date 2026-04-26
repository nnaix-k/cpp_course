operator<<

#include <iostream>

class Point {
public:
    Point(int x_value, int y_value)
    {
        x = x_value;
        y = y_value;
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }

private:
    int x;
    int y;
};

int main()
{
    Point p(1, 2);
    std::cout << p << "\n";
    return 0;
}
