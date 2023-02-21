#ifndef NODE_HPP
# define NODE_HPP

# include "ft_containers.hpp"

namespace	ft {

	template<class T>
	struct	node {

		/*** MEMBER TYPES ***/

		typedef T		value_type;
		typedef size_t	color_type;

		/*** MEMBER FUNCTIONS ***/

		node():
			value(),
			color(BLACK),
			parent(NULL),
			left(NULL),
			right(NULL) {}

		node(const value_type &v):
			value(v),
			color(RED),
			parent(NULL),
			left(NULL),
			right(NULL) {}

		node(const value_type &v, node *l, node *r):
			value(v),
			color(RED),
			parent(NULL),
			left(l),
			right(r) {}

		/*** MEMBER OBJECTS ***/

		value_type	value;
		color_type	color;
		node		*parent;
		node		*left;
		node		*right;

	};

};

#endif
