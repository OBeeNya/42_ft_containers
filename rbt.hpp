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
				if (_root == _end) {
					_root = p;
					_root->parent = _end;
					_size++;
					return (_root);
				}
				while (parent != _end) {
					if (_cmp(val, parent->value)) {
						if (parent->left == _end)
							break ;
						parent = parent->left;
					}
					else if (_cmp(parent->value, val)) {
						if (parent->right == _end)
							break ;
						parent = parent->right;
					}
					else {
						_a.destroy(p);
						_a.deallocate(p, 1);
						return (NULL);
					}
				}
				p->parent = parent;
				if (_cmp(val, parent->value))
					parent->left = p;
				else
					parent->right = p;
				_size++;
				if (p->parent->parent == _end)
					return (p);
				_insert_fix(p);
				return (p);
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

			void	_insert_fix(pointer p) {
				pointer	uncle;
				while (p->parent->color == RED) {
					if (p->parent == p->parent->parent->right) {
						uncle = p->parent->parent->left;
						if (uncle->color == RED) {
							uncle->color = BLACK;
							p->parent->color = BLACK;
							p->parent->parent->color = RED;
							p = p->parent->parent;
						}
						else {
							if (p == p->parent->left) {
								p = p->parent;
								_right_rotate(p);
							}
							p->parent->color = BLACK;
							p->parent->parent->color = RED;
							_left_rotate(p->parent->parent);
						}
					}
					else {
						uncle = p->parent->parent->right;
						if (uncle->color == RED) {
							uncle->color = BLACK;
							p->parent->color = BLACK;
							p->parent->parent->color = RED;
							p = p->parent->parent;
						}
						else {
							if (p == p->parent->right) {
								p = p->parent;
								_left_rotate(p);
							}
							p->parent->color = BLACK;
							p->parent->parent->color = RED;
							_right_rotate(p->parent->parent);
						}
					}
					if (p == _root)
						break ;
				}
				_root->color = BLACK;
			}

			void	_right_rotate(pointer p) {
				pointer	l = p->left;
				p->left = l->right;
				if (l->right != _end)
					l->right->parent = p;
				l->parent = p->parent;
				if (p->parent == _end)
					_root = l;
				else if (p == p->parent->right)
					p->parent->right = l;
				else
					p->parent->left = l;
				l->right = p;
				p->parent = l;
			}

			void	_left_rotate(pointer p) {
				pointer	r = p->right;
				p->right = r->left;
				if (r->left != _end)
					r->left->parent = p;
				r->parent = p->parent;
				if (p->parent == _end)
					_root = r;
				else if (p == p->parent->left)
					p->parent->left = r;
				else
					p->parent->right = r;
				r->left = p;
				p->parent = r;
			}

	};

};

#endif
