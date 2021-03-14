#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>

namespace ft {
	template <
		typename Category,
		typename T,
		typename Distance = std::ptrdiff_t,
		typename Pointer = T*,
		typename Reference = T& >
		class iterator {
		public:
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef Category	iterator_category;
		};

		struct output_iterator_tag {};
		struct input_iterator_tag {};
		struct forward_iterator_tag : public input_iterator_tag {};
		struct bidirectional_iterator_tag : public forward_iterator_tag {};
		struct random_access_iterator_tag : public bidirectional_iterator_tag {};
}
// namespace std {
// 	template < T >
// 	struct iterator_traits<ft::random_access_iterator_tag> {
// 		typedef typename Iterator::iterator_category iterator_category;
// 		typedef typename Iterator::value_type        value_type;
// 		typedef typename Iterator::difference_type   difference_type;
// 		typedef typename Iterator::pointer           pointer;
// 		typedef typename Iterator::reference         reference;
//   };
// }

#endif