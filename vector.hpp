#ifndef VECTOR_H
# define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "utils.hpp"
#include "vector_iterator.hpp"
#include "allocator.hpp"
#include "reverse_iterator.hpp"

namespace ft{
	template < typename T, typename Alloc = ft::allocator<T> >
	class vector
	{
	public:
		typedef T										value_type;
		typedef Alloc									allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef ft::vector_iterator<value_type>			iterator;
		typedef ft::vector_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator< iterator >		reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;
		typedef std::ptrdiff_t							difference_type;
		typedef size_t									size_type;

	private:
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;
		pointer			_data;

		void	setCapacity(size_type capacity){
			_capacity = capacity;
		}

		static size_type	get_fit_capacity(size_type target){
			size_type	capacity = 8;
			while (capacity < target)
				capacity *= 2;
			return (capacity);
		}

		pointer	allocate(size_type n) {
			return (_allocator.allocate(n));
		}

		void	deallocate() {
			_allocator.deallocate(_data);
			// _allocator.deallocate(_data, _capacity);
		}

		void	construct(size_type index, const_reference val, pointer data) {
			_allocator.construct(_allocator.address(data[index]), val);
		}

		void	construct(size_type index, const_reference val) {
			construct(index, val, _data);
		}

		void	destroy(size_type index, pointer data) {
			_allocator.destroy(_allocator.address(data[index]));
		}

		void	destroy(size_type index) {
			destroy(index, _data);
		}

		void	destroy(iterator position) {
			size_type i = 0;
			iterator first = begin();
			while (first != position)
			{
				first++;
				i++;
			}
			destroy(i);
		}

		void	realloc(size_type target) {
			setCapacity(get_fit_capacity(target));
			pointer	new_data = 0;
			new_data = allocate(_capacity);
			for (size_t i = 0; i < _size; i++){
				construct(i, _data[i], new_data);
				destroy(i);
			}
			deallocate();
			_data = new_data;
		}

		void	realloc() {
			realloc(_capacity * 2);
		}

	public:
		vector(const allocator_type& alloc = allocator_type()) : _size(0), _capacity(8), _allocator(alloc), _data(_allocator.allocate(_capacity)) {}
		vector(
			size_type n,
			const value_type &val = value_type(),
			const allocator_type& alloc = allocator_type()) : _size(n), _capacity(get_fit_capacity(n)), _allocator(alloc), _data(_allocator.allocate(_capacity)) {
			for (size_t i = 0; i < n; i++)
				construct(i, val);
		}
		template <typename InputIterator>
		vector (
			InputIterator first,
			typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last,
			const allocator_type& alloc = allocator_type()) : _size(ft::distance< InputIterator >(first, last)), _capacity(get_fit_capacity(ft::distance< InputIterator >(first, last))), _allocator(alloc), _data(_allocator.allocate(_capacity)) {
				int i = 0;

				for (InputIterator it = first; it != last; it++) {
					construct(i, *it);
					i++;
				}
			}
		vector (const vector& x) : _size(0), _capacity(0), _allocator(x._allocator), _data(0) {
			this->_size = x._size;
			this->_capacity = x._capacity;
			this->_data = allocate(_capacity);
			for (size_t i = 0; i < this->_size; i++)
				this->_data[i] = x._data[i];
		}
		~vector(void) {
			clear();
			deallocate();
		}
		vector& operator= (const vector& x) {
			if (this != &x){
				clear();
				deallocate();
				this->_size = x._size;
				this->_capacity = x._capacity;
				this->_data = allocate(_capacity);
				for (size_t i = 0; i < this->_size; i++)
					this->_data[i] = x._data[i];
			}
			return (*this);
		}

		iterator begin() {
			if (empty())
				return (iterator());
			return (iterator(_data[0]));
		}

		const_iterator begin() const {
			if (empty())
				return (const_iterator());
			return (const_iterator(_data[0]));
		}

		iterator end() {
			if (empty())
				return (iterator());
			return (iterator(_data[size()]));
		}

		const_iterator end() const {
			if (empty())
				return (const_iterator());
			return (const_iterator(_data[size()]));
		}

		reverse_iterator rbegin(){
			return (reverse_iterator(_data[size()]));
		}

		const_reverse_iterator rbegin() const {
			return(rbegin());
		}

		reverse_iterator rend(){
			return(reverse_iterator(_data[0]));
		}

		const_reverse_iterator rend() const {
			return(rend());
		}

		size_type	size() const {
			return (this->_size);
		}

		size_type	max_size() const {
			return (_allocator.max_size());
		}

