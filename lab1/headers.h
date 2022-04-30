#include <vector>

struct Polynom {
	Polynom() : degree(0) {
		coef = new double[degree + 1];
		coef[0] = 0;
	}
	Polynom(double* coef, size_t degree) : degree(degree) {
		this->coef = new double[degree + 1];
		for (int i = 0; i < degree; ++i)
			this->coef[i] = coef[i];
	}
	Polynom(std::vector<int> const& coef) {
		this->degree = coef.size();
		this->coef = new double[degree + 1];
		for (int i = 0; i < degree + 1; ++i) {

		}
	}

private:
	size_t degree;
	double* coef;
};