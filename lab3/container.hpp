#include "algorithms.hpp"

template<typename T>
struct type_size {
	static constexpr size_t size = sizeof(T);
};

class CPoint {
public:
	friend std::ostream& operator<<(std::ostream& stream, CPoint p);
	CPoint(double x = 0, double y = 0) : x_(x), y_(y) {}

	bool operator==(CPoint p2) {
		return (x_ == p2.x_ && y_ == p2.y_);
	}
	bool operator>(CPoint p2) {
		return (x_ > p2.x_) || (x_ == p2.x_ && y_ > p2.y_);
	}
	bool operator<(CPoint p2) {
		return (x_ < p2.x_) || (x_ == p2.x_ && y_ < p2.y_);
	}
private:
	double x_;
	double y_;
};

std::ostream& operator<<(std::ostream& stream, CPoint p) {
	stream << '(' << p.x_ << ',' << p.y_ << ')';

	return stream;
}

template<typename T>
struct cB_iterator : std::iterator<std::random_access_iterator_tag, T> {
	cB_iterator(T* ptr)
		: ptr_(ptr) {}
	cB_iterator() 
		: ptr_(nullptr) {}

	T& operator*() {
		return *ptr_;
	}
	T const& operator*() const {
		return *ptr_;
	}
	cB_iterator& operator++() {
		++ptr_;

		return *this;
	}
	cB_iterator& operator++(int) {
		cB_iterator temp_it(*this);
		++ptr_;

		return temp_it;
	}
	cB_iterator& operator--() {
		--ptr_;

		return *this;
	}
	cB_iterator& operator--(int) {
		cB_iterator temp_it(*this);
		--ptr_;

		return temp_it;
	}
	bool operator==(cB_iterator const& it) {
		return it.ptr_ == ptr_;
	}
	bool operator!=(cB_iterator const& it) {
		return it.ptr_ != ptr_;
	}
	cB_iterator& operator+=(size_t shift) {
		/*shift %= (end_ - begin_);
		if (ptr_ + shift < end_)
			ptr_ += shift;
		else {
			size_t overflow = (ptr_ + shift) - end_;
			ptr_ = begin_ + overflow;
		}

		return *this;*/
		ptr_ += shift;
		return *this;
	}
	cB_iterator& operator-=(size_t shift) {
		/*shift %= (end_ - begin_);
		if (ptr_ - shift >= begin_)
			ptr_ -= shift;
		else {
			size_t overflow = (begin_ - (ptr_ - shift));
			ptr_ = end_ - overflow;
		}

		return *this;*/
		ptr_ -= shift;
		return *this;
	}
	cB_iterator operator+(size_t shift) {
		cB_iterator temp(*this);

		return (temp += shift);
	}
	cB_iterator operator-(size_t shift) {
		cB_iterator temp(*this);

		return (temp -= shift);
	}
	bool operator<(cB_iterator it) {
		return ptr_ < it.ptr_;
	}
	bool operator>=(cB_iterator it) {
		return ptr_ >= it.ptr_;
	}
	bool operator<=(cB_iterator it) {
		return ptr_ <= it.ptr_;
	}
	bool operator>(cB_iterator it) {
		return ptr_ > it.ptr_;
	}

protected:
	T* ptr_;
};

template<typename T, typename _Alloc=std::allocator<T>>
class circularBuffer {
public:
	using iterator = cB_iterator<T>;
	using const_iterator = const cB_iterator<T>;
	using value_type = T;
	using pointer = typename T*;
	using const_pointer = typename T* const;
	using reference = T&;
	using const_reference = const T&;
	using allocator_type = _Alloc;
	using _Alty_traits = std::allocator_traits<_Alloc> ;

	circularBuffer() : circularBuffer(1) {}
	explicit circularBuffer(size_t n) {
		buffer = new T[n];
		capacity = n;
		first = buffer + (n / 2);
		last = first;
	}
	explicit circularBuffer(std::initializer_list<T> IL) {
		capacity = IL.size();
		buffer = new T[capacity];

		int counter = 0;
		for (auto x : IL) {
			buffer[counter++] = x;
		}
		first = buffer;
		last = buffer + capacity;
	}
	circularBuffer(circularBuffer const& cB) : capacity(cB.capacity) {
		size_t shift_f = first - buffer;
		size_t shift_l = last - buffer;

		buffer = new T[capacity];
		memcpy(buffer, cB.buffer, capacity * sizeof(T));
		first = buffer + shift_f;
		last = buffer + shift_l;
	}

	iterator begin() {
		return iterator(first);
	}
	iterator end() {
		return iterator(last);
	}
	const_iterator cbegin() {
		return iterator(first);
	}
	const_iterator cend() {
		return iterator(last);
	}

	T const& operator[](size_t index) const {
		assert(index < (last - first));

		return *(first + index);
	}

	void push_back(T const& new_el) {
		if (last == buffer + capacity) {
			size_t shift = (first - buffer);
			T* new_buffer = new T[capacity * 2];
			memcpy(new_buffer, buffer, capacity*sizeof(T));
			delete[] buffer;
			buffer = new_buffer;
			last = buffer + capacity;
			capacity *= 2;
			first = buffer + shift;
		}

		*last = new_el;
		++last;
	}

	void push_front(T const& new_el) {
		if (first == buffer) {
			size_t shift = last - buffer;
			T* new_buffer = new T[capacity * 2];
			memcpy(new_buffer + capacity, buffer, capacity * sizeof(T));
			delete[] buffer;
			buffer = new_buffer;
			last = buffer + capacity + shift;
			first = buffer + capacity;
			capacity *= 2;
		}
		--first;
		*first = new_el;
	}
	T pop_back() {
		assert(("Popping from empty buffer is unavailable", first < last));
		T temp(*(--last));
		*last = T();

		return std::move(temp);
	}
	T pop_front() {
		assert(first < last && "Popping from empty buffer is unavailable");
		T temp(*(first));
		*(first++) = T();

		return std::move(temp);
	}

	void print(std::ostream& stream = std::cout) const {
		for (auto it = first; it < last; it++) {
			stream << *it << ' ';
		}
		stream << '\n';
	}
	void print_range(std::ostream& stream = std::cout) const {
		for (auto it = buffer; it < buffer + capacity; ++it)
			stream << *it << ' ';
		stream << '\n';
	}
	size_t size() const {
		return last - first;
	}
void resize(size_t size, T&& el = T()) {
		size_t shift_l = last - buffer;
		size_t shift_f = first - buffer;
		T* new_buffer = new T[(first - buffer) + size 
							+ (buffer + capacity) - last];
		for (int i = 0; i < size; ++i) {
			if (i < (last - first)) {
				new_buffer[shift_f + i] = *(first + i);
			}
			else
				new_buffer[shift_f + i] = el;
		}
		first = new_buffer + shift_f;
		last = new_buffer + shift_f + size;
		delete[] buffer;
		buffer = new_buffer;
	}
protected:
	T* buffer;
	size_t capacity;
	T* first;
	T* last;
};