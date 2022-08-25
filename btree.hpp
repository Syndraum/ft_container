#ifndef BTREE_HPP
# define BTREE_HPP

namespace ft{
	template <typename T>
	struct btree_node
	{
		typedef T	value_type;

		btree_node() : value(NULL), left(NULL), right(NULL), parent(NULL) {}
		btree_node(const btree_node &x) : value(x.value), left(x.left), right(x.right), parent(x.parent) {}

		void set_left (btree_node<T>* l)
		{
			left = l;
			if (l)
				l->parent = this;
		}

		void set_right(btree_node<T>* n)
		{
			right = n;
			if (n)
				n->parent = this;
		}

		value_type	*value;
		btree_node		*left;
		btree_node		*right;
		btree_node		*parent;
	};
}

#endif