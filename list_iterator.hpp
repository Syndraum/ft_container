#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

#include <iterator>
#include <cstddef>
#include "utils.hpp"
#include "node.hpp"

namespace ft
{
	template < typename T>
	class list_iterator
	{
	public:
		typedef T											value_type;
		typedef std::ptrdiff_t								difference_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef list_iterator								iterator;
		typedef ft::node<T>									node;

		list_iterator() : _node(0) {}
		list_iterator(node *x) : _node(x) {}
		list_iterator(node &x) : _node(&x) {}
		list_iterator(const iterator &x) { *this = x; }
		~list_iterator() {}

		iterator &operator=(const iterator &x)
		{
			_node = x._node;
			return (*this);
		}

		operator list_iterator<const T>() {
			ft::node<const T> * new_node = reinterpret_cast<ft::node<const T> *>(this->_node);
			return list_iterator<const T>(new_node);
		}

		value_type &operator*() const { return (*(_node->data)); }
		value_type *operator->() const { return (_node->data); }

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

		node *	getNode() const{
			return (this->_node);
		}

	protected:
		node *_node;
	};

	template < typename T, typename U >
	bool operator==(const list_iterator<T> &x, const list_iterator<U> &y){
		return (x.getNode()->data == y.getNode()->data);
	}

	template < typename T, typename U >
	bool operator!=(const list_iterator<T> &x, const list_iterator<U> &y){
		return (!(x == y));
	}
}

#endif