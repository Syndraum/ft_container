#ifndef ALLOCATOR_HPP
# define ALLOCATOR_HPP

#include <cmath>

#if _WIN32 || _WIN64
# if _WIN64
#  define ENVIRONMENT 64
# else
#  define ENVIRONMENT 32
# endif
#endif

#if __GNUC__
# if __x86_64__ || __ppc64__
#  define ENVIRONMENT 64
# else
#  define ENVIRONMENT 32
# endif
#endif

#ifndef ENVIRONMENT
# define ENVIRONMENT 32
#endif

namespace ft{
	template < typename T >
	class allocator
	{
	private:
		/* data */
	public:
		allocator () throw() {}
		allocator (const allocator& alloc) throw() {(void)alloc;}
		template <class U>
		allocator (const allocator<U>& alloc) throw() {(void)alloc;}
		~allocator()throw() {}

		typedef T										value_type;
		typedef value_type*								pointer;
		typedef value_type&								reference;
		typedef const value_type*						const_pointer;
		typedef const value_type&						const_reference;
		typedef std::ptrdiff_t							difference_type;
		typedef size_t									size_type;
		template <class U> struct rebind { typedef allocator<U> other; };

		pointer address ( reference x ) const {
			return (&x);
		}

		const_pointer address ( const_reference x ) const {
			return (&x);
		}

		pointer allocate (size_type n) {
			pointer p = 0;
			p = reinterpret_cast<pointer>(::operator new (sizeof(value_type) * n));
			return p;
		}

		void deallocate (pointer p) {
			::operator delete(p);
		}

		size_type max_size() const throw() {
			unsigned long long n = ((pow(2, ENVIRONMENT) - 1.0) / sizeof(T));
			return (n);
		}

		void construct ( pointer p, const_reference val ) {
			new ((void*)p) value_type (val);
		}

		void destroy (pointer p) {
			((T*)p)->~T();
		}
	};

	template <> class allocator<void> {
	public:
	typedef void* pointer;
	typedef const void* const_pointer;
 	typedef void value_type;
	template <class U> struct rebind { typedef allocator<U> other; };
};
	
}

#endif