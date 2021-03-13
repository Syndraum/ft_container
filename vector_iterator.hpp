#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP

#include <cstddef>

namespace ft
{
	template < typename T >
	class vector_iterator
	{
	private:
		typedef std::ptrdiff_t		difference_type;
		typedef vector_iterator		iterator;

		T *_p;

	public:
		vector_iterator(void) : _p(0) {}
		vector_iterator(T &x) : _p(&x) {}
		vector_iterator(const iterator &x) { *this = x; }
		virtual ~vector_iterator(void) {}

		iterator &operator=(const iterator &x)
		{
			_p = x._p;
			return (*this);
		}

		friend bool operator==(const iterator &x, const iterator &y)
		{
			return (x._p == y._p);
		}

		friend bool operator!=(const iterator &x, const iterator &y)
		{
			return (!(x == y));
		}

		T &operator*() const { return (*_p); }
		T *operator->() const { return (_p); }

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

		iterator operator+(const difference_type &n)
		{
			return (iterator(_p[n]));
		}
		friend iterator operator+(const difference_type n, iterator &x)
		{
			return (x + n);
		}
		iterator operator-(const int &n)
		{
			return (iterator(*(_p - n)));
		}
		difference_type operator-(const iterator &it)
		{
			return (_p - it._p);
		}
		friend bool operator<(const iterator &x, const iterator &y)
		{
			return (x._p < y._p);
		}
		friend bool operator>(const iterator &x, const iterator &y)
		{
			return (x._p > y._p);
		}
		friend bool operator<=(const iterator &x, const iterator &y)
		{
			return (!(x > y));
		}
		friend bool operator>=(const iterator &x, const iterator &y)
		{
			return (!(x < y));
		}
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
		T &operator[](const int index) { return (_p[index]); }
	};
} // namespace ft

#endif