#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_containers.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft {

	template <class T, class Allocator = std::allocator<T>>
	class	vector {

		public:

			/*** MEMBER TYPES ***/

			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef std::size_t											size_type;
			typedef std::ptrdiff_t										difference_type;
			typedef value_type&											reference;
			typedef const value_type&									const_reference;
			typedef typename allocator_type::pointer					pointer;
			typedef typename allocator_type::const_pointer				const_pointer;
			typedef typename ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/*** MEMBER FUNCTIONS ***/

			vector() {}

			explicit vector(const Allocator &alloc) {}

			explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator()) {}

			template <class InputIt>
			vector(InputIt first, InputIt last, const Allocator &alloc = Allocator()) {}

			vector(const vector &other) {}
		
		private:

			/*** MEMBER TYPES ***/

			allocator_type	_alloc;
			size_type		_count;
			size_type		_capacity;
			pointer			_first;
			pointer			_last;

	};

};

#endif
