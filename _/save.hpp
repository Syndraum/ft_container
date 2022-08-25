/* ================= LOG =================
 * 16 August :
 *	ADD
 *	- reverse iterator class
 *	- rbegin(), rend()
 *	- stack class
 *	- pair struct
 *	- make_pair
 *	UPDATE
 *	- insert()
 *
 * 14 August :
 * ADD
 * 	- vector constructor
 *	- operator=()
 *
 * 13 August :
 * ADD
 *	- iterator_traits
 *	- is_integral
 *	- enable_if
 *	- assign()
 *	- resize()
 *	- insert()
 *	- erase()
 *	- swap()
*/

//============================================================================
// iterator_traits.hpp
//============================================================================

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft {
    template <typename T>
    struct iterator_traits
    {
        typedef typename T::iterator_category iterator_category;
        typedef typename T::value_type value_type;
        typedef typename T::difference_type difference_type;
        typedef typename T::pointer pointer;
        typedef typename T::reference reference;
    };

    template <typename T>
    struct iterator_traits<T*>
    {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
    };

    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;
    };
}

#endif // ITERATOR_TRAIT_HPP

//============================================================================
// utils.hpp
//============================================================================

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft {

// ========== IS_INTEGRAL ===========
	template <typename T, T val>
	struct integral_constant
	{
		static const T value = val;
	};

	struct false_type : public integral_constant<bool, false> {};
	struct true_type : public integral_constant<bool, true> {};

	template <class T>
	struct is_integral : public false_type {};
	template <>
	struct is_integral<int> : public true_type {};
	template <>
	struct is_integral<unsigned int> : public true_type {};
	template <>
	struct is_integral<bool> : public true_type {};
	template <>
	struct is_integral<char> : public true_type {};
	template <>
	struct is_integral<unsigned char> : public true_type {};
	template <>
	struct is_integral<signed char> : public true_type {};
	template <>
	struct is_integral<short> : public true_type {};
	template <>
	struct is_integral<unsigned short> : public true_type {};
	template <>
	struct is_integral<long> : public true_type {};
	template <>
	struct is_integral<unsigned long> : public true_type {};
	template <>
	struct is_integral<long long> : public true_type {};
	template <>
	struct is_integral<unsigned long long> : public true_type {};

// ========= ENABLE_IF =========
	template<bool B, typename T = void>
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

// ========== DISTANCE =========
	template<typename InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
    distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type n = 0;

		for (; first != last; ++first)
			++n;
		return (n);
	}

// =========== SWAP ===========
	template <class T> void swap ( T& a, T& b )
	{
		T c(a);
		a=b;
		b=c;
	}

}
#endif

//============================================================================
// vector.hpp
//============================================================================

// ========= CONSTRUCTORS =========

// fill
vector(
	size_type n,
	const value_type &val = value_type(),
	const allocator_type& alloc = allocator_type()
	) : 
		_size(0), 
		_capacity(get_fit_capacity(n)), 
		_allocator(alloc), 
		_data(_allocator.allocate(_capacity))
{
	insert(begin(), n, val);
}

// range
template <typename InputIterator>
vector (
	InputIterator first,
	typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last,
	const allocator_type& alloc = allocator_type()
	) : 
		_size(0), 
		_capacity(get_fit_capacity(ft::distance< InputIterator >(first, last))), 
		_allocator(alloc), 
		_data(_allocator.allocate(_capacity))
{
	insert(begin(), first, last);
}

// copy
vector (const vector& x) : _size(0), _capacity(x._capacity), _allocator(x._allocator), _data(_allocator.allocate(_capacity))
{
	insert(begin(), x.begin(), x.end());
}

// ========= DESTRUCTOR ========

~vector(void)
{
	clear();
	_allocator.deallocate(_data, _capacity);
}

// ========== ASSIGNMENT OPERATOR =========

vector& operator= (const vector& x)
{
	if (this != &x)
    {
		clear();
		_allocator.deallocate(_data, _capacity);
		_size = 0;
		_capacity = x._capacity;
		_allocator = x._allocator;
		_data = _allocator.allocate(_capacity);
		insert(begin(), x.begin(), x.end());
	}
	return (*this);
}

// ========== RBEGIN, REND ==========

reverse_iterator rbegin()
{
	return (reverse_iterator(_data[size()]));
}

const_reverse_iterator rbegin() const
{
	return(rbegin());
}

reverse_iterator rend()
{
	return(reverse_iterator(_data[0]));
}

const_reverse_iterator rend() const
{
	return(rend());
}

// ========= RESIZE =========

