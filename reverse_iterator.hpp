#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
namespace ft {
	template < typename Iterator >
	class reverse_iterator
	{
	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;

		reverse_iterator() : _base_it(iterator_type()) {}
		explicit reverse_iterator (iterator_type it) : _base_it(it) {}
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base_it(rev_it.base()) {}
		~reverse_iterator() {}

		iterator_type	base() const
		{
			return (_base_it);
		}

		reference		operator*() const
		{
			iterator_type tmp = _base_it;
			return (*(--tmp));
		}

		reverse_iterator operator+ (difference_type n) const
		{
			return (reverse_iterator(_base_it - n));
		}

		reverse_iterator& operator++()
		{
			--_base_it;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		reverse_iterator& operator+= (difference_type n)
		{
			_base_it -= n;
			return(*this);
		}

		reverse_iterator operator- (difference_type n) const
		{
			return ( reverse_iterator(_base_it + n));
		}

		reverse_iterator& operator--()
		{
			++_base_it;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		reverse_iterator& operator-= (difference_type n)
		{
			_base_it += n;
			return(*this);
		}

		pointer operator->() const
		{
			iterator_type	tmp(_base_it);
			tmp--;
			return(tmp.operator->());
		}

		reference operator[] (difference_type n) const
		{
			return (base()[-n-1]);
		}

	private:
		iterator_type	_base_it;
	};

	template <typename Iterator1, typename Iterator2>
	bool operator== (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator!= (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator< (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator> (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<= (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>= (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it)
	{
			return (rev_it + n);
	}

	template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator- (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
			return((rhs.base() - lhs.base()));
	}
}

#endif