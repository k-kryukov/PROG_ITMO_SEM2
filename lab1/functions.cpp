#include "geometry.h"

struct Segment {
	Point p1;
	Point p2;

	Segment() : p1({ 0, 0 }), p2({ 0, 0 }) {}
	Segment(pair<double, double> p1, pair<double, double> p2) : p1(p1), p2(p2) {}
	bool parall(Segment const& s) {
		if (this->p2.x - this->p1.x == 0 || s.p2.x - s.p1.x == 0) {
			if (s.p2.x - s.p1.x == 0 && this->p2.x - this->p1.x == 0)
				return true;
			return false;
		}

		return abs((this->p2.y - this->p1.y) / (this->p2.x - this->p1.x) 
				 - (s.p2.y - s.p1.y) / (s.p2.x - s.p1.x)) < EPS;
	}
};

void delete_odd_spaces(string& s) {
	int i = 1, j = 1, n = s.length();

	for (; j < n; ++j) {
		if (s[j - 1] == ' ' && s[j] == ' ')
			continue;

		s[i] = s[j];
		++i;
	}

	s.resize(i);
}

void reverse_words(string& s) {
	int i = 0, n = s.length();

	while (i < n) {
		while (i < n && s[i] == ' ') {
			++i;
		}
		if (i == n)
			break;

		int left = i, right = 0;
		while (s[i] != ' ' && i < n)
			++i;
		right = i - 1;

		int new_left = i;
		while (right - left + 1 > 1) {
			swap(s[right], s[left]);
			++left;
			--right;
		}

		i = new_left;
	}
}

bool correct_trapeze(vector<pair<double, double>> const& p) {
	vector<Segment> segments(4);
	for (int i = 0; i < 4; ++i) {
		segments[i] = Segment(p[i], p[(i + 1) % 4]);
	}

	for (int i = 0; i < 4; ++i) {
		for (int j = i + 1; j < 4; ++j) {
			if (segments[i].parall(segments[j])) {
				if (j - i == 2)
					return true;
				else
					return false;
			}
		}
	}
	
	return false;
}