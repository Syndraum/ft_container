#ifndef LIST_H
# define LIST_H

#include <cstdlib>
#include "utils.hpp"
#include "list_iterator.hpp"
#include "node.hpp"
#include "allocator.hpp"
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

			operator const list<T>(){
				return (const_cast< list<T> >(*this));
			}

			list& operator= (const list& x) {
				this->clear();
				const_iterator it;
				for (it = x.begin(); it != x.end(); it++)
					this->push_back(*it);
				return (*this);
			}

			iterator begin() {
				return (iterator(*(_front.next)));
			}

			const_iterator begin() const {
				return (const_iterator(reinterpret_cast<ft::node<const int> *>(_front.next)));
			}

			iterator end() {
				return (iterator(_back));
			}

			const_iterator end() const {
				return (const_iterator(reinterpret_cast<ft::node<const int> *>(_back.previous->next)));
			}

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

			template <class InputIterator>
			void assign (
				InputIterator first,
				typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last) {
				clear();
				for (InputIterator it = first; it != last; it++)
					push_back(*it);
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

			iterator insert (iterator position, const value_type& val) {
				iterator cursor;
				node * elm = new node(val);

				for (cursor = begin(); cursor != position; cursor++) { continue; }
				elm->previous = cursor.getNode()->previous;
				elm->next = cursor.getNode();
				elm->next->previous = elm;
				elm->previous->next = elm;
				_size++;
				return (iterator(elm));
			}

			void insert (iterator position, size_type n, const value_type& val) {
				iterator	cursor;
				node		*elm = 0;

				for (cursor = begin(); cursor != position; cursor++) { continue; }
				for (size_type i = 0; i < n; i++){
					elm = new node(val);
					elm->previous = cursor.getNode()->previous;
					elm->next = cursor.getNode();
					elm->next->previous = elm;
					elm->previous->next = elm;
				}
				_size += n;
			}

			template <class InputIterator>
			void insert (
					iterator position,
					InputIterator first,
					typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last
				) {
				iterator	cursor;
				node		*elm = 0;

				for (cursor = begin(); cursor != position; cursor++) { continue; }
				for (InputIterator it = first; it != last; it++){
					elm = new node(*it);
					elm->previous = cursor.getNode()->previous;
					elm->next = cursor.getNode();
					elm->next->previous = elm;
					elm->previous->next = elm;
				}
				_size += ft::distance(first, last);
			}

			iterator erase (iterator position) {
				iterator	cursor;
				node		*elm;

				for (cursor = begin(); cursor != position; cursor++) { continue; }
				elm = cursor.getNode();
				elm->previous->next = elm->next;
				elm->next->previous = elm->previous;
				cursor = iterator(elm->next);
				delete elm;
				_size--;
				return (cursor);
			}

			iterator erase (iterator first, iterator last) {
				iterator	cursor;
				node		*elm;
				size_type	diff = ft::distance(first, last);

				for (cursor = begin(); cursor != first; cursor++) { continue; }
				for (size_type i = 0; i < diff; i++)
				{
					elm = cursor.getNode();
					elm->previous->next = elm->next;
					elm->next->previous = elm->previous;
					cursor++;
					delete elm;
				}
				_size -= diff;
				return (cursor);
			}

			void swap (list& x) {
				ft::swap(this->_size, x._size);
				ft::swap(this->_front.next, x._front.next);
				ft::swap(this->_back.previous, x._back.previous);
				ft::swap(this->_back.previous->next, x._back.previous->next);
				ft::swap(this->_front.next->previous, x._front.next->previous);
				ft::swap(this->_allocator, x._allocator);
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

			void splice (iterator position, list& x) {
				splice(position, x, x.begin(), x.end());
			}

			void splice (iterator position, list& x, iterator i) {
				iterator inc = iterator(i);
				splice (position, x, i, ++inc);
			}

			void splice (iterator position, list& x, iterator first, iterator last) {
				node * end = position.getNode();
				node * begin = end->previous;
				node * new_first = first.getNode()->previous;
				node * new_last = last.getNode();
				size_type diff = ft::distance(first, last);

				begin->next = new_first->next;
				begin->next->previous = begin;
				end->previous = new_last->previous;
				end->previous->next = end;
				new_first->next = new_last;
				new_last->previous = new_first;
				this->_size += diff;
				x._size -= diff;
			}

			void remove (const value_type& val) {
				iterator jump;

				for (iterator it = begin(); it != end(); it++)
				{
					if (*it == val){
						jump = it;
						jump--;
						erase(it);
						it = jump;
					}
				}
			}

			template <class Predicate>
			void remove_if (Predicate pred) {
				iterator jump;

				for (iterator it = begin(); it != end(); it++){
					if (pred(*it)){
						jump = it;
						jump--;
						erase(it);
						it = jump;
					}
				}
			}

			void unique() {
				iterator last = begin();

				for (iterator it = ++begin(); it != end(); it++){
					if (*it == *last){
						erase(it);
						it = last;
					}
					last = it;
				}
			}

			template <class BinaryPredicate>
			void unique (BinaryPredicate binary_pred) {
				iterator last = begin();

				for (iterator it = ++begin(); it != end(); it++){
					if (binary_pred(*it, *last)){
						erase(it);
						it = last;
					}
					last = it;
				}
			}

			void merge (list& x) {
				list<T> tmp;

				if (this != &x){
					while (!(this->empty() || x.empty())) {
						if (this->front() < x.front())
							tmp.splice(tmp.end(), *this, this->begin());
						else
							tmp.splice(tmp.end(), x, x.begin());
					}
					this->splice(this->begin(), tmp);
					this->splice(this->end(), x);
				}
			}

			template <class Compare>
			void merge (list& x, Compare comp) {
				list<T> tmp;

				if (this != &x){
					while (!(this->empty() || x.empty())) {
						if (comp(this->front(), x.front()))
							tmp.splice(tmp.end(), *this, this->begin());
						else
							tmp.splice(tmp.end(), x, x.begin());
					}
					this->splice(this->begin(), tmp);
					this->splice(this->end(), x);
				}
			}

			void reverse() {
				node * cursor = 0;

				ft::swap(_front.next, _back.previous);
				ft::swap(_front.next->next, _back.previous->previous);
				for (iterator it = begin(); it != end(); it++ ){
					cursor = it.getNode();
					ft::swap(cursor->next, cursor->previous);
				}
			}
	};

	template <class T, class Alloc>
	bool operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		typename list<T,Alloc>::const_iterator rit = rhs.begin();
		for (typename list<T,Alloc>::const_iterator lit = lhs.begin(); lit != lhs.end(); lit++){
			if (*lit != *rit)
				return (false);
			++rit;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	void swap (list<T,Alloc>& x, list<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif