#ifndef LIST_H
# define LIST_H

#include <cstdlib>

namespace ft {
	template < typename T >
	class list
	{
		class node
		{
		private:
			T		_data;
			node *	_before;
			node *	_next;
			node(void) : _data(T()), _before(0), _next(0) {}
		public:
			node(const T & data) : _data(data), _before(0), _next(0) {}
			~node(void);

			void	setData(T const & data) {_data = data;}
			T &		getData(void) const {return _data;}
			void	setBefore(node * before) {_before = before;}
			node *	getBefore(void) const {return _before;}
			void	setNext(node * next) {_next = next;}
			node *	getNext(void) const {return _next;}
		};
		
		typedef T					value_type;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef value_type*			pointer;
		typedef const value_type*	const_pointer;
		typedef std::ptrdiff_t		differrence_type;
		typedef size_t				size_type;

		node *	_front;
		node *	_back;

		public:
			list(void) : _front(0), _back(0) {}
			list(size_type n, const value_type& val = value_type()) {
				for (size_type i = 0; i < n; i++)
					push_front(val);
			}
			list(const list & x) {this = x;}
			~list(void) {}

			bool	empty() const{
				if (!_front)
					return false;
				return true;
			}

			reference front(){
				return (*_front);
			}

			void push_front (const value_type& val){
				list::node * elm = new node(val);
				elm->setNext(_front);
				_front->setBefore(elm);
				_front = elm;
				if (!_back)
					_back = elm;
			}
	};
}

#endif