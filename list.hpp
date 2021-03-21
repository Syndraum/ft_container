#ifndef LIST_H
# define LIST_H

#include <cstdlib>
#include "list_iterator.hpp"
#include "node.hpp"
#include "reverse_iterator.hpp"

namespace ft {
	template < typename T, class Alloc = ft::allocator<T> >
	class list
	{
		public:
			typedef T										value_type;
			typedef Alloc									allocator_type;
			typedef value_type&								reference;
			typedef const value_type&						const_reference;
			typedef value_type*								pointer;
			typedef const value_type*						const_pointer;
			typedef ft::list_iterator<value_type>			iterator;
			typedef ft::list_iterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator< iterator >		reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;
			typedef std::ptrdiff_t							differrence_type;
			typedef size_t									size_type;
			typedef ft::node<T>								node;

		private:
			node		_front;
			node		_back;
			size_type	_size;
			Alloc		_allocator;

		public:
			list (const allocator_type& alloc = allocator_type()) : _front(node(T())), _back(node(T())), _size(0), _allocator(alloc) {
				_front.next = &_back;
				_back.previous = &_front;
			}
			list (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _front(node(T())), _back(node(T())), _size(0), _allocator(alloc) {
				_front.next = &_back;
				_back.previous = &_front;
				for (size_type i = 0; i < n; i++)
					push_front(val);
			}

			template <class InputIterator>
			list (
				InputIterator first,
				typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last,
				const allocator_type& alloc = allocator_type()) : _front(node(T())), _back(node(T())), _size(0), _allocator(alloc) {
				_front.next = &_back;
				_back.previous = &_front;
				for (InputIterator it = first; it != last; it++)
					push_back(*it);
			}

			// list(const list & x) {this = x;}
			~list(void) {
				clear();
			}

			// list& operator= (const list& x) {
			// 	this->clear();
			// 	const_iterator it;
			// 	for (it = x.begin(); it != x.end(); it++){
			// 		this->push_back(*it);
			// 	}
			// 	return (*this);
			// }

			iterator begin() {
				if (empty())
					return (iterator());
				return (iterator(_front.next));
			}

			// const_iterator begin() const {
			// 	return (const_iterator(_front.next));
			// }

			iterator end() {
				if (empty())
					return (iterator());
				return (iterator(&_back));
			}

			// const_iterator end() const {
			// 	return (const_iterator(&_back));
			// }

			reverse_iterator rbegin() {
				return (reverse_iterator(&_back));
			}

			// const_reverse_iterator rbegin() const {
			// 	return (reverse_iterator(&_back));
			// }

			reverse_iterator rend() {
				return (reverse_iterator(_front.next));
			}

			// const_reverse_iterator rend() const {
			// 	return (reverse_iterator(_front.next));
			// }

			bool	empty() const{

				if (_front.next != &_back)
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
				return (_front.next->data);
			}

			reference back(){
				return (_back.previous->data);
			}

			void assign (size_type n, const value_type& val) {
				clear();
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			void push_front (const value_type& val){
				list::node * elm = new node(val);

				elm->next = _front.next;
				elm->previous = &_front;
				_front.next->previous = elm;
				_front.next = elm;
				_size++;
			}

			void pop_front () {
				if (empty())
					return ;
				node * next_node = _front.next->next;
				delete _front.next;
				_front.next = next_node;
				next_node->previous = &_front;
				_size--;
			}

			void push_back (const value_type& val) {
				list::node * elm = new node(val);

				elm->previous = _back.previous;
				elm->next = &_back;
				_back.previous->next = elm;
				_back.previous = elm;
				_size++;
			}

			void pop_back() {
				if (empty())
					return ;
				node * previous_node = _back.previous->previous;
				delete _back.previous;
				_back.previous = previous_node;
				previous_node->next = &_back;
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
				while (size() > 0) 
					pop_front();
			}
	};
}

#endif