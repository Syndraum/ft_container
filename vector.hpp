#ifndef VECTOR_H
# define VECTOR_H

#include <iostream>
#include <algorithm>
#include <memory>

namespace ft{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	private:
		typedef T								value_type;
		typedef std::allocator< value_type >	allocator_type;
		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef value_type*						pointer;
		typedef const value_type*				const_pointer;
		typedef std::ptrdiff_t					differrence_type;
		typedef size_t							size_type;

		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;
		pointer			_data;


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

		void	construct(size_type index, const_reference val) {
			_allocator.construct(_allocator.address(_data[index]), val);
		}

		void	destroy(size_type index) {
			_allocator.destroy(_allocator.address(_data[index]));
		}

		void	realloc() {
			_capacity *= 2;
			pointer	new_data = allocate(_capacity);
			for (size_t i = 0; i < _size; i++)
				new_data[i] = this->_data[i];
			deallocate();
			_data = new_data;
		}
		void	realloc(size_type target) {
			_capacity = get_fit_capacity(target);
			size_type limit = std::min(_size, _capacity);
			pointer	new_data = allocate(_capacity);
			for (size_t i = 0; i < limit; i++)
				new_data[i] = this->_data[i];
			deallocate();
			_data = new_data;
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

		size_type	size() const {
			return (this->_size);
		}

		void resize (size_type n, value_type val = value_type()) {
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
			return (_data + n);
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

		// DELETE
		void print(void) {
			for (size_t i = 0; i < this->size(); i++)
			{
				std::cout << _data[i];
				if (i == this->size() -1)
					std::cout << std::endl;
				else
					std::cout << ", ";
			}
		}
	};
}

#endif