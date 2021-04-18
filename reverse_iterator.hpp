#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

namespace ft {
	template < typename Iterator >
	class reverse_iterator
	{
	public:
		typedef Iterator								iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;

		reverse_iterator() : _base_iterator(NULL) {}
		explicit reverse_iterator (iterator_type it) : _base_iterator(it) {}
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base_iterator(rev_it.base()) {}
		~reverse_iterator() {}

		iterator_type	base() const{
			return (this->_base_iterator);
		}

		reference		operator*() const {
			iterator_type tmp = _base_iterator;
			return (*(--tmp));
		}

		reverse_iterator operator+ (difference_type n) const {
			return ( reverse_iterator(_base_iterator - n));
		}

		reverse_iterator& operator++() {
			--(this->_base_iterator);
			return (*this);
		}

		reverse_iterator operator++(int) {
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		reverse_iterator& operator+= (difference_type n) {
			this->_base_iterator -= n;
			return(*this);
		}

		reverse_iterator operator- (difference_type n) const {
			return ( reverse_iterator(_base_iterator + n));
		}

		reverse_iterator& operator--() {
			++(this->_base_iterator);
			return (*this);
		}

		reverse_iterator operator--(int) {
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		reverse_iterator& operator-= (difference_type n) {
			this->_base_iterator += n;
			return(*this);
		}

		pointer operator->() const {
			iterator_type	tmp(this->_base_iterator);
			tmp--;
			return(tmp.operator->());
			// return &(operator*());
		}

		reference operator[] (difference_type n) const {
			return (base()[-n-1]);
		}

	private:
		iterator_type	_base_iterator;
	};

	template <typename Iterator1, typename Iterator2>
	bool operator== (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator!= (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator< (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator> (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<= (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>= (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it){
			return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs){
			return(ft::distance(lhs.base(), rhs.base()));
	}
}

#endif