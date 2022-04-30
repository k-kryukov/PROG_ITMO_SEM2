#include "geometry.h"

int main() {
	// ALGEBRA TEST MODULE
	{
		Polynom<double> p1({ 1, 2, 1 });
		Polynom<double> p2({ 1, 4, 6, 4, 1 });
		cout << "p1: " << p1 << "p2: " << p2;
		cout << "p1 + p2: " << p1 + p2;
		cout << "p1 - p2: " << p1 - p2;
		p1 -= p2;
		cout << "p1: " << p1;
		cout << "p1 * 8: " << p1 * 8;

		cout << "Input coef to generate a polynom!\n";
		cin >> p1;
		cout << "p1: " << p1;
		p1 = p2;
		cout << "p1 after =p2:" << p1;
		cout << "p1 == p2: " << boolalpha << (p1 == p2);
	}

	// GEOMETRY TEST MODULE!
	{
		Point p1(1, 2), p2(0, 0);
		cout << p1.dist(p2) << endl;

		Polyline pl({ {0, 0}, {1,1}, {2,0} });
		cout << pl.perimeter() << endl;

		ClosedPolyline cpl({ {0, 0}, {1,1}, {2,2} });
		cout << cpl.perimeter() << endl;

		Polygon p({ {0, 0}, {1,1}, {2,1}, {3, 0} });
		cout << p.perimeter() << ' ' << p.square() << endl;

		Triangle t({ {0, 0}, {1, 0}, {0, 1} });
		cout << t.perimeter() << ' ' << t.square() << endl;

		Trapeze tpz({ {0, 0}, {0, 2}, {2, 2}, {4, 0} });

		vector<Polygon*> shapes(4);
		shapes[0] = new Polygon(p);
		shapes[1] = new Triangle(t);
		shapes[2] = new Trapeze(tpz);
	}
	return 0;
}