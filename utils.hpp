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

	template <typename InputIterator1, typename InputIterator2>
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

	template <class Arg1, class Arg2, class Result>
	struct binary_function {
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	template <typename T>
	struct less : ft::binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const {return x<y;}
	};

	template <typename Key, typename T>
	struct pair
	{
		pair() : first(Key()), second(T()) {}
		pair(Key &key) : first(key), second(T()) {}
		pair(const Key &key, const T &value) : first(key), second(value) {}
		// pair(pair<Key, T> &x) : first(x.first), second(x.second) {}
		pair<Key, T> &operator=(pair<Key, T> x) {
			if (this != &x) {
				this->first = x.first;
				this->second = x.second;
			}
			return (*this);
		}

		Key	first;
		T	second;

		operator pair<const Key,  T>(){
			return (pair<const Key, T>(first, second));
		}

		template <typename U, typename V>
		operator pair<U, V>(){
			return (pair<U, V>(
				static_cast<U>(first),
				static_cast<V>(second)));
		}
	};
	
}

#endif