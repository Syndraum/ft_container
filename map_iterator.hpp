#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "btree.hpp"
#include <iterator>

namespace ft {
	template <typename T>
	class map_iterator
	{
	public:
		typedef T											value_type;
		typedef std::ptrdiff_t								difference_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef map_iterator								iterator;
		typedef ft::btree<T>								btree;
		typedef ft::btree<const T>							const_btree;

		map_iterator() : _node(0) {}
		map_iterator(btree *x) : _node(x) {}
		map_iterator(btree &x) : _node(&x) {}
		map_iterator(const iterator &x) { *this = x; }
		~map_iterator() {}

		operator map_iterator<const T>(){
			return (map_iterator<const T>(reinterpret_cast< const_btree *>(_node)));
		}

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

		reference	operator*() const { return (*(_node->value)); }
		pointer		operator->() const { return (_node->value); }

		iterator &operator++()
		{
			btree *last = this->_node;

			if (_node->right) {
				_node = _node->right;
				while(_node->left)
					_node = _node->left;
			}
			else{
				_node = _node->parent;
				while (_node->parent && _node->right == last) {
					last = this->_node;
					_node = _node->parent;
				}
			}
			
			return (*this);
		}

		iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		iterator &operator--()
		{
			btree *last = this->_node;

			if (_node->left) {
				_node = _node->left;
				while(_node->right)
					_node = _node->right;
			}
			else{
				_node = _node->parent;
				while (_node->parent && _node->left == last) {
					last = this->_node;
					_node = _node->parent;
				}
			}
			return (*this);
		}

		iterator operator--(int)
		{
			iterator tmp = *this;
			--(*this);
			return (tmp);
		}

		btree *getNode(){
			return (this->_node);
		}

	private:
		btree *_node;
	};
}

#endif