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
		reverse_iterator (iterator_type it) : _base_iterator(it) {};
		~reverse_iterator() {}

		iterator_type	base() const{
			return (this->_base_iterator);
		}

		reference		operator*() const {
			iterator_type tmp = _base_iterator;
			return (*(--tmp));
		}

		reverse_iterator operator+ (difference_type n) const {
			return ( _base_iterator - n);
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
			return ( _base_iterator + n);
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

	template <class Iterator>
	bool operator== (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool operator!= (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool operator< (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool operator> (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator<= (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool operator>= (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs) {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it){
			return (rev_it + n);
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator- (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it){
			return (rev_it - n);
	}
}

#endif