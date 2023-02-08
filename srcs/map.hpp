#ifndef MAP_HPP
# define MAP_HPP

# include "../includes/ft_containers.hpp"
# include "../includes/pair.hpp"
# include "../includes/reverse_iterator.hpp"
# include "../includes/rbt.hpp"

namespace	ft {

	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class	map {

		public:

			/*** MEMBER TYPES ***/

			typedef Key												key_type;
			typedef T												mapped_type;
			typedef typename ft::pair<const Key, T>					value_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Compare											key_compare;
			typedef Allocator										allocator_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef T*												iterator;
			typedef const T*										const_iterator;
			typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef typename ft::rbt<value_type, value_compare>		rbt;

			/*** MEMBER CLASSES ***/

			class	value_compare:
				public std::binary_function<value_type, value_type, bool> {

					friend class	map;

					public:

						/*** MEMBER TYPES ***/

						typedef bool		result_type;
						typedef value_type	first_argument_type;
						typedef value_type	second_argument_type;

						/*** MEMBER FUNCTIONS ***/

						bool	operator()(const first_argument_type &lhs, const second_argument_type &rhs) const {
							return (comp(lhs.first, rhs.first));
						}

					protected:

						/*** MEMBER OBJECTS ***/

						key_compare	comp;

						/*** MEMBER FUNCTIONS ***/

						value_compare(key_compare c):
							comp(c) {}

			};

			/*** MEMBER FUNCTIONS ***/

			// map() {}

			// explicit map(const key_compare &comp, const allocator_type &alloc = Allocator()) {}

			// template<class InputIt>
			// map(InputIt first, InputIt last, const key_compare &comp = Compare(), const allocator_type &alloc = Allocator()) {}

			// map(const map &other) {}

		private:

			value_compare	_comp;
			allocator_type	_a;
			pointer			_first;

	};

};

#endif
