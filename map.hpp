#ifndef MAP_HPP
# define MAP_HPP

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
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef std::ptrdiff_t							difference_type;
		typedef std::size_t								size_type;
		typedef ft::btree<value_type>					btree_type;

		struct value_compare : public ft::binary_function< value_type, value_type, bool>
		{
			protected:
				Compare _comp;
				value_compare(Compare comp) : _comp(comp) {}
			public:
				bool operator() (const value_type& x, const value_type& y) const {
					return comp(x.first, y.first);
				}
		};

		map(
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _root(0), _size(0), _comp(comp), _allocator(alloc) {}
		~map() {}

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
			btree_type	*cursor = _root;
			btree_type	*last = 0;

			while (cursor && k != cursor->value->first){
				last = cursor;
				if (key_compare()(k, cursor->value->first))
					cursor = cursor->left;
				else 
					cursor = cursor->right;
			}
			if (!cursor){
				btree_type *node = new btree_type();
				value_type *pair = new value_type(k);
				node->value = pair;
				if (!last)
					_root = node;
				else if (key_compare()(k, last->value->first))
					last->left = node;
				else
					last->right = node;
				cursor = node;
			}
			return(cursor->value->second);
		}

		key_compare key_comp() const {
			return (_comp);
		}

		value_compare value_comp() const {
			return (value_compare(_comp));
		}


		void	print() {
			_apply(_print_node, _root);
		}

	private:
		btree_type		*_root;
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
	};
}

#endif