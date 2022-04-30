#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <cassert>
#include <map>

using namespace std;

#define EPS 0.000001

void delete_odd_spaces(string& s);

void reverse_words(string& s);

bool correct_trapeze(vector<pair<double, double>> const& p);

template<class T = double>	
struct Polynom {
	Polynom() = default;

	Polynom(T* coef, size_t degree) {
		for (int i = 0; i < degree; ++i) {
			this->coef[i] = coef[i];
		}
	}
	Polynom(T free_member) {
		coef[0] = free_member;
	}
	Polynom(std::vector<T> const& coef) {
		for (int i = 0; i < coef.size(); ++i) {
			this->coef[i] = coef[coef.size() - 1 - i];
		}
	}
	Polynom(Polynom const& p) {
		coef.clear();

		for (auto x : p.coef) {
			this->coef[x.first] = x.second;
		}
	}
	~Polynom() {
		coef.clear();
	}
	bool operator==(Polynom const& p) {
		if (p.coef.empty() && coef.empty())
			return true;
		else if (p.coef.empty() xor coef.empty())
			return false;

		return coef == p.coef;
	}
	Polynom& operator=(Polynom const& p) {
		if (*this != p) {
			coef.clear();
			coef = p.coef;
		}

		return *this;
	}
	bool operator!=(Polynom const& p) {
		return !(*this == p);
	}
	
	Polynom operator+() { return *this; }
	Polynom operator-() {
		for (auto& x : coef) {
			x.second = -x.second;
		}

		return *this;
	}
	Polynom& operator+=(Polynom const& p) {
		for (auto x : p.coef) {
			if (coef.find(x.first) != coef.end()) {
				coef[x.first] += x.second;
				if (coef[x.first] == 0)
					coef.erase(x.first);
			}
			else {
				if (x.second != 0)
					coef[x.first] = x.second;
			}
		}

		return *this;
	}
	Polynom& operator-=(Polynom p) {
		*this += -p;
		return *this;
	}
	Polynom operator+(Polynom const& p) {
		Polynom temp(*this);

		return (temp += p);
	}
	Polynom operator-(Polynom p) {
		Polynom temp(*this);

		return (temp -= p);
	}
	T operator[](size_t i) const { 
		assert(coef.find(i) != coef.end());

		return coef[i];
	}
	T& operator[](size_t i) {
		assert(coef.find(i) != coef.end());

		return coef[i];
	}

	Polynom& operator*=(int n) {
		for (auto& x : coef)
			x.second *= n;

		return *this;
	}
	Polynom& operator/=(int n) {
		assert(n != 0);
		for (auto& x : coef)
			x.second *= n;

		return *this;
	}
	Polynom operator*(int n) {
		Polynom temp(*this);

		return (temp *= n);
	}
	Polynom operator/(int n) {
		Polynom temp(*this);

		return (temp /= n);
	}

	friend ostream& operator<<(ostream& stream, Polynom const& p) {
		if (p.coef.empty()) {
			stream << 0;
			return stream << endl;
		}

		if (p.coef.rbegin()->second == 1)
			stream << "x^" << p.coef.rbegin()->first << ' ';
		else
			stream << p.coef.rbegin()->second << "x^" << p.coef.rbegin()->first << ' ';
		vector<pair<size_t, T>> temp;
		for (auto x : p.coef)
			temp.push_back(x);

		for (int i = temp.size() - 2; i >= 0; --i) {
			pair<size_t, T> x;
			x.first = temp[i].first;
			x.second = temp[i].second;

			int deg = x.first;
			if (x.second == 0)
				continue;
			else if (deg == 0)
				stream << (x.second > 0 ? "+ " : "- ") << abs(x.second);
			else if (x.second == 1)
				stream << (x.second > 0 ? "+ " : "- ") << "x^" << deg << ' ';
			else
				stream << (x.second > 0 ? "+ " : "- ") << abs(x.second) << "x^" << deg << ' ';
		}

		return stream << endl;
	}

	friend istream& operator>>(istream& stream, Polynom& p) {
		p.coef.clear();

		string line;

		getline(stream, line);
		delete_odd_spaces(line);
		
		reverse_words(line);
		reverse(line.begin(), line.end());

		size_t degree = 0;
		for (int i = 0; i < line.length(); ++i) {
			if (line[i] == ' ' && i != 0 && i != line.length() - 1)
				++degree;
		}

		int cur_deg = 0;
		for (size_t i = (line[0] == ' '); i < line.length() && cur_deg <= degree; ++i) {
			p.coef[cur_deg] = 0;
			bool negative = false;
			while (i < line.length() && line[i] != ' ') {
				if (line[i] == '-') {
					negative = true;
				}
				else {
					p.coef[cur_deg] *= 10;
					p.coef[cur_deg] += negative ? -(line[i] - '0') : line[i] - '0';
				}
				++i;
			}

			++cur_deg;
		}

		return stream;
	}

private:
	map<size_t, T> coef;
};

template <class T = double>
Polynom<T> operator*(int n, Polynom<T> const& p) {
	return Polynom<T>(p) * n;
}