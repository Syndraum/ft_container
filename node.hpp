#ifndef NODE_HPP
# define NODE_HPP

namespace ft {
	template <typename T>
	struct node
	{
	private:
	public:
		node(void) : data(T()), previous(0), next(0) {}
		// node(T *x) : data(*x), previous(0), next(0) {}
		node(const T & data) : data(data), previous(0), next(0) {}
		node(T &x, node *previous, node *next) : data(x), previous(previous), next(next) {}
		~node(void) {}

		node &operator=(const node & x){
			if (this != &x){
				data = x.data;
				previous = x.previous;
				next = x.next;
			}
			return (*this);
		}

		operator node<const T>() {
			return node<const T>(this->data, reinterpret_cast<ft::node<const T> *>(previous), reinterpret_cast<ft::node<const T> *>(next));
		}

		T		data;
		node *	previous;
		node *	next;
	};
}

#endif