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
        typedef std::ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;
    };

    template <typename T>
    struct iterator_traits<const T*>
    {
        typedef std::random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;
    };
}

#endif // ITERATOR_TRAIT_HPP
