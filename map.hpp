#ifndef MAP_HPP
# define MAP_HPP

#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include "btree.hpp"

namespace ft {
	template <
		typename Key,
		typename T,
		typename Compare = ft::less<Key>,
		typename Alloc = std::allocator<ft::pair<const Key,T> >
	>
	class map
	{
	public:
		
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef Compare									key_compare;
		typedef Alloc									allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef ft::map_iterator<value_type>			iterator;
		typedef ft::map_iterator<const value_type>		const_iterator;
		typedef ft::reverse_iterator< iterator >		reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;
		typedef ft::btree_node<value_type>				node_type;
		typedef ft::btree_node<const value_type>		const_node_type;

		struct value_compare : public ft::binary_function< value_type, value_type, bool>
		{
			friend class map;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}
			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		};

		map(
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _root(new node_type()), _sentinel(_root), _size(0), _comp(comp), _allocator(alloc) {}
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _root(new node_type()), _sentinel(_root), _size(0), _comp(comp), _allocator(alloc) {
				insert(first, last);
			}
		map (const map &x) : _root(new node_type()), _sentinel(_root), _size(0), _comp(x._comp), _allocator(x._allocator) {
			insert(x.begin(), x.end());
		}
		~map()
		{
			clear();
			delete _sentinel;
		}

		map& operator= (const map& x){
			if (this != &x) {
				clear();
				_root = _sentinel;
				_comp = x._comp;
				_allocator = x._allocator;
				insert(x.begin(), x.end());
			}
			return (*this);
		}

		iterator begin() {
			if (empty())
				return(end());
			return (iterator(_get_first()));
		}

		const_iterator begin() const {
			if (empty())
				return(end());
			return (const_iterator(reinterpret_cast<const_node_type *>(_get_first())));
		}

		iterator end() {
			return (iterator(_sentinel));
		}

		const_iterator end() const {
			if (empty())
				return(const_iterator());
			return (const_iterator(reinterpret_cast<const_node_type *>(_sentinel)));
		}

		reverse_iterator rbegin() {
			return (reverse_iterator(_sentinel));
		}

		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(_sentinel));
		}

		reverse_iterator rend() {
			return (reverse_iterator(_get_first()));
		}

		const_reverse_iterator rend() const {
			return (const_reverse_iterator(_get_first()));
		}

		bool empty() const {
			if (_size)
				return (false);
			return (true);
		}

		size_type size() const {
			return (_size);
		}

		size_type max_size() const {
			return (_allocator.max_size());
		}

		mapped_type& operator[] (const key_type& k)
		{
			return (insert(value_type(k)).first->second);
		}

		ft::pair<iterator,bool> insert(const value_type& val) {
			node_type	*cursor	= _root;
			node_type	*parent	= _root->parent;
			node_type	*node	= NULL;

			while (cursor && cursor != _sentinel)
			{
				if ( cursor->value->first == val.first)
					return (ft::pair<iterator,bool>(iterator(cursor), false));
				parent = cursor;
				if (key_compare()(val.first, cursor->value->first))
					cursor = cursor->left;
				else 
					cursor = cursor->right;
			}
			node = _create_node(val, parent);
			if (empty())
				_root = node;
			else
				_set_child(parent, node);
			if (cursor == _sentinel)
				node->set_right(_sentinel);
			_size++;
			_balance(node);
			return (ft::pair<iterator, bool>(node , true));
		}

		iterator insert (iterator position, const value_type& val) {
			iterator it;

			(void)position;
			it = insert(val).first;
			return (it);
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			for (InputIterator it = first; it != last; it++)
				insert(ft::make_pair(it->first, it->second));
		}

		void erase (iterator position) {
			node_type *to_erase	= position.getNode();
			node_type *parent	= to_erase->parent;
			node_type *pivot	= NULL;

			if (to_erase->left) {
				pivot = to_erase->left;
				if (to_erase->right && to_erase->right != _sentinel){
					node_type *cursor = pivot;
					while (cursor->right) {
						cursor = cursor->right;
					}
					cursor->right = to_erase->right;
					cursor->right->parent = cursor;
				}
			}
			else if (to_erase->right && to_erase->right != _sentinel)
				pivot = to_erase->right;
			if (parent) {
				if (parent->left == to_erase)
					parent->left = pivot;
				else
					parent->right = pivot;
			}
			else {
				_root = pivot;
				if (pivot)
					pivot->parent = NULL;
			}
			_set_child(parent, pivot);
			if (to_erase->right == _sentinel) {
				if (pivot)
					pivot->set_right(_sentinel);
				else if (parent)
					parent->set_right(_sentinel);
				else {
					_root = _sentinel;
					_sentinel->parent = NULL;
				}
			}
			_delete_node(to_erase);
			if (pivot)
				_balance(pivot);
			else if (parent)
				_balance(parent);
			_size--;
		}

		size_type erase (const key_type& k) {
			iterator it = find(k);

			if(it == end())
				return (0);
			erase(it);
			return (1);
		}

		void erase (iterator first, iterator last) {
			iterator next = first;

			for (iterator it = first; it != last; it = next)
			{
				next++;
				this->erase(it);
			}
		}

		void swap (map& x) {
			ft::swap(_root, x._root);
			ft::swap(_sentinel, x._sentinel);
			ft::swap(_size, x._size);
			ft::swap(_comp, x._comp);
			ft::swap(_allocator, x._allocator);
		// 	if (this->_root.left)
		// 		this->_root.left->parent = &this->_root;
		// 	if (x._root.left)
		// 		x._root.left->parent = &x._root;
		}

		void clear()
		{
			_suffix_apply(&map::_delete_node, _root);
			_sentinel->parent = NULL;
			_root = _sentinel;
			_size = 0;
		}

		key_compare key_comp() const
		{
			return (_comp);
		}

		value_compare value_comp() const {
			return (value_compare(_comp));
		}

		iterator find (const key_type& k) {
			node_type	*cur = _root;

			while (cur && cur != _sentinel) {
				if (key_compare()(k, cur->value->first))
					cur = cur->left;
				else if (key_compare()( cur->value->first, k))
					cur = cur->right;
				else
					return (iterator(cur));
			}
			return (end());
		}

		const_iterator find (const key_type& k) const {
			node_type	*cur = _root;

			while (cur && cur != _sentinel) {
				if (key_compare()(k, cur->value->first))
					cur = cur->left;
				else if (key_compare()( cur->value->first, k))
					cur = cur->right;
				else
					return (const_iterator(reinterpret_cast<const_node_type *>(cur)));
			}
			return (end());
		}

		size_type count (const key_type& k) const {
			if (find(k) == end())
				return (0);
			return (1);
		}
		
		iterator lower_bound (const key_type& k) {
			iterator it = begin();

			while (it != end() && key_comp()(it->first, k))
				it++;
			return (it);
		}

		const_iterator lower_bound (const key_type& k) const {
			const_iterator it = begin();

			while (it != end() && key_comp()(it->first, k))
				it++;
			return (it);
		}

		iterator upper_bound (const key_type& k) {
			iterator it = begin();

			while (it != end() && !key_comp()(k, it->first))
				it++;
			return (it);
		}

		const_iterator upper_bound (const key_type& k) const {
			const_iterator it = begin();

			while (it != end() && !key_comp()(k, it->first))
				it++;
			return (it);
		}

		pair<iterator,iterator>	equal_range (const key_type& k)
		{
			iterator it = begin();

			while (it != end() && (key_comp()(it->first, k)))
				it++;
			if (it == end() || key_comp()(k, it->first))
				return (pair<iterator, iterator>(it, it));
			iterator upper = it;
			return (pair<iterator, iterator>(it, ++upper));
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			const_iterator it = begin();

			while (it != end() && (key_comp()(it->first, k)))
				it++;
			if (it == end() || key_comp()(k, it->first))
				return (pair<const_iterator, const_iterator>(it, it));
			const_iterator upper = it;
			return (pair<const_iterator, const_iterator>(it, ++upper));
		}

		//
		void debug() {
			_printTree(_root, "", true);
			_sanitaze(_root, NULL);
		}

	private:
		node_type *		_root;
		node_type *		_sentinel;
		size_type		_size;
		key_compare		_comp;
		allocator_type	_allocator;

		// template < typename Function >
		// void	_apply(Function func, node_type *node) {
		// 	if (node) {
		// 		_apply(func, node->left);
		// 		func(*node);
		// 		_apply(func, node->right);
		// 	}
		// }

		void	_suffix_apply(void (map::*func)(node_type*), node_type *node)
		{
			if (!node || node == _sentinel)
				return ;
			_suffix_apply(func, node->left);
			_suffix_apply(func, node->right);
			(this->*func)(node);
		}

		node_type *_create_node(const value_type& val, node_type *parent = NULL)
		{
			node_type *node = new node_type();
			node->value = _allocator.allocate(1);
			_allocator.construct(node->value, val);
			node->parent = parent;
			return (node);
		}

		// node_type *create_node(const key_type &key, const mapped_type &value = mapped_type()) {
		// 	node_type *node = new node_type();
		// 	node->value = _allocator.allocate(1);
		// 	_allocator.construct(node->value, value_type(key, value));
		// 	return (node);
		// }

		// node_type *create_node(const key_type &key, node_type *parent, const mapped_type &value = mapped_type()) {
		// 	node_type *node = new node_type();
		// 	node->value = _allocator.allocate(1);
		// 	_allocator.construct(node->value, value_type(key, value));
		// 	node->parent = parent;
		// 	return (node);
		// }
		
		// void	destroy_pair(node_type *node){
		// 	_allocator.destroy(node->value);
		// }

		void	_delete_node(node_type *node){
			_allocator.destroy(node->value);
			_allocator.deallocate(node->value, 1);
			delete(node);
		}

		void _set_child(node_type *parent, node_type *child)
		{
			if (!child)
				return ;
			if (!parent)
				child->parent = NULL;
			else if (_comp(parent->value->first, child->value->first))
				parent->set_right(child);
			else
				parent->set_left(child);
		}

		node_type	*_get_first() const
		{
			node_type *node = _root;

			while (node->left)
				node = node->left;
			return (node);
		}

		// node_type	*_last() const {
		// 	node_type *node = _root->left;
		// 	while (node->right)
		// 		node = node->right;
		// 	return (node);
		// }

		// const	node_type& getRoot(){
		// 	return(*_root);
		// }

		void _printTree(node_type *root, std::string indent, bool last) {
			if (root != NULL && root != _sentinel) {
				std::cout << indent;
				if (last) {
				std::cout << "R----";
				indent += "   ";
				} else {
				std::cout << "L----";
				indent += "|  ";
				}
				std::cout << root->value->first << std::endl;
				_printTree(root->left, indent, false);
				_printTree(root->right, indent, true);
			}
		}

		size_t	_get_height(node_type *node) {
			size_t	left	= 0;
			size_t	right	= 0;

			if (!node || node == _sentinel)
				return (0);
			left = 1 + _get_height(node->left);
			right = 1 + _get_height(node->right);
			return (std::max(left, right));
		}

		int		_get_diff_height(node_type *node) {
			return (_get_height(node->left) - _get_height(node->right));
		}

		void	_balance(node_type *node) {
			int diff_height = 0;

			while (node) {
				diff_height = _get_diff_height(node);
				if (diff_height > 1) {
					if (_get_diff_height(node->left) < 0)
						_left_rotate(node->left);
					_right_rotate(node);
				}
				else if (diff_height < -1) {
					if (_get_diff_height(node->right) > 0)
						_right_rotate(node->right);
					_left_rotate(node);
				}
				node = node->parent;
			}
			while (_root->parent) {
				_root = _root->parent;
			}
		}

		void _sanitaze(node_type * node, node_type *parent) {

			if (!node)
				return;
			_sanitaze(node->left, node);
			if (node == _sentinel)
				std::cout << "Sentinel";
			else
				std::cout << node->value->first;
			std::cout << " -> ";
			if (node->parent)
				std::cout << node->parent->value->first;
			else
				std::cout << "NULL";
			std::cout << " " << (node->parent == parent) << std::endl;
			_sanitaze(node->right, node);
		}

		void	_left_rotate(node_type *node) {
			node_type * pivot	= node->right;
			node_type * tmp		= pivot->left;

			node->right = tmp;
			if (tmp)
				tmp->parent = node;
			_set_child(node->parent, pivot);
			_set_child(pivot, node);
		}

		void	_right_rotate(node_type *node) {
			node_type * pivot	= node->left;
			node_type * tmp		= pivot->right;

			node->left = tmp;
			if (tmp)
				tmp->parent = node;
			_set_child(node->parent, pivot);
			_set_child(pivot, node);
		}
	};

	template< class Key, class T, class Compare, class Alloc >
	bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		typename map<Key, T, Compare>::const_iterator rit = rhs.begin();

		if (lhs.size() != rhs.size())
			return (false);
		for (typename ft::map<Key, T, Compare>::const_iterator lit = lhs.begin(); lit != lhs.end(); lit++)
		{
			if (*lit != *rit)
				return (false);
			rit++;
		}
		return (true);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	void swap (map<T,Alloc>& x, map<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif