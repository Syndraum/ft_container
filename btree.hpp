#ifndef BTREE_HPP
# define BTREE_HPP

#include "utils.hpp"

namespace ft{
	template <typename T>
	struct btree
	{
		typedef T	value_type;

		btree() : value(0), left(0), right(0), parent(0) {}
		btree(value_type *x) : value(x), left(0), right(0), parent(0) {}

		operator btree<const T>(){
			return(btree<const T>(value));
		}

		value_type	*value;
		btree		*left;
		btree		*right;
		btree		*parent;
	};
}

#endif