void		resize (size_type n, value_type val = value_type())
{
	reserve(n);
	if (n < _size)
	{
		for (size_type i = n; i < _size; i++)
			_allocator.destroy(_data + i);
	}
	else
	{
		for (size_type i = _size; i < n; i++)
			_allocator.construct(_data + i, val);
	}
	_size = n;
}

//	UPDATE ! optimization !

void		resize (size_type n, value_type val = value_type())
{
	reserve(n);
	for (size_type i = n; i < _size; i++)
		_allocator.destroy(_data + i);
	for (size_type i = _size; i < n; i++)
		_allocator.construct(_data + i, val);
	_size = n;
}

// ========= ASSIGN =========

template <class InputIterator>
void		assign (
		InputIterator first,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last
	)
{
	size_type n = ft::distance(first, last);
	size_type i = 0;

	clear();
	reserve(n);
	for (; first != last; first++)
	{
		_allocator.construct(_data + n, *first);
		i++;
	}
	_size = n;
}

void assign (size_type n, const value_type& val)
{
	clear();
	reserve(n);
	for (size_type i = 0; i < n; i++)
		_allocator.construct(_data + i, val);
	_size = n;
}

// ========= INSERT =========

iterator insert (iterator position, const value_type& val)
{
	difference_type	idx_position = position - begin();

	insert(position, 1, val);
	return (begin() + idx_position);
}

void insert (iterator position, size_type n, const value_type& val)
{
	size_type idx_position = position - begin();

	reserve(_size + n);
	position = begin() + idx_position;
	for (iterator ite = end() - 1; ite != position - 1; ite--)
	{
		_allocator.construct(&*(ite + n), *ite);
		_allocator.destroy(&(*ite));
	}
	for (size_type i = 0; i < n; i++)
		_allocator.construct(&*(position + i), val);
	_size += n;
}

template <class InputIterator>
void insert (
	iterator position,
	InputIterator first,
	typename enable_if <!is_integral <InputIterator>::value, InputIterator >::type last
	)
{
	size_type n = ft::distance(first, last);
	size_type idx_position = position - begin();

	reserve(_size + n);
	position = begin() + idx_position;
	for (iterator ite = end() - 1; ite != position - 1; ite--)
	{
		_allocator.construct(&*(ite + n), *ite);
		_allocator.destroy(&(*ite));
	}
	for (InputIterator it = first; it != last; it++)
	{
		_allocator.construct(&*(position), *it);
		position++;
	}
	_size += n;
}

// ========= ERASE =========

iterator erase (iterator position)
{
	return (erase(position, position + 1));
}

iterator erase (iterator first, iterator last)
{
	size_type n = last - first;
	size_type i = 0;

	for (iterator it = first; it != last; it++)
		_allocator.destroy(&(*it));
	for (iterator it = last; it != end(); it++)
	{
		_allocator.construct(&(*first) + i, *it);
		_allocator.destroy(&(*it));
		i++;
	}
	_size -= n;
	return (first);
}

// =========== SWAP ===========

void swap (vector& x)
{
	ft::swap(_size, x._size);
	ft::swap(_capacity, x._capacity);
	ft::swap(_allocator, x._allocator);
	ft::swap(_data, x._data);
}

// =========== EXTERN SWAP ===========

template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
{
	x.swap(y);
}

//============================================================================
// reverse_iterator.hpp
//============================================================================


#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"
namespace ft {
	template < typename Iterator >
	class reverse_iterator
	{
	public:
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;

		reverse_iterator() : _base_it(iterator_type()) {}
		explicit reverse_iterator (iterator_type it) : _base_it(it) {}
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base_it(rev_it.base()) {}
		~reverse_iterator() {}

		iterator_type	base() const
		{
			return (_base_it);
		}

		reference		operator*() const
		{
			iterator_type tmp = _base_it;
			return (*(--tmp));
		}

		reverse_iterator operator+ (difference_type n) const
		{
			return (reverse_iterator(_base_it - n));
		}

		reverse_iterator& operator++()
		{
			--_base_it;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return tmp;
		}

		reverse_iterator& operator+= (difference_type n)
		{
			_base_it -= n;
			return(*this);
		}

		reverse_iterator operator- (difference_type n) const
		{
			return ( reverse_iterator(_base_it + n));
		}

		reverse_iterator& operator--()
		{
			++_base_it;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return tmp;
		}

		reverse_iterator& operator-= (difference_type n)
		{
			_base_it += n;
			return(*this);
		}

		pointer operator->() const
		{
			iterator_type	tmp(_base_it);
			tmp--;
			return(tmp.operator->());
		}

		reference operator[] (difference_type n) const
		{
			return (base()[-n-1]);
		}

	private:
		iterator_type	_base_it;
	};

