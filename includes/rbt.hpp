#ifndef RBT_HPP
# define RBT_HPP

# include "ft_containers.hpp"
# include "node.hpp"

namespace	ft {

	template <typename T, class Compare, typename node = ft::node<T>, typename Allocator = std::allocator<node> >
	class	rbt {

		public:

			/*** MEMBER TYPES ***/

			typedef T								value_type;
			typedef std::size_t						size_type;	                                 
			typedef Allocator						allocator_type;	                            
			typedef value_type&						reference;
			typedef	Compare							value_compare;
			typedef typename Allocator::pointer		pointer;                          

			/*** MEMBER FUNCTIONS ***/
			
			rbt(const value_compare &comp = value_compare()):
				_comp(comp),
				_alloc(allocator_type()) {
				_null = _alloc.allocate(1);
				_alloc.construct(_null, node(value_type()));	
				_null->parent = NULL;
				_null->right = NULL;
				_null->left = NULL;
				_null->color = BLACK;
				_root = _null;
			}

			~rbt() {}

			/*** Iterators ***/

			pointer	begin() {
				return (_minimum(_root));
			}

			pointer	begin() const {
				return (_minimum(_root));
			}

			pointer	end() {
				return (_maximum(_root));
			}
	
			pointer	end() const {
				return (_maximum(_root));
			}

			pointer	getNull() const {
				return (_null);
			}

			pointer	getRoot() const {
				return (_root);
			}

			/*** Capacity ***/

			size_type	max_size() const {
				return (_alloc.max_size());
			}

			/*** Modifiers ***/

			pointer	insert(value_type key) {
				pointer	p = _alloc.allocate(1);
				_alloc.construct(p, node(key, _null, _null));
				pointer	y = NULL;
				pointer	x = _root;
				while (x != _null) {
					y = x;
					if (_comp(p->value, x->value))
						x = x->left;
					else if (_comp(x->value, p->value))
						x = x->right;
					else {
						_alloc.destroy(p);
						_alloc.deallocate(p, 1);
						return (NULL);
					}
				}
				p->parent = y;
				if (!y)
					_root = p;
				else if (_comp(p->value, y->value))
					y->left = p;
				else
					y->right = p;
				if (!(p->parent)) {
					p->color = BLACK;
					return (p);
				}
				if (!(p->parent->parent))
					return (p);
				_insertFix(p);
				return (p);
			}

			bool	deleteNode(value_type value) {
				return (_deleteNode(_root, value));
			}

			void	delete_tree(pointer p) {
				_root = _null;
				if (p == _null)
					return ;
				delete_tree(p->left);
				delete_tree(p->right);
				_alloc.destroy(p);
				_alloc.deallocate(p, 1);
			}

			void	delete_null() {
				_alloc.destroy(_null);
				_alloc.deallocate(_null, 1);
			}

			void	clear() {
				_clear(_root);
				_root = _null;
			}

			/*** Lookup***/

			pointer	find(const pointer p, const value_type &key) const {
				if (p == _null)
					return (_null);
				else if (_comp(key, p->value))
					return find(p->left, key);
				else if(_comp(p->value, key))
					return (find(p->right, key));
				return (p);
			}

			pointer	upper_bound(const value_type &key) const {
				return (_upper_bound(key, _root));
			}	

			pointer	lower_bound(const value_type &key) const {
				return (_lower_bound(key, _root));
			}

		private:

			/*** MEMBER OBJECTS ***/

			value_compare	_comp;
			allocator_type	_alloc;
			pointer			_root;
			pointer			_null;

			/*** MEMBER FUNCTIONS ***/

			/*** Iterators ***/

			pointer	_minimum(pointer p) {
				if (p == _null)
					return (p);
				while (p->left != _null)
					p = p->left;
				return (p);
			}

			pointer	_minimum(pointer p) const {
				if (p == _null)
					return (p);
				while (p->left != _null)
					p = p->left;
				return (p);
			}

			pointer	_maximum(pointer p) {
				if (p == _null)
					return (p);
				while (p->right != _null)
					p = p->right;
				return (p);
			}
	
			pointer	_maximum(pointer p) const {
				if (p == _null)
					return (p);
				while (p->right != _null)
					p = p->right;
				return (p);
			}

			/*** Modifiers ***/

