#ifndef VECTOR_H
# define VECTOR_H

#include <iostream>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <iterator>

namespace ft{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:
		class iterator : std::iterator <std::random_access_iterator_tag, T > {
			private:
				T *		_p;
			public:
				iterator(void) : _p(0) {}
				iterator(T & x) : _p(&x) {}
				iterator(const iterator & x) {*this = x;}
				iterator &	operator=(const iterator & x) {
					_p = x._p;
					return (*this);
				}

				friend bool	operator==(const iterator & x, const iterator & y){
					return (x._p == y._p);
				}

				friend bool	operator!=(const iterator & x, const iterator & y){
					return (!(x == y));
				}

				const T & operator*() const{return (*_p);}
				const T * operator->() const {return (_p);}

				iterator & operator++() {this->_p++; return (*this);}
				iterator operator++(int) {
					T tmp = *_p;
					++*this;
					return (tmp);
				}

				iterator & operator--() {this->_p--; return (*this);}
				iterator operator--(int) {
					T tmp = *_p;
					--*this;
					return (tmp);
				}

				iterator operator+(const int &n) {
					_p = _p + n;
					return (*this);
				}

				iterator operator-(const int &n) {
					_p = _p - n;
					return (*this);
				}

				// TEST
				iterator operator-(const iterator &it) {
					_p = _p - std::distance(*this, it);
					return(*this);
				}
		};

		typedef T										value_type;
		typedef std::allocator< value_type >			allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef iterator								iterator;
		typedef const iterator							const_iterator;
		typedef std::reverse_iterator< iterator >		reverse_iterator;
		typedef const std::reverse_iterator< iterator >	const_reverse_iterator;
		typedef std::ptrdiff_t							differrence_type;
		typedef size_t									size_type;

	private:
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;
		pointer			_data;

		void	setCapacity(size_type capacity){
			if (capacity > max_size())
				throw std::length_error("");
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
			_allocator.deallocate(_data, _capacity);
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

		void	realloc(size_type target) {
			setCapacity(get_fit_capacity(target));
			pointer	new_data = allocate(_capacity);
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
		~vector(void) {
			deallocate();
		}
		vector& operator= (const vector& x) {
			if (this != &x){
				deallocate();
				this->_size = x->_size;
				this->_capacity = x->_capacity;
				this->_data = allocate(_capacity);
				for (size_t i = 0; i < this->_capacity; i++)
					this->_data[i] = x->_data[i];
			}
			return (*this);
		}

		iterator begin() {
			if (empty())
				return (iterator());
			return (iterator(_data[0]));
		}

		const_iterator begin() const {
			return (begin());
		}

		iterator end() {
			if (empty())
				return (iterator());
			return (iterator(_data[size()]));
		}

		const_iterator end() const {
			return (end());
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
			if (n > _capacity)
				realloc(get_fit_capacity(n));
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
			return (_data + n);
		}

		const_reference operator[](size_type n) const {
			return (_data[n]);
		}

		reference at (size_type n) {
			if (n >= size())
				throw std::out_of_range("");
			return (_data + n);
		}

		const_reference at (size_type n) const {
			return (at(n));
		}

		reference front() {
			return (_data[0]);
		}

		const_reference front() const {
			return (front());
		}

		reference back() {
			return (_data[size() - 1]);
		}

		const_reference back() const {
			return (back());
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

		void swap (vector& x) {
			std::swap(this->_size, x._size);
			std::swap(this->_capacity, x._capacity);
			std::swap(this->_allocator, x._allocator);
			std::swap(this->_data, x._data);
			// pointer tmp = this->_data;

			// this->_data = x._data;
			// x._data = tmp;
		}

		void clear() {
			for (size_type i = 0; i < size(); i++)
				destroy(i);
			_size = 0;
		}

		// DELETE
		void print(void) {
			std::cout << "capacity : " << _capacity << "\t| ";
			for (size_t i = 0; i < this->size(); i++)
			{
				std::cout << _data[i];
				if (i != this->size() -1)
					std::cout << ", ";
			}
			std::cout << std::endl;
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

	// template <class T, class Alloc>
	// bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {

	// }
}

#endif