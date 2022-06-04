#include <iostream>
#include "headers.hpp"

int main() {
	using std::cout;
	
	Polynom<0, 0, 0, 0> p;
	static_assert(calculate(p, 1) == 0);
}