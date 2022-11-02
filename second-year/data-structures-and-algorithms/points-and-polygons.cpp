/*
    Name: Avery Zeiler
    Student Number: 400305001
    MacID: zeilera
    Date: February 2, 2022
*/

#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

class Point
{
    public:
        Point ();			                        //constructor without arguments
        Point (double xCoord, double yCoord);	    //constructor to set x and y
        double getx () const;		                //gets the x private member
        double gety () const;		                //gets the y private member
        double distanceTo (const Point &otherP);    //calculates distance between 2 points
        friend istream& operator>> (istream& stream, Point& other);
        friend ostream& operator<< (ostream& stream, const Point& other);
    private:
        double x, y;
};

class Polygon
{
    public:
        Polygon (int ps);		                //constructor 1: indicates number of points
        Polygon (int ps, Point psvector[]);	    //constructor 2: contains array of points
        ~Polygon();                             //destructor
        double perimeter ();                    //calculates perimeter of polygon
        friend istream& operator>> (istream& stream, Polygon& other);
        friend ostream& operator<< (ostream& stream, const Polygon& other);
    private:
        int numPoints;
        Point * points;
};

Point::Point () {
  x = 0;
  y = 0;
}

Point::Point (double xCoord, double yCoord) {
  x = xCoord;
  y = yCoord;
}

double Point::getx () const {
  return x;
}

double Point::gety () const {
  return y;
}

double Point::distanceTo (const Point & otherP) {
  if ((pow (x - otherP.x, 2) + pow (y - otherP.y, 2)) >= 0) {
      return sqrt (pow (x - otherP.x, 2) + pow (y - otherP.y, 2));
    } else {
      return 0;
    }
}

istream& operator>> (istream& stream, Point& other) {
    stream >> other.x >> other.y;
    return stream;
}

ostream& operator<< (ostream& stream, const Point& other) {
    stream << "P(" << other.x << "," << other.y << ")";
    return stream;
}

Polygon::Polygon (int ps) {
    numPoints = ps;
    points = new Point [numPoints];
    for (int i = 0; i < numPoints; i++) {
        points[i] = Point(0,0);
    }
}

Polygon::Polygon (int ps, Point psvector[]) {
    numPoints = ps;
    points = new Point [numPoints];
    for (int i = 0; i < numPoints; i++) {
        points[i] = psvector[i];
    }
}

Polygon::~Polygon() {
    delete [] points;
}

double Polygon::perimeter() {
    double sum = 0.0;
    for (int i = 0; i < (numPoints - 1); i++) {
        sum += points[i].distanceTo(points[i+1]);
    }
    sum += points[numPoints - 1].distanceTo(points[0]);
    return sum;
}

istream& operator>> (istream& stream, Polygon& other) {
    for (int i = 0; i < other.numPoints; i++) {
        stream >> other.points[i];
    }
    return stream;
}

ostream& operator<< (ostream& stream, const Polygon& other) {
    for (int i = 0; i < other.numPoints; i++) {
        stream << other.points[i] << " ";
    }
    return stream;
}

int main() {
    /*
    Expected output:

    P(0, 0), P(5, 12)
    5, 12
    13, 13
    P(9, 15)
    P(0, 0) P(0, 0) P(0, 0) P(0, 0) P(0, 0)
    P(0, 0) P(0, 1) P(1, 1) P(1, 0)
    4, 0
    P(1, 4) P(5, 1) P(10, 13) P(6, 10) P(1, 10)
    34
    */

    Point p1;  // (2) no arg constructor
    cout << p1 << ", ";  

    Point p2(5, 12);  // (3) two arg constructor
    cout << p2 << "\n";

    cout << p2.getx() << ", ";  // (4) getters
    cout << p2.gety() << "\n";

    cout << p1.distanceTo(p2) << ", ";  // (5) distanceTo
    cout << p2.distanceTo(p1) << "\n";

    istringstream input1("9 15");  // (6) input
    input1 >> p1;
    cout << p1 << "\n";

    Polygon poly(5);  // (9) size-only constructor
    cout << poly << "\n";

    Point* points_list = new Point[4];  // (10) array constructor
    points_list[0] = Point(0, 0);
    points_list[1] = Point(0, 1);
    points_list[2] = Point(1, 1);
    points_list[3] = Point(1, 0);
    Polygon rectangle(4, points_list);
    cout << rectangle << "\n";


    cout << rectangle.perimeter() << ", "; // (12) perimeter
    cout << poly.perimeter() << "\n";


    istringstream input2("1 4 5 1 10 13 6 10 1 10");  // (13) input
    input2 >> poly;
    cout << poly << "\n";
    cout << poly.perimeter() << "\n";
    
    return 0;
}
