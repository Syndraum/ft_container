#ifndef LIST_H
# define LIST_H

#include <cstdlib>

namespace ft {
	template < typename T, class Alloc = ft::allocator<T> >
	class list
	{
		public:
			typedef T					value_type;
			typedef Alloc				allocator_type;
			typedef value_type&			reference;
			typedef const value_type&	const_reference;
			typedef value_type*			pointer;
			typedef const value_type*	const_pointer;
			typedef std::ptrdiff_t		differrence_type;
			typedef size_t				size_type;

		private:
			class node
			{
			private:
				node(void) : data(T()), previous(0), next(0) {}
			public:
				node(const T & data) : data(data), previous(0), next(0) {}
				~node(void) {}

				T		data;
				node *	previous;
				node *	next;
			};

			node *		_front;
			node *		_back;
			size_type	_size;
			Alloc		_allocator;

		public:
			list (const allocator_type& alloc = allocator_type()): _front(0), _back(0), _size(0), _allocator(alloc) {}
			// list(size_type n, const value_type& val = value_type()) {
			// 	for (size_type i = 0; i < n; i++)
			// 		push_front(val);
			// }
			// list(const list & x) {this = x;}
			~list(void) {
				clear();
			}

			bool	empty() const{
				if (!_front)
					return false;
				return true;
			}

			size_type	size() const {
				return (_size);
			}

			size_type max_size() const {
				return (_allocator.max_size());
			}

			reference front(){
				return (_front->data);
			}

			reference back(){
				return (_back->data);
			}

			void push_front (const value_type& val){
				list::node * elm = new node(val);
				elm->next = _front;
				if (_front)
					_front->previous = elm;
				_front = elm;
				if (!_back)
					_back = elm;
				_size++;
			}

			void pop_front () {
				node * next_node = _front->next;
				delete _front;
				_front = next_node;
				_front->previous = 0;
				_size--;
			}

			void push_back (const value_type& val) {
				list::node * elm = new node(val);
				elm->previous = _back;
				if (_back)
					_back->next = elm;
				
				_back = elm;
				if (!_front)
					_front = elm;
				_size++;
			}

			void pop_back() {
				node * previous_node = _back->previous;
				delete _back;
				_back = previous_node;
				_back->next = 0;
				_size--;
			}

			void resize (size_type n, value_type val = value_type()) {
				if (n < size()){
					while (size() > n)
						pop_back();
				}
				else{
					while (size() < n)
						push_back(val);
				}
			}

			void clear () {
				node * next_node = 0;
				while (_front) {
					next_node = _front->next;
					delete _front;
					_front = next_node;
				}
			}
	};
}

#endif