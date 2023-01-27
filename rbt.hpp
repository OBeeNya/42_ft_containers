#ifndef RBT_HPP
# define RBT_HPP

# include "ft_containers.hpp"
# include "node.hpp"

namespace	ft {

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
					_a.construct(_end, node_type(value_type(), BLACK));
					_root = _end;
				}

			~rbt() {
				if (_root != _end)
					clear(_root);
				_a.deallocate(_end, 1);
			}

			/*** Iterators ***/

			pointer	get_begin() const {
				return (_get_min(_root));
			}

			pointer	get_end() const {
				return (_end);
			}

			pointer	get_root() const {
				return (_root);
			}

			/*** Capacity ***/

			bool	empty() const {
				return (!(size()));
			}

			size_type	size() const {
				return (size);
			}

			size_type	max_size() const {
				return (std::numeric_limits<difference_type>::max() / sizeof(node_type::value_type));
			}

			/*** Modifiers ***/

			void	clear() {
				_clear(_root);
				size = 0;
				_root = _end;
			}

			pointer	insert(const value_type &val) {
				pointer	p = _a.allocate(1);
				_a.construct(p, node(val, BLACK, NULL, _end, _end));
				pointer	parent = _root;

			}

		private:

			/*** MEMBER OBJECTS ***/

			pointer			_root;
			pointer			_end;
			value_compare	_cmp;
			allocator_type	_a;
			size_type		_size;

			/*** MEMBER FUNCTIONS ***/

			/*** Modifiers ***/

			void	_clear(pointer p) {
				if (p == _end)
					return ;
				_clear(p->left);
				_clear(p->right);
				_a.destroy(p);
				_a.deallocate(p, 1);
			}

	};

};

#endif
