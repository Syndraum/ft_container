#ifndef NODE_HPP
# define NODE_HPP

namespace ft {
	template <typename T>
	struct node
	{
	private:
		node(void) : data(T()), previous(0), next(0) {}
	public:
		node(const T & data) : data(data), previous(0), next(0) {}
		~node(void) {}

		T		data;
		node *	previous;
		node *	next;
	};
}

#endif