			bool	_deleteNode(pointer p, value_type key) {
				pointer	z = _null;
				pointer	x, y;
				while (p != _null) {
					if (p->value == key) 
						z = p;
					if (_comp(p->value, key))
						p = p->right;
					else
						p = p->left;
				}
				if (z == _null)
					return (false);
				y = z;
				int	y_color = y->color;
				if (z->left == _null) {
					x = z->right;
					_transplant(z, z->right);
				}
				else if (z->right == _null) {
					x = z->left;
					_transplant(z, z->left);
				}
				else {
					y = _minimum(z->right);
					y_color = y->color;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else  {
						_transplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					_transplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				delete z;
				if (y_color == BLACK)
					_deleteFix(x);
				return (true);
			}

			void	_clear(pointer p) {
				if (p == _null)
					return ;
				_clear(p->right);
				_clear(p->left);
				_alloc.destroy(p);
				_alloc.deallocate(p, 1);
			}

			void	_leftRotate(pointer x) {
				pointer	y = x->right;
				x->right = y->left;
				if (y->left != _null)
					y->left->parent = x;
				y->parent = x->parent;
				if (!(x->parent))
					_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			void	_rightRotate(pointer x) {
				pointer	y = x->left;
				x->left = y->right;
				if (y->right != _null)
					y->right->parent = x;
				y->parent = x->parent;
				if (!(x->parent))
					_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			void	_transplant(pointer u, pointer v) {
				if (!(u->parent))
					_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void	_insertFix(pointer k) {	
				pointer	u;
				while (k->parent->color == RED) {
					if (k->parent == k->parent->parent->right) {
						u = k->parent->parent->left;
						if (u->color == RED) {
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else {
							if (k == k->parent->left) {
								k = k->parent;
								_rightRotate(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							_leftRotate(k->parent->parent);
						}
					}
					else {
						u = k->parent->parent->right;
						if (u->color == RED) {
							u->color = BLACK;
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							k = k->parent->parent;
						}
						else {
							if (k == k->parent->right) {
								k = k->parent;
								_leftRotate(k);
							}
							k->parent->color = BLACK;
							k->parent->parent->color = RED;
							_rightRotate(k->parent->parent);
						}
					}
					if (k == _root) 
						break;
				}
				_root->color = BLACK;
			}

			void	_deleteFix(pointer x) {
				pointer	s;
				while (x != _root && x->color == BLACK) {
					if (x == x->parent->left) {
						s = x->parent->right;
						if (s->color == RED) {
							s->color = BLACK;
							x->parent->color = RED;
							_leftRotate(x->parent);
							s = x->parent->right;
						}
						if (s->left->color == BLACK && s->right->color == BLACK) {
							s->color = RED;
							x = x->parent;
						} 
						else {
							if (s->right->color == BLACK) {
								s->left->color = BLACK;
								s->color = RED;
								_rightRotate(s);
								s = x->parent->right;
							}
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->right->color = BLACK;
							_leftRotate(x->parent);
							x = _root;
						}
					} 
					else {
						s = x->parent->left;
						if (s->color == RED) {
							s->color = BLACK;
							x->parent->color = RED;
							_rightRotate(x->parent);
							s = x->parent->left;
						}
						if (s->left->color == BLACK && s->right->color == BLACK) {
							s->color = RED;
							x = x->parent;
						} 
						else {
							if (s->left->color == BLACK) {
								s->right->color = BLACK;
								s->color = RED;
								_leftRotate(s);
								s = x->parent->left;
							}
							s->color = x->parent->color;
							x->parent->color = BLACK;
							s->left->color = BLACK;
							_rightRotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = BLACK;
			}

			/*** Lookup ***/

			pointer	_lower_bound(const value_type &val, pointer p) const {
				pointer	ret = _null;
				if (p == _null)
					return (ret);
				while (p != _null) {
					if (!(_comp(p->value, val))) {
						ret = p;
						p = p->left;
					}
					else
						p = p->right;
				}
				return (ret);
			}

			pointer	_upper_bound(const value_type &val, pointer p) const {
				pointer	ret = _null;
				while(p != _null) {
					if (_comp(val, p->value)) {
						ret = p;
						p = p->left;
					}
					else
						p = p->right;
				}
				return (ret);
			}

	};

};

#endif
