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
					_a.construct(_end, node(value_type(), BLACK));
					_root = _end;
				}

			~rbt() {
				if (_root != _end)
					_destroy_tree(_root);
				_a.deallocate(_end, 1);
			}

			bool	empty() const {
				return (!(size()));
			}

			size_type	size() const {
				return (size);
			}

			size_type	max_size() const {

			}

		private:

			/*** MEMBER FUNCTIONS ***/

			void	_destroy_tree(pointer n) {
				if (n == _end)
					return ;
				_destroy_tree(n->left);
				_destroy_tree(n->right);
				_a.destroy(n);
				_a.deallocate(n, 1);
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
