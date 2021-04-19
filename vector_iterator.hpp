#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <iterator>
#include <cstddef>
#include "utils.hpp"

namespace ft
{
	template < typename T >
	class vector_iterator
	{
	public:
		typedef T											value_type;
		typedef std::ptrdiff_t								difference_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef std::random_access_iterator_tag				iterator_category;
		typedef vector_iterator								iterator;
		typedef vector_iterator<const T>					const_iterator;

		vector_iterator() : _p(0) {}
		vector_iterator(value_type &x) : _p(&x) {}
		vector_iterator(value_type *x) : _p(x) {}
		vector_iterator(const iterator &x) { *this = x; }
		virtual ~vector_iterator(void) {}

		iterator &operator=(const iterator &x)
		{
			_p = x._p;
			return (*this);
		}

		operator vector_iterator<const T>() {
			return vector_iterator<const T>(*this->_p);
		}

		value_type &operator*() const { return (*_p); }
		value_type *operator->() const { return (_p); }

		iterator &operator++()
		{
			this->_p++;
			return (*this);
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			++(this->_p);
			return (tmp);
		}

		iterator &operator--()
		{
			this->_p--;
			return (*this);
		}
		iterator operator--(int)
		{
			iterator tmp = *this;
			--(this->_p);
			return (tmp);
		}

		iterator operator+(const difference_type &n) const
		{
			return (iterator(_p[n]));
		}
		friend iterator operator+(const difference_type n, const iterator &x)
		{
			return (x + n);
		}
		iterator operator-(const int &n) const
		{
			return (iterator(*(_p - n)));
		}
		// difference_type operator-(const iterator &it) const
		// {
		// 	return (_p - it._p);
		// }
		iterator &operator+=(const int &n)
		{
			_p += n;
			return (*this);
		}
		iterator &operator-=(const int &n)
		{
			_p -= n;
			return (*this);
		}
		value_type &operator[](const int index) const { return (_p[index]); }
	protected:
		value_type *_p;
	};

	template < typename T, typename U >
	typename vector_iterator<T>::difference_type operator-(const vector_iterator<T> &x, const vector_iterator<U> &y)
	{
		return (&x[0] - &y[0]);
	}

	template < typename T, typename U >
	bool operator==(const vector_iterator<T> &x, const vector_iterator<U> &y)
	{
		return (&x[0] == &y[0]);
	}

	template < typename T, typename U >
	bool operator!=(const vector_iterator<T> &x, const vector_iterator<U> &y)
	{
		return (!(x == y));
	}

	template < typename T, typename U >
	bool operator<(const vector_iterator<T> &x, const vector_iterator<U> &y) 
	{
		return (&x[0] < &y[0]);
	}
	template < typename T, typename U >
	bool operator>(const vector_iterator<T> &x, const vector_iterator<U> &y) 
	{
		return (&x[0] > &y[0]);
	}
	template < typename T, typename U >
	bool operator<=(const vector_iterator<T> &x, const vector_iterator<U> &y) 
	{
		return (!(x > y));
	}
	template < typename T, typename U >
	bool operator>=(const vector_iterator<T> &x, const vector_iterator<U> &y) 
	{
		return (!(x < y));
	}
}

#endif