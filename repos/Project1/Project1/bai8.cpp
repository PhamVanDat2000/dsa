#include <iostream>
#include<string.h>
using namespace std;

enum Color
{
    red,
    green,
    blue
};
enum Size
{
    small,
    medium,
    big
};

class Toy
{
protected:
    double price;

public:
    Toy(double price)
    {
        this->price = price;
    }

    virtual void printType() = 0;
    friend class ToyBox;
};

class CarToy : public Toy
{
private:
    Color color;

public:
    CarToy(double price, Color color) : Toy(price)
    {
        /*
         * STUDENT ANSWER
         */
        this->price = price;
        this->color = color;

    }

    void printType()
    {
        cout << "This is a car toy\n";
    }

    friend class ToyBox;
};

class PuzzleToy : public Toy
{
private:
    Size size;

public:
    PuzzleToy(double price, Size size) : Toy(price)
    {
        /*
         * STUDENT ANSWER
         */
        this->price = price;
        this->size = size;
    }

    void printType()
    {
        cout << "This is a puzzle toy\n";
    }

    friend class ToyBox;
};

class ToyBox
{
private:
    Toy* toyBox[5];
    int numberOfItems;

public:
    ToyBox()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero numberOfItems and nullptr toyBox
         */
        toyBox[0] = NULL;
        toyBox[1] = NULL;
        toyBox[2] = NULL;
        toyBox[3] = NULL;
        toyBox[4] = NULL;
        numberOfItems = 0;
    }

    int addItem(const CarToy& carToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Car toy to the box.
                 If successfully added, the function returns the current number of toys in the box.
                 If the box is full, return -1.
         */
        for (int i = 0; i < 5; i++) {
            if (toyBox[i] != NULL) {
                toyBox[i] = carToy;
                return i;
            }
            else
                return -1;
        }
    }

    int addItem(const PuzzleToy& puzzleToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Puzzle toy to the box.
                 If successfully added, the function returns the current number of toys in the box.
                 If the box is full, return -1.
         */
        for (int i = 0; i < 5; i++) {
            if (toyBox[i] != NULL) {
                toyBox[i] = puzzleToy;
                return i;
            }
            else
                return -1;
        }
    }

    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++)
            toyBox[i]->printType();
    }
};



int main() {
    CarToy car(20000, red);
    PuzzleToy puzzle(30000, small);
    car.printType();
    puzzle.printType();
    return 0;
}