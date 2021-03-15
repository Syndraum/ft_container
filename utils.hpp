#ifndef UTILS_HPP
# define UTILS_HPP

#include <cstddef>

namespace ft{
	template <typename T, T val>
	struct storage
	{
		static const T value = val;
	};

	struct false_type : public storage<bool, false> {};
	struct true_type : public storage<bool, true> {};

	template <class T> struct is_integral : public false_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<short> : public true_type {};
	template <> struct is_integral<unsigned short> : public true_type {};
	template <> struct is_integral<long> : public true_type {};
	template <> struct is_integral<unsigned long> : public true_type {};
	template <> struct is_integral<long long> : public true_type {};
	template <> struct is_integral<unsigned long long> : public true_type {};

	template<bool B, typename T = void>
		struct enable_if {};

	template<typename T>
		struct enable_if<true, T> { typedef T type; };

	template<typename InputIterator>
	std::ptrdiff_t distance (InputIterator first, InputIterator last){
		std::ptrdiff_t diff = 0;
		for (InputIterator it = first; it != last; it++)
			diff++;
		return (diff);
	}

	template<typename T>
	void swap(T & x, T &y) {
		T	tmp = x;
		x = y;
		y = tmp;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (
		InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2) {
		while (first1!=last1) {
			if (first2==last2 || *first2<*first1)
				return false;
			else if (*first1<*first2)
				return true;
			++first1;
			++first2;
		}
		return (first2!=last2);
	}
}

#endif