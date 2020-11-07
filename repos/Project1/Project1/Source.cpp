#include <iostream>
#include <math.h>
using namespace std;

class Point
{
private:
    double x, y;
public:
    Point()
    {
        this->x = 0;
        this->y = 0;
    }
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    void setX(double x)
    {
        this->x = x;
    }
    void setY(double y)
    {
        this->y = y;
    }
    double getX() const
    {
        return this->x;
    }
    double getY() const
    {
        return this->y;
    }
    double distanceToPoint(const Point& pointA)
    {
        return sqrt((this->x - pointA.getX()) * (this->x - pointA.getX()) + (this->y - pointA.getY()) * (this->y - pointA.getY()));
    }
};

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        /*
         * STUDENT ANSWER
         */
        this->center.setX(0);
        this->center.setY(0);
        this->radius = 0;
    }

    Circle(Point center, double radius)
    {
        /*
         * STUDENT ANSWER
         */
        this->center = center;
        this->radius = radius;
    }

    void operator=(const Circle& circle)
    {
        /*
         * STUDENT ANSWER
         */
        this->center = circle.center;
        this->radius = circle.radius;
    }

    bool operator==(const Circle& circle)
    {
        /*
         * STUDENT ANSWER
         */
        if (this->center.getX() == circle.center.getX() && this->center.getY() == circle.center.getY() && this->radius == circle.radius)
            return true;
        else
            return false;
    }

    friend istream& operator >> (istream& in, Circle& circle)
    {
        /*
         * STUDENT ANSWER
         */
        double A, B, C;
        in >> A;
        in >> B;
        in >> C;
        circle.center.setX(A);
        circle.center.setY(B);
        circle.radius = C;
        return in;
    }

    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};

int main() {
    Circle A;
    cin >> A;
    A.printCircle();
    return 0;
}