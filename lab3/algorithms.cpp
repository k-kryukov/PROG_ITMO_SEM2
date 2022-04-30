#include "container.hpp"
#include <array>

int main() {
	using std::vector;
	using std::cin;
	using std::ofstream;
	using std::cout;
	using std::endl;
	cout << std::boolalpha;

	// ALGO
	vector<int> v1{ 1,2,3,3,2,1 };
	vector<std::string> v2{  "doch", "mama","papa", "sin" };
	vector<CPoint> v3{ {0,0}, {1,1}, {2,2} };
	vector<std::pair<int, int>> v4{ { 0,0 }, { 1,1 }, { 2,2 } };
	cout << algo::all_of(v1.begin(), v1.end(), [](int x) {return (x < 4); }) << endl;
	cout << algo::any_of(v1.begin(), v1.end(), [](int x) {return (x < 0); }) << endl;
	cout << algo::none_of(v2.begin(), v2.end(), [](std::string s) {return s=="ded"; }) 
		 << endl;
	cout << algo::one_of(v1.begin(), v1.end(), [](int x) {return (x < 0); }) << endl;
	cout << algo::is_sorted(v3.begin(), v3.end(), algo::less<CPoint>()) << endl;
	cout << algo::is_partitioned(v2.begin(), v2.end(),  
								 [](std::string s) { return s[0] > 'm'; })
		 << endl;
	cout << algo::is_palindrome("abacaba", "abacaba" + 7, algo::equal<const char>())
		 << endl;

	// CONTAINER
	circularBuffer<CPoint> cB(5);
	auto it = cB.end()--;
	cB.pop_back();

	return 0;
	circularBuffer<CPoint> temp(cB);

	cB.push_back({ 1,2 });
	cB.push_front({ 0, 1 });

	for (auto cur_point : cB) {
		cout << cur_point << ' ';
	} 
	cout << endl;
	
	cB.push_back({ 2,3 });
	cB.push_front({ -1, 0});

	cout << cB.pop_front() << ' ' << cB.pop_front() << endl;

	for (auto cur_point : cB) {
		cout << cur_point << ' ';
	}
	cout << endl;

	cB.push_back({ 2,3 });
	cB.push_front({ -1, 0 });

	for (circularBuffer<CPoint>::iterator it = cB.begin(); it != cB.end(); ++it) {
		cout << *it << ' ';
	}
	cout << endl;

	for (auto x : cB)
		cout << x << ' ';
	cout << endl;

	cB.resize(2);
	cB.print_range();

	return 0;
}