template<int... numbers>
struct Polynom;

template<int x, int... numbers>
struct Polynom<x, numbers...> {
	static const int value = x;
	static const int degree = Polynom<numbers...>::degree + 1;
	using polynom = Polynom<numbers...>;
};

template<int x>
struct Polynom<x> {
	static const int value = x;
	static const int degree = 0;
};

template<>
struct Polynom<> {};

template<int x, int... numbers>
std::ostream& operator<<(std::ostream& out, Polynom <x, numbers...>const& p) {
	out << x << ' ';
	out << Polynom<numbers...>();
	return out;
}

template<int x>
std::ostream& operator<<(std::ostream& out, Polynom <x>const& p) {
	out << x << std::endl;
	return out;
}

constexpr const int pow(int x, int p) {
	if (p == 0)
		return 1;
	return x * pow(x, p - 1);
}

template<int x, int ...numbers>
constexpr int calculate(Polynom<x, numbers...> const& p, const int value) {
	return pow(value, Polynom<x, numbers...>::degree) * x
		+ calculate(Polynom<numbers...>(), value);
}

template<int x>
constexpr int calculate(Polynom<x> const& p, const int value) {
	return x;
}

constexpr int calculate(Polynom<> const& p, const int value) {
	return 0;
}