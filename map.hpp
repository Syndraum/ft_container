#ifndef MAP_HPP
# define MAP_HPP

#include "iterator.hpp"
#include "map_iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include "allocator.hpp"
#include "btree.hpp"

namespace ft {
	template <
		typename Key,
		typename T,
		typename Compare = ft::less<Key>,
		typename Alloc = ft::allocator<ft::pair<const Key,T> >
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
		typedef ft::btree<value_type>					btree_type;
		typedef ft::btree<const value_type>				const_btree_type;

		struct value_compare : public ft::binary_function< value_type, value_type, bool>
		{
			protected:
				Compare _comp;
			public:
				value_compare(Compare comp) : _comp(comp) {}
				bool operator() (const value_type& x, const value_type& y) const {
					return _comp(x.first, y.first);
				}
		};

		map(
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _root(btree_type()), _size(0), _comp(comp), _allocator(alloc) {}
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _root(btree_type()), _size(0), _comp(comp), _allocator(alloc) {
				insert(first, last);
			}
		~map() {
			clear();
		}

		map& operator= (const map& x){
			if (this != &x) {
				this->clear();
				this->_comp = x._comp;
				this->_allocator = x._allocator;
				this->insert(x.begin(), x.end());
			}
			return (*this);
		}

		iterator begin() {
			if (empty())
				return(end());
			return (iterator(_first()));
		}

		const_iterator begin() const {
			if (empty())
				return(end());
			return (const_iterator(reinterpret_cast<const_btree_type *>(_first())));
		}

		iterator end() {
			return (iterator(_root));
		}

		const_iterator end() const {
			if (empty())
				return(const_iterator());
			return (const_iterator(reinterpret_cast<const_btree_type *>(_root.left->parent)));
		}

		reverse_iterator rbegin() {
			return (reverse_iterator(_root));
		}

		const_reverse_iterator rbegin() const {
			return (const_reverse_iterator(_root));
		}

		reverse_iterator rend() {
			return (reverse_iterator(_first()));
		}

		const_reverse_iterator rend() const {
			return (const_reverse_iterator(_first()));
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

		mapped_type& operator[] (const key_type& k) {
			return (insert(value_type(k)).first->second);
		}

		ft::pair<iterator,bool> insert(const value_type& val) {
			btree_type	*cursor = _root.left;
			btree_type	*last = &_root;
			bool		is_exist = true;

			while (cursor && cursor->value->first != val.first)
			{
				last = cursor;
				if (key_compare()(val.first, cursor->value->first))
					cursor = cursor->left;
				else 
					cursor = cursor->right;
			}
			if (!cursor) {
				btree_type *node = create_node(val.first, last, val.second);
				if (last == &_root) {
					last->left = node;
					last->right = node;
				}
				else if (key_compare()(val.first, last->value->first))
					last->left = node;
				else
					last->right = node;
				cursor = node;
				is_exist = false;
				_size++;
			}
			return (ft::pair<iterator, bool>(cursor ,!is_exist));
		}

		iterator insert (iterator position, const value_type& val) {
			iterator last = &_root;
			iterator tmp;

			while (position != this->end() && tmp != position)
			{
				tmp = last;
				last = position;
				if (this->key_comp()(val.first, position->first))
					position--;
				else if (this->key_comp()(position->first, val.first))
					position++;
				else
					return (position);
			}
			btree_type *node = create_node(val.first, val.second);
			if (position == last){
				position.getNode()->left = node;
				position.getNode()->right = node;
			}
			else {
				if (position == this->end())
					ft::swap(position, last);
				if (this->key_comp()(val.first, position->first)) {
					if (position.getNode()->left)
						(--position).getNode()->right = node;
					else
						position.getNode()->left = node;
				}
				else{
					if (position.getNode()->right)
						(++position).getNode()->left = node;
					else
						position.getNode()->right = node;
				}
			}
			node->parent = position.getNode();
			_size++;
			return (iterator(node));
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			iterator last_insert = this->begin();

			for (InputIterator it = first; it != last; it++)
				last_insert = this->insert(last_insert, *it);
		}

		void erase (iterator position) {
			btree_type *to_erase = position.getNode();
			btree_type *parent = to_erase->parent;
			btree_type *pivot = 0;

			if (to_erase->left) {
				pivot = to_erase->left;
				if (to_erase->right){
					btree_type *cursor = pivot;
					while (cursor->right)
						cursor = cursor->right;
					cursor->right = to_erase->right;
					cursor->right->parent = cursor;
				}
			}
			else if (to_erase->right)
				pivot = to_erase->right;
			if (pivot)
				pivot->parent = parent;
			if (parent == &_root){
				parent->left = pivot;
				parent->right = pivot;
			}
			else if (parent->left == to_erase)
				parent->left = pivot;
			else
				parent->right = pivot;
			this->delete_node(to_erase);
			_size--;
		}

		size_type erase (const key_type& k) {
			iterator it = this->find(k);
			this->erase(it);
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
			ft::swap(this->_size, x._size);
			ft::swap(this->_comp, x._comp);
			ft::swap(this->_allocator, x._allocator);
			ft::swap(this->_root.left, x._root.left);
			ft::swap(this->_root.right, x._root.right);
			if (this->_root.left)
				this->_root.left->parent = &this->_root;
			if (x._root.left)
				x._root.left->parent = &x._root;
		}

		void clear() {
			if (this->empty())
				return ;
			_apply_suffix(&map::delete_node, _root.left);
			_root.left = 0;
			_root.right = 0;
			_size = 0;
		}

		key_compare key_comp() const {
			return (_comp);
		}

		value_compare value_comp() const {
			return (value_compare(_comp));
		}

		iterator find (const key_type& k) {
			btree_type	*cursor = _root.left;

			while (cursor) {
				if (key_compare()(k, cursor->value->first))
					cursor = cursor->left;
				else if (key_compare()( cursor->value->first, k))
					cursor = cursor->right;
				else
					return (iterator(cursor));
			}
			return (end());
		}

		const_iterator find (const key_type& k) const {
			btree_type	*cursor = _root.left;

			while (cursor) {
				if (key_compare()(k, cursor->value->first))
					cursor = cursor->left;
				else if (key_compare()( cursor->value->first, k))
					cursor = cursor->right;
				else
					return (const_iterator(reinterpret_cast<const_btree_type *>(cursor)));
			}
			return (end());
		}

		size_type count (const key_type& k) const {
			if (this->find(k) != end())
				return (1);
			return (0);
		}
		
		iterator lower_bound (const key_type& k) {
			iterator it = this->begin();

			while (it != this->end() && this->key_comp()(it->first, k))
				it++;
			return (it);
		}

		const_iterator lower_bound (const key_type& k) const {
			const_iterator it = this->begin();

			while (it != this->end() && this->key_comp()(it->first, k))
				it++;
			return (it);
		}

		iterator upper_bound (const key_type& k) {
			iterator it = this->begin();

			while (it != this->end() && !this->key_comp()(k, it->first))
				it++;
			return (it);
		}

		const_iterator upper_bound (const key_type& k) const {
			const_iterator it = this->begin();

			while (it != this->end() && !this->key_comp()(k, it->first))
				it++;
			return (it);
		}

		pair<iterator,iterator>	equal_range (const key_type& k) {
			iterator it = this->begin();

			while (it != this->end() && (this->key_comp()(k, it->first) || this->key_comp()(it->first, k)))
				it++;
			iterator upper = it;
			return (pair<iterator, iterator>(it, ++upper));
		}

		pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			const_iterator it = this->begin();

			while (it != this->end() && (this->key_comp()(k, it->first) || this->key_comp()(it->first, k)))
				it++;
			iterator upper = it;
			return (pair<const_iterator, const_iterator>(it, ++upper));
		}

	private:
		btree_type		_root;
		size_type		_size;
		key_compare		_comp;
		allocator_type	_allocator;

		static void	_print_node(btree_type &node) {
			std::cout << node.value->first << " ==> " << node.value->second << "\n";
		}

		template < typename Function >
		void	_apply(Function func, btree_type *node) {
			if (node) {
				_apply(func, node->left);
				func(*node);
				_apply(func, node->right);
			}
		}

		void	_apply_suffix(void (map::*func)(btree_type*), btree_type *node) {
			if (node) {
				_apply_suffix(func, node->left);
				_apply_suffix(func, node->right);
				(this->*func)(node);
			}
		}

		btree_type *create_node(const key_type &key, const mapped_type &value = mapped_type()) {
			btree_type *node = new btree_type();
			node->value = _allocator.allocate();
			_allocator.construct(node->value, value_type(key, value));
			return (node);
		}

		btree_type *create_node(const key_type &key, btree_type *parent, const mapped_type &value = mapped_type()) {
			btree_type *node = new btree_type();
			node->value = _allocator.allocate();
			_allocator.construct(node->value, value_type(key, value));
			node->parent = parent;
			return (node);
		}
		
		void	destroy_pair(btree_type *node){
			_allocator.destroy(node->value);
		}

		void	delete_node(btree_type *node){
			destroy_pair(node);
			_allocator.deallocate(node->value);
			delete(node);
		}

		btree_type	*_first() const {
			btree_type *node = _root.left;
			while (node->left)
				node = node->left;
			return (node);
		}

		btree_type	*_last() const {
			btree_type *node = _root.left;
			while (node->right)
				node = node->right;
			return (node);
		}

		const	btree_type& getRoot(){
			return(*_root);
		}
	};

	template <class T, class Alloc>
	void swap (map<T,Alloc>& x, map<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif