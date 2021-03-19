#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

#include <cstddef>
#include "iterator.hpp"
#include "utils.hpp"
#include "node.hpp"

namespace ft
{
	template < typename T >
	class list_iterator
	{
	public:
		typedef T											value_type;
		typedef std::ptrdiff_t								difference_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef ft::random_access_iterator_tag				iterator_category;
		typedef list_iterator								iterator;
		typedef ft::node<T>									node;

		list_iterator() : _node(0) {}
		list_iterator(node *x) : _node(x) {}
		list_iterator(const iterator &x) { *this = x; }
		~list_iterator() {}

		iterator &operator=(const iterator &x)
		{
			_node = x._node;
			return (*this);
		}

		friend bool operator==(const iterator &x, const iterator &y)
		{
			return (x._node == y._node);
		}

		friend bool operator!=(const iterator &x, const iterator &y)
		{
			return (!(x == y));
		}

		operator vector_iterator<const T>() {
			return vector_iterator<const T>(*this->_node);
		}

		value_type &operator*() const { return (_node->data); }
		value_type *operator->() const { return (&_node->node); }

		iterator &operator++()
		{
			this->_node = this->_node->next;
			return (*this);
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			this->_node = this->_node->next;
			return (tmp);
		}

		iterator &operator--()
		{
			this->_node = this->_node->previous;
			return (*this);
		}
		iterator operator--(int)
		{
			iterator tmp = *this;
			this->_node = this->_node->previous;
			return (tmp);
		}

	protected:
		node *_node;
	};
}

#endif