#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "ft_containers.hpp"
# include "iterator.hpp"

namespace	ft {

	template <typename T, typename node>
	class	map_iterator {

		public:

			/*** MEMBER TYPES ***/

			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference			reference;
			typedef	node																			node_type;
			typedef node*																			node_ptr;
			typedef node&																			node_ref;

			/*** MEMBER FUNCTIONS ***/

			map_iterator():
				_current(NULL),
				_root(NULL),
				_end(NULL) {}

			map_iterator(const node_ptr &current, const node_ptr &root, const node_ptr &end):
				_current(current),
				_root(root),
				_end(end) {}

			map_iterator(const map_iterator &src):
				_current(src._current),
				_root(src._root),
				_end(src._end) {}

			~map_iterator() {}

			map_iterator	&operator=(const map_iterator &rhs)
			{
				if (this == &rhs)
					return (*this);
				_current = rhs._current;
				_root = rhs._root;
				_end = rhs._end;
				return (*this);
			}

			map_iterator	&operator++() {
				_increment();
				return (*this);
			}

			map_iterator	operator++(int) {
				map_iterator	tmp(*this);
				_increment();
				return (tmp);
			}

			map_iterator	&operator--() {
				_decrement();
				return (*this);
			}

			map_iterator	operator--(int) {
				map_iterator	tmp(*this);
				_decrement();
				return (tmp);
			}

			bool	operator==(const map_iterator & rhs) const {
				return (_current == rhs._current);
			}

			bool	operator!=(const map_iterator & rhs) const {
				return (_current != rhs._current);
			}

			reference	operator*() const {
				return (_current->value);
			}

			pointer	operator->() const {
				return (&(_current->value));
			}

			operator map_iterator<const T, node>() const {
				return (map_iterator<const T, node>(_current, _root, _end));
			}

		private:

			/*** MEMBER OBJECTS ***/

			node_ptr	_current;
			node_ptr	_root;
			node_ptr	_end;

			/*** MEMBER FUNCTIONS ***/

			void	_increment() {
				if (_current == _end) {
					_current = _max(_root);
					return ;
				}
				node_ptr	tmp_current = _current;
				if (tmp_current->right != _end)
					_current = _min(tmp_current->right);
				else {
					node_ptr	tmp_parent = tmp_current->parent;
					while (tmp_parent && tmp_current == tmp_parent->right) {
						tmp_current = tmp_parent;
						tmp_parent = tmp_current->parent;
					}
					if (!tmp_parent)
						_current = _end;
					else
						_current = tmp_parent;
				}
			}

			void	_decrement() {
				if (_current == _end) {
					_current = _max(_root);
					return ;
				}
				if (_current->left != _end) {
					_current = _max(_current->left);
				}
				else {
					node_ptr	tmp_parent = _current->parent;
					while (tmp_parent && tmp_parent != _end && _current == tmp_parent->left) {
						_current = tmp_parent;
						tmp_parent = tmp_parent->parent;
					}
					_current = tmp_parent;
				}
			}

			node_ptr	_max(node_ptr x) {
				if (!x || x == _end)
					return (_end);
				while (x->right != _end && x->right)
					x = x->right;
				return (x);
			}

			node_ptr	_min(node_ptr x) {
				if (!x || x == _end)
					return(_end);
				while (x->left != _end && x->left)
					x = x->left;
				return (x);
			}

	};

};

#endif
