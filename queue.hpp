#ifndef QUEUE_HPP
# define QUEUE_HPP

#include "list.hpp"

namespace ft {
	template <class T, class Container = ft::list<T> >
	class queue {
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef std::size_t	size_type;

		Container	c;

		explicit queue (const container_type& ctnr = container_type()) : c(ctnr) {}

		bool empty() const {
			return (c.empty());
		}

		size_type size() const {
			return (c.size());
		}

		value_type& front() {
			return (c.front());
		}

		const value_type& front() const {
			return (c.front());
		}

		value_type& back() {
			return (c.back());
		}

		const value_type& back() const {
			return (c.back());
		}

		void push (const value_type& val) {
			c.push_back(val);
		}

		void pop() {
			c.pop_front();
		}
	};

	template <class T, class Container>
	bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Container>
	bool operator< (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator> (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (!(rhs < lhs));
	}

	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs) {
		return (!(lhs < rhs));
	}
}

#endif