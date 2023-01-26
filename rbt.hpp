#ifndef RBT_HPP
# define RBT_HPP

# include "ft_containers.hpp"

namespace	ft {

	template< class T,  class Compare = std::less<key>, class Allocator>
	class	rbt {

		protected:

			/*** MEMBER STRUCTURES ***/

			template< class T >
			struct	node {

				/*** MEMBER TYPES ***/

				typedef T			value_type;
				typedef size_type	color_type;

				/*** MEMBER FUNCTIONS ***/

				node():
					value(),
					color(BLACK),
					parent(NULL),
					left(NULL),
					right(NULL) {}

				node(const value_type &v, const color_type c = BLACK, node *p = NULL, node *l = NULL, node *r = NULL):
					value(v),
					color(c),
					parent(p),
					left(l),
					right(r) {}

				~node() {}

				node	&operator==(node &rhs) {
					if (&this == rhs)
						return (*this);
					value = rhs.value;
					color = rhs.color,
					parent = rhs.parent;
					left = rhs.left;
					right = rhs.right;
					return (*this);
				}

				/*** MEMBER OBJECTS ***/

				value_type	value;
				color_type	color;
				node		*parent;
				node		*left;
				node		*right;

			};

	};

};

#endif