	template <typename Iterator1, typename Iterator2>
	bool operator== (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator!= (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator< (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator> (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator<= (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename Iterator1, typename Iterator2>
	bool operator>= (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& rev_it)
	{
			return (rev_it + n);
	}

	template <typename Iterator1, typename Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator- (
		const reverse_iterator<Iterator1>& lhs,
		const reverse_iterator<Iterator2>& rhs)
	{
			return((rhs.base() - lhs.base()));
	}
}

#endif

//============================================================================
// stack.hpp
//============================================================================

#ifndef STACK_HPP
# define STACK_HPP

#include "vector.hpp"

namespace ft {
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef std::size_t	size_type;

		explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}

		bool empty() const
		{
			return (c.empty());
		}

		size_type size() const
		{
			return (c.size());
		}

		value_type& top()
		{
			return (c.back());
		}

		const value_type& top() const
		{
			return (c.back());
		}

		void push (const value_type& val)
		{
			c.push_back(val);
		}

		void pop()
		{
			c.pop_back();
		}
	
	protected:
		Container	c;
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif

//============================================================================
//================================   MAP   ===================================
//============================================================================

//============================================================================
// pair.hpp
//============================================================================

template <class T1, class T2>
struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;

	pair() : first(), second() {}
	template <class U, class V>
	pair(const pair<U,V>& p) : first(p.first), second(p.second) {}
	pair(const first_type& a, const second_type& b) : first(a), second(b) {}

	first_type	first;
	second_type	second;
};

template <class T1,class T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{
	return ( pair<T1,T2>(x,y) );
}

//============================================================================
// btree_node.hpp
//============================================================================

#ifndef BTREE_NODE_HPP
# define BTREE_NODE_HPP

namespace ft
{
	template <typename T>
	struct btree_node
	{
		typedef T	value_type;

		btree_node() : value(NULL), parent(NULL), left(NULL), right(NULL) {}
		btree_node(const value_type& val) : value(val.value), parent(NULL), left(NULL), right(NULL) {}

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
		btree_node	*left;
		btree_node	*right;
		btree_node	*parent;
	};
	
}

#endif

//============================================================================
// map.hpp
//============================================================================

#include <memory>
#include "pair.hpp"
#include "btree_node.hpp"

namespace ft
{
	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Alloc = std::allocator<ft:pair<const Key, T> >
	>
	class map
	{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft:pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		// typedef ft::map_iterator<value_type>				iterator;
		// typedef ft::map_iterator<const value_type>			const_iterator;
		// typedef std::reverse_iterator<iterator>				reverse_iterator;
		// typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef typename std::ptrdiff_t						difference_type;
		typedef typename std::size_t						size_type;

		typedef btree_node<value_type>						node_type;

		// CONSTRUCTORS
		map(
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()
		) : _root(new node_type()), _sentinel(_root), _comp(comp), _allocator(alloc) {}

		// DESTRUCTOR
		~map()
		{
			clear();
			delete _sentinel;
		}

		// CAPACITY
		bool empty() const
		{
			if (_size)
				return (false);
			return (true);
		}

		size_type size() const
		{
			return (_size);
		}

		size_type max_size() const
		{
			return (_allocator.max_size());
		}

		// ELEMENT ACCESS
		mapped_type& operator[](const key_type& key)
		{
			return (insert(value_type(key, mapped_type())).first->second);
		}

		// MODIFIERS
		ft::pair<iterator,bool> insert(const value_type& val)
		{
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
			return (ft::pair<iterator, bool>(node , true));
		}

		void clear()
		{
			_suffix_apply(&map::_delete_node, _root);
			_root = _sentinel;
			_size = 0;
		}

		// OBSERVERS
		key_compare key_comp() const
		{
			return (_comp);
		}

		// ALLOCATOR
		allocator_type get_allocator() const
		{
			return (_allocator);
		}

	private:
		node_type *		_root;
		node_type *		_sentinel;
		size_type		_size;
		key_compare		_comp;
		allocator_type	_allocator;

		node_type *_create_node(const value_type& val, node_type *parent = NULL)
		{
			node_type *node = new node_type();
			node->value = _allocator.allocate(1);
			_allocator.construct(node->value, val);
			node->parent = parent;
			return (node);
		}

		void _destroy_node(node_type *node)
		{
			_allocator.destroy(node->value);
			_allocator.deallocate(node->value, 1);
			delete node;
		}

		void _set_child(node_type *parent, node_type *child)
		{
			if (_comp(parent->value->first, child->value->first))
				parent->set_right(child);
			else
				parent->set_left(child);
		}

		void	_suffix_apply(void (map::*func)(node_type*), node_type *node)
		{
			if (!node || node == _sentinel)
				return ;
			_suffix_apply(func, node->left);
			_suffix_apply(func, node->right);
			(this->*func)(node);
		}
}