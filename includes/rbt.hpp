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

			rbt():
				_cmp(),
				_a(),
				_size(0) {}

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
					_clear(_root);
				_a.deallocate(_end, 1);
			}

			/*** Iterators ***/

			pointer	begin() const {
				return (_min(_root));
			}

			pointer	end() const {
				return (_end);
			}

			pointer	root() const {
				return (_root);
			}

			/*** Capacity ***/

			bool	empty() const {
				return (!(size()));
			}

			size_type	size() const {
				return (_size);
			}

			size_type	max_size() const {
				return (std::numeric_limits<difference_type>::max() / sizeof(ft::node<value_type>));
			}

			/*** Modifiers ***/

			void	clear() {
				_clear(_root);
				_size = 0;
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

			bool	erase(const value_type &val) {
				pointer	to_del, to_switch, to_fix;
				to_del = _find(val, _root);
				if (!to_del)
					return (false);
				to_switch = to_del;
				int	switch_col = to_switch->color;
				if (!(to_del->left)) {
					to_fix = to_del->right;
					_transplant(to_del, to_del->right);
				}
				else if (!(to_del->right)) {
					to_fix = to_del->left;
					_transplant(to_del, to_del->left);
				}
				else {
					to_switch = _min(to_del->right);
					switch_col = to_switch->color;
					to_fix = to_switch->right;
					if (to_switch->parent == to_del)
						to_fix->parent = to_switch;
					else {

						if (to_switch)
							_transplant(to_switch, to_switch->right);
						else
							return (false);
						to_switch->right = to_del->right;
						to_switch->right->parent = to_switch;
					}
					_transplant(to_del, to_switch);
					to_switch->left = to_del->left;
					to_switch->left->parent = to_switch;
					to_switch->color = to_del->color;
				}
				_a.destroy(to_del);
				_a.deallocate(to_del, 1);
				if (switch_col == BLACK)
					_erase_fix(to_fix);
				return (true);
			}

			void	swap(rbt &other) {
				pointer	root = other._root;
				pointer	end = other._end;
				value_compare	cmp = other._cmp;
				allocator_type	a = other._a;
				size_type	size = other._size;
				other._root = _root;
				other._end = _end;
				other._cmp = _cmp;
				other._a = _a;
				other._size = _size;
				_root = root;
				_end = end;
				_cmp = cmp;
				_a = a;
				_size = size;
			}

			/*** Lookup ***/

			pointer	find(const value_type &val) const {
				return (_find(val, _root));
			}

			pointer	lower_bound(const value_type &val) const {
				pointer	tmp = _root;
				pointer	save = _end;
				while (tmp != _end) {
					if (!_cmp(tmp->value, val)) {
						save = tmp;
						tmp = tmp->left;
					}
					else
						tmp = tmp->right;
				}
				return (save);
			}

			pointer	upper_bound(const value_type &val) const {
				pointer	tmp = _root;
				pointer	save = _end;
				while (tmp != _end) {
					if (_cmp(val, tmp->value)) {
						save = tmp;
						tmp = tmp->left;
					}
					else
						tmp = tmp->right;
				}
				return (save);
			}

		private:

			/*** MEMBER OBJECTS ***/

			pointer			_root;
			pointer			_end;
			value_compare	_cmp;
			allocator_type	_a;
			size_type		_size;

			/*** MEMBER FUNCTIONS ***/

			/*** Iterators ***/

			pointer	_min(pointer p) const {
				if (!p || p == _end)
					return (_end);
				else {
					while (p->left != _end)
						p = p->left;
					return (p);
				}
			}

			/*** Modifiers ***/

			void	_clear(pointer p) {
				if (!p || p == _end)
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
				if (l->right)
					l->right->parent = p;
				l->parent = p->parent;
				if (!(p->parent))
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
				if (r->left)
					r->left->parent = p;
				r->parent = p->parent;
				if (!(p->parent))
					_root = r;
				else if (p == p->parent->left)
					p->parent->left = r;
				else
					p->parent->right = r;
				r->left = p;
				p->parent = r;
			}

			void	_transplant(pointer x, pointer y) {
				if (!(x->parent))
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;

				if (y)
					y->parent = x->parent;
			}

			void	_erase_fix(pointer to_fix) {
				pointer	save;
				if (!to_fix)
					return ;
				while (to_fix && to_fix->color == BLACK) {
					if (to_fix == to_fix->parent->left) {
						save = to_fix->parent->right;
						if (save->color == RED) {
							save->color = BLACK;
							to_fix->parent->color = RED;
							_left_rotate(to_fix->parent);
							save = to_fix->parent->right;
						}
						if (save->left->color == BLACK && save->right->color == BLACK) {
							save->color = RED;
							to_fix = to_fix->parent;
						}
						else {
							if (save->right->color == BLACK) {
								save->left->color = BLACK;
								save->color = RED;
								_right_rotate(save);
								save = to_fix->parent->right;
							}
							save->color = to_fix->parent->color;
							to_fix->parent->color = BLACK;
							save->right->color = BLACK;
							_left_rotate(to_fix->parent);
							to_fix = _root;
						}
					}
					else {
						save = to_fix->parent->left;
						if (save->color == RED) {
							save->color = BLACK;
							to_fix->parent->color = RED;
							_right_rotate(to_fix->parent);
							save = to_fix->parent->left;
						}
						if (save->left->color == BLACK && save->right->color == BLACK) {
							save->color = RED;
							to_fix = to_fix->parent;
						}
						else {
							if (save->left->color == BLACK) {
								save->right->color = BLACK;
								save->color = RED;
								_left_rotate(save);
								save = to_fix->parent->left;
							}
							save->color = to_fix->parent->color;
							to_fix->parent->color = BLACK;
							save->left->color = BLACK;
							_right_rotate(to_fix->parent);
							to_fix = _root;
						}
					}
				}
				to_fix->color = BLACK;
			}

			/*** Lookup ***/

			pointer	_find(const value_type &val, const pointer current) const {
				if (!current)
					return (NULL);
				if (_cmp(current->value, val))
					return (_find(val, current->right));
				if (_cmp(val, current->value))
					return (_find(val, current->left));
				return (current);
			}

	};

};

#endif