		void		resize (size_type n, value_type val = value_type()) {
			if (n > this->_capacity)
				realloc(n);
			if (n < this->_size){
				for (size_type i = n; i < _size; i++)
					destroy(i);
			}
			else {
				for (size_type i = _size; i < n; i++)
					construct(i, val);
			}
			this->_size = n;
		}

		void		reserve (size_type n) {
			try {
				if (n > _capacity)
					realloc(get_fit_capacity(n));
			} catch (std::exception& e) {
				throw;
			}
		}

		size_type	capacity() const {
			return (this->_capacity);
		}

		bool		empty() const {
			if(size())
				return (false);
			return (true);
		}

		reference operator[](size_type n) {
			return (*(_data + n));
		}

		const_reference operator[](size_type n) const {
			return (_data[n]);
		}

		reference at (size_type n) {
			std::stringstream tmp;
			if (n >= size()){
				tmp << "vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << size() << ")";
				throw std::out_of_range(tmp.str());
			}
			return (_data[n]);
		}

		const_reference at (size_type n) const {
			return (at(n));
		}

		reference front() {
			return (_data[0]);
		}

		const_reference front() const {
			return (_data[0]);
		}

		reference back() {
			return (_data[size() - 1]);
		}

		const_reference back() const {
			return (_data[size() - 1]);
		}

		template <class InputIterator>
		void assign (
				InputIterator first, 
				typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last) {
			size_type n = ft::distance(first, last);
			if (n > _capacity)
				realloc(n);
			for (size_type i = 0; i < _size; i++)
				destroy(i);
			_size = n;
			int i = 0;
			for (InputIterator it = first; it != last; it++){
				construct(i, *it);
				i++;
			}

		}

		void assign (size_type n, const value_type& val) {
			if (n > _capacity)
				realloc(n);
			for (size_type i = 0; i < _size; i++)
				destroy(i);
			_size = n;
			for (size_t i = 0; i < n; i++)
				construct(i, val);
		}

		void push_back (const value_type& val) {
			size_type	size = this->size();
			if (size == capacity())
				realloc();
			construct(size, val);
			_size++;
		}

		void pop_back() {
			if (!empty()){
				destroy(size() - 1);
				_size--;
			}
		}

		iterator insert (iterator position, const value_type& val) {
			difference_type	tmp = position - begin();
			insert(position, 1, val);
			return (begin() + tmp);
		}

		void insert (iterator position, size_type n, const value_type& val) {
			size_type to_end = end() - position;
			size_type j = 0;

			if (size() + n > capacity())
				realloc(size() + n);
			for (j = 0; j < to_end; j++)
			{
				construct(size() - 1 + n - j, _data[size() - 1 - j]);
				destroy(size() - 1 - j);
			}
			for (size_type i = 0; i < n; i++)
				construct(size() - 1 + n - j - i, val);
			_size += n;
		}

		template <class InputIterator>
		void insert (
			iterator position,
			InputIterator first,
			typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last) {
			size_type n = ft::distance(first, last);
			size_type diff_incert_end = ft::distance(position, end());
			size_type i = 0;
			size_type j = 0;

			if (size() + n > capacity()) {
				realloc(size() + n);
			}
			for (j = 0; j < diff_incert_end; j++)
			{
				construct(size() - 1 + n - j, _data[size() - 1 - j]);
				destroy(size() - 1 - j);
			}
			for (InputIterator it = last - 1; it != first - 1; it--){
				construct(size() - 1 + n - j - i, *it);
				i++;
			}
			_size += n;
		}

		iterator erase (iterator position) {
			return (erase(position, position + 1));
		}

		iterator erase (iterator first, iterator last) {
			iterator next = first + 1;
			difference_type diff = last - first;
			difference_type to_first = first - begin();
			difference_type to_end = end() - (first + diff);

			for (difference_type i = 0; i < diff; i++)
				destroy(to_first + i);
			for (difference_type i = 0; i < to_end; i++)
			{
				construct(to_first + i, _data[(to_first + i + diff)]);
				destroy(to_first + i + diff);
			}
			_size -= diff;
			return (next);
		}

		void swap (vector& x) {
			ft::swap(this->_size, x._size);
			ft::swap(this->_capacity, x._capacity);
			ft::swap(this->_allocator, x._allocator);
			ft::swap(this->_data, x._data);
		}

		void clear() {
			for (size_type i = 0; i < size(); i++)
				destroy(i);
			_size = 0;
		}
	};

	template <typename T, typename Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}

	template <typename T, typename Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
				return (false);
		}
		return (true);
	}

	template <typename T, typename Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return (!(lhs==rhs));
	}

	template <typename T, typename Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <typename T, typename Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return((rhs < lhs));
	}

	template <typename T, typename Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return(!(lhs > rhs));
	}

	template <typename T, typename Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return(!(lhs < rhs));
	}
}

#endif