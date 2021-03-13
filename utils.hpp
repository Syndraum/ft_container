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

	template<bool B, class T = void>
		struct enable_if {};

	template<class T>
		struct enable_if<true, T> { typedef T type; };

	template<class InputIterator>
	std::ptrdiff_t distance (InputIterator first, InputIterator last){
		std::ptrdiff_t diff = 0;
		for (InputIterator it = first; it != last; it++)
			diff++;
		return (diff);
	}
}

#endif