#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "btree.hpp"

namespace ft {
	template <typename T>
	class map_iterator
	{
	public:
		typedef T											value_type;
		typedef std::ptrdiff_t								difference_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef ft::bidirectional_iterator_tag				iterator_category;
		typedef map_iterator								iterator;
		typedef ft::btree<T>								btree;

		map_iterator() : _node(0) {}
		map_iterator(btree *x) : _node(x) {}
		map_iterator(btree &x) : _node(&x) {}
		map_iterator(const iterator &x) { *this = x; }
		~map_iterator() {}

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

		value_type &operator*() const { return (&_node->value); }
		value_type *operator->() const { return (_node->value); }

		iterator &operator++()
		{
			btree *last = this->_node;

			if (_node->right) {
				_node = _node->right;
				while(_node->left)
					_node = _node->left;
			}
			// else if (_node->left){
			// 	while(_node->left)
			// 		_node = _node->left;
			// }
			else{
				_node = _node->parent;
				while (_node && _node->right == last) {
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
			// else if (_node->left){
			// 	while(_node->left)
			// 		_node = _node->left;
			// }
			else{
				_node = _node->parent;
				while (_node && _node->left == last) {
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

		btree *	getNode(){
			return (this->_node);
		}

	private:
		btree *_node;
	};
}

#endif