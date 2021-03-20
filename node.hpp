#ifndef NODE_HPP
# define NODE_HPP

namespace ft {
	template <typename T>
	struct node
	{
	private:
	public:
		node(void) : data(T()), previous(0), next(0) {}
		node(const T & data) : data(data), previous(0), next(0) {}
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
			// node< const T > new_node(this->data)
			return node<const T>(const_cast< T& >(this->data));
		}

		T		data;
		node *	previous;
		node *	next;
	};
}

#endif