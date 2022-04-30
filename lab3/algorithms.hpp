#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <ctime>
#include <unordered_set>
#include <algorithm>
#include <list>
#include <cassert>
#include <fstream>
#include <limits>
#include <iterator>
#include <cassert>
#include <cmath>

#pragma once

namespace algo {
	template<typename T>
	struct equal {
		bool operator()(T& a, T& b) {
			return (a == b);
		}
	};
	template<typename T>
	struct greater {
		bool operator()(T& a, T& b) {
			return (a > b);
		}
	};
	template<typename T>
	struct less {
		bool operator()(T& a, T& b) {
			return (a < b);
		}
	};

	template<typename it>
	void verify_range(it first, it last, 
					  std::random_access_iterator_tag it_tag) {
		assert(first <= last);
	}

	template<typename it>
	void verify_range(it first, it last, std::bidirectional_iterator_tag it_tag) {}

	template<typename InputIt, typename Func>
	bool all_of(InputIt first, InputIt last, Func pred) {
		verify_range(first, last, std::iterator_traits<InputIt>::iterator_category());
		for (auto iter = first; iter != last; ++iter) {
			if (!pred(*iter))
				return false;
		}

		return true;
	}

	template<typename InputIt, typename Func>
	bool any_of(InputIt first, InputIt last, Func pred) {
		verify_range(first, last, std::iterator_traits<InputIt>::iterator_category());

		for (auto iter = first; iter != last; ++iter) {
			if (pred(*iter))
				return true;
		}

		return false;
	}

	template<typename InputIt, typename Func>
	bool none_of(InputIt first, InputIt last, Func pred) {
		verify_range(first, last, std::iterator_traits<InputIt>::iterator_category());

		for (auto iter = first; iter != last; ++iter) {
			if (pred(*iter))
				return false;
		}

		return true;
	}

	template<typename InputIt, typename Func>
	bool one_of(InputIt first, InputIt last, Func pred) {
		verify_range(first, last, std::iterator_traits<InputIt>::iterator_category());

		bool answer = false;
		for (auto iter = first; iter != last; ++iter) {
			bool cur_res = pred(*iter);

			if (cur_res && !answer) {
				answer = true;
			}
			else if (cur_res)
				return false;
		}

		return answer;
	}

	template<typename InputIt, typename Func>
	bool is_sorted(InputIt first, InputIt last, Func pred) {
		verify_range(first, last, std::iterator_traits<InputIt>::iterator_category());

		auto prev = first;
		for (auto iter = ++first; iter != last; ++iter) {
			if (!pred(*prev, *iter))
				return false;

			++prev;
		}

		return true;
	}

	template<typename InputIt, typename Func, typename T>
	InputIt find_not(InputIt first, InputIt last, T element) { // decltype(*first)
		verify_range(first, last, std::iterator_traits<InputIt>::iterator_category());

		for (auto it = first; it != last; ++it) {
			if (*it != element) {
				return it;
			}
		}

		return last;
	}

	template<typename BidirIt, typename T>
	BidirIt find_backward(BidirIt first, BidirIt last, T element) { // decltype(*first)
		verify_range(first, last, std::iterator_traits<BidirIt>::iterator_category());
		BidirIt tale = (--last)++;

		for (auto it = tale; it != first; --it) {
			if (*it == element) {
				return it;
			}
		}

		if (*first == element)
			return first;

		return last;
	}

	template<typename BidirIt, typename Func>
	bool is_palindrome(BidirIt first, BidirIt last, Func pred) {
		verify_range(first, last, std::iterator_traits<BidirIt>::iterator_category());
		BidirIt begin = first, end = --last;

		while (begin != end) {
			if (!pred(*begin, *end))
				return false;

			++begin;
			if (begin == end)
				return true;
			--end;
		}

		return true;
	}

	template<typename InputIt, typename Func>
	bool is_partitioned(InputIt first, InputIt last, Func pred) {
		verify_range(first, last, std::iterator_traits<InputIt>::iterator_category());

		bool found_partitioner = false;
		bool first_ok = false;

		for (auto iter = first; iter != last; ++iter) {
			if (found_partitioner && (!first_ok != pred(*iter)))
				return false;

			if (iter == first) {
				if (pred(*iter))
					first_ok = true;
			}
			else {
				if (first_ok && !pred(*iter) || !first_ok && pred(*iter)) {
					found_partitioner = true;
				}
			}
		}

		return true;
	}
}