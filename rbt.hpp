#ifndef RBT_HPP
# define RBT_HPP

# include "ft_containers.hpp"

namespace	ft {

	template< class T >
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

	template< class T,  class Compare, class node = ft::node<T>, class Allocator = std::allocator<node> >
	class	rbt {

		public:

			/*** MEMBER TYPES ***/

				typedef T									value_type;
				typedef Allocator							allocator_type;
				typedef typename allocator_type::pointer	pointer;
				typedef typename allocator_type::reference	reference;
				typedef node								node_type;
				typedef std::size_t							size_type;
				typedef std::ptrdiff_t						difference_type;
				typedef Compare								value_compare;
				typedef typename node::color_type			color_type;

			/*** MEMBER FUNCTIONS ***/

			rbt(const value_compare	&cmp = value_compare()):
				_cmp(cmp),
				_a(allocator_type()),
				_size(0) {
					_end = _a.allocate(1);
					_a.construct(_end, node(value_type(), RED));
					_root = _end;
				}

	private:

			pointer			_root;
			pointer			_end;
			value_compare	_cmp;
			allocator_type	_a;
			size_type		_size;

	};

};

#endif
