#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_containers.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft {

	template <class T, class Allocator = std::allocator<T>>
	class	vector {

		public:

			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_tyoe::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			// typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			// typedef typename ft::reverse_iterator<const iterator>			const_reverse_iterator;

	};

};

#endif
