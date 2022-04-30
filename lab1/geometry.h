#include "algebra.h"

const double pi = 3.1415;

struct Point {
	Point(double x = 0, double y = 0) {
		this->x = x;
		this->y = y;
	}
	Point(Point const& p) : x(p.x), y(p.y) {}
	Point(pair<double, double> p) : x(p.first), y(p.second) {}
	Point& operator=(Point const& p) = default;

	double dist(Point const& p) {
		return sqrt((this->x - p.x) * (this->x - p.x) +
			(this->y - p.y) * (this->y - p.y));
	}

	friend class Polygon;
	friend class Segment;

protected:
	double x, y;
};

struct Polyline {
	Point** points;
	size_t cnt_v;

	Polyline(std::vector<std::pair<double, double>> const& p) {
		assert(p.size() > 1);
		cnt_v = p.size();
		points = new Point*[p.size()];
		for (int i = 0; i < p.size(); ++i)
			points[i] = new Point(p[i].first, p[i].second);
	}
	virtual ~Polyline() {
		for (int i = 0; i < cnt_v; ++i)
			delete points[i];
		delete points;
	}
	Polyline(Polyline const& p) {
		cnt_v = p.cnt_v;

		points = new Point * [cnt_v];
		for (int i = 0; i < cnt_v; ++i) {
			points[i] = new Point(*p.points[i]);
		}
	}
	
	Polyline& operator=(Polyline const& p) {
		cout << "Assignment operator!\n";
		for (int i = 0; i < cnt_v; ++i) {
			delete points[i];
		}
		delete points;

		cnt_v = p.cnt_v;
		points = new Point *[cnt_v];
		
		for (int i = 0; i < cnt_v; ++i)
			points[i] = new Point(*p.points[i]);

		return *this;
	}

	virtual double perimeter() const {
		double p = 0;

		for (size_t i = 0; i < cnt_v - 1; ++i) {
			p += points[i]->dist(*points[i + 1]);
		}
		
		return p;
	}
};

struct ClosedPolyline : Polyline {
	ClosedPolyline(std::vector<pair<double, double>> const& p) : Polyline(p) {}

	ClosedPolyline(ClosedPolyline const& p) = default;

	ClosedPolyline& operator=(ClosedPolyline const& p) = default;

	double perimeter() const override {
		double p = Polyline::perimeter();
		p += points[0]->dist(*points[cnt_v - 1]);

		return p;
	}
};

struct Polygon : ClosedPolyline {
	Polygon(std::vector<pair<double, double>> const& p) : ClosedPolyline(p) {}

	Polygon(Polygon const& p) = default;
	Polygon& operator=(Polygon const& p) = default;

	double square() const {
		double s = points[cnt_v - 1]->x * points[0]->y
				 - points[cnt_v - 1]->y * points[0]->x;


		for (int i = 0; i < cnt_v - 1; ++i) {
			s += points[i]->x * points[i + 1]->y;
			s -= points[i + 1]->x * points[i]->y;
		}

		return abs(s) / 2;
	}
};

struct Triangle : Polygon {
	Triangle(std::vector<pair<double, double>> const& p) : Polygon(p) {
		assert(p.size() == 3 && square() > EPS);
	}
};

struct Trapeze : Polygon {
	Trapeze(std::vector<pair<double, double>> const& p) : Polygon(p) {
		assert(p.size() == 4 && square() > EPS && correct_trapeze(p));
	}

	Trapeze(Trapeze const& p) = default;
	Trapeze& operator=(Trapeze const& p) = default;

};

struct RegPolygon : Polygon {
	RegPolygon(std::vector<pair<double, double>> const& p) : Polygon(p) {}

	RegPolygon(RegPolygon const& rp) = default;
	RegPolygon& operator=(RegPolygon const& rp) = default;
};