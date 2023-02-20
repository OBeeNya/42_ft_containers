#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "ft_containers.hpp"
# include "iterator.hpp"

namespace	ft {

	template< class T, class node >
	class	map_iterator:
		public ft::iterator< std::bidirectional_iterator_tag, T > {

		public:

			/*** MEMBER TYPES ***/

			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>	iterator;
			typedef typename iterator::value_type								value_type;
			typedef typename iterator::difference_type							difference_type;
			typedef typename iterator::pointer									pointer;
			typedef typename iterator::reference								reference;
			typedef typename iterator::iterator_category						iterator_category;
			typedef node														node_type;
			typedef node*														node_pointer;
			typedef node&														node_reference;

			/*** MEMBER FUNCTIONS ***/

			map_iterator():
				_current(),
				_root(),
				_end() {}

			map_iterator(const node_pointer &current, const node_pointer &root, const node_pointer &end):
				_current((!current) ? end : current),
				_root(root),
				_end(end) {}

			map_iterator(const map_iterator &src):
				_current(src._current),
				_root(src._root),
				_end(src._end) {}
			
			~map_iterator() {}

			operator	map_iterator<const T, node> () {
				return (map_iterator<const T, node>(_current, _root, _end));
			}

			map_iterator	&operator=(const map_iterator &rhs) {
				if (this != &rhs) {
					_current = rhs._current;
					_root = rhs._root;
					_end = rhs._end;
				}
				return (*this);
			}

			map_iterator	&operator++() {
				if (_current == _end)
					_current = _min(_root);
				else
					_current = _next();
				return (*this);
			}

			map_iterator	operator++(int) {
				map_iterator	tmp = *this;
				if (_current == _end)
					_current = _min(_root);
				else
					_current = _next();
				return (tmp);
			}

			map_iterator	&operator--() {
				if (_current == _end)
					_current = _max(_root);
				else
					_current = _previous();
				return (*this);
			}

			map_iterator	operator--(int) {
				map_iterator	tmp = *this;
				if (_current == _end)
					_current = _max(_root);
				else
					_current = _previous();
				return (tmp);
			}

			bool	operator==(const map_iterator &rhs) const {
				return (_current == rhs._current);
			}

			bool	operator!=(const map_iterator &rhs) const {
				return (!(_current == rhs._current));
			}

			reference	operator*() const {
				return (_current->value);
			}

			pointer	operator->() const {
				return (&(_current->value));
			}

		private:

			/*** MEMBER OBJECTS ***/

			node_pointer	_current;
			node_pointer	_root;
			node_pointer	_end;

			/*** MEMBER FUNCTIONS ***/

			node_pointer	_next() {
				if (_current->right != _end)
					return (_min(_current->right));
				node_pointer	next = _current->parent;
				while (next != _end && _current == next->right) {
					_current = next;
					next = next->parent;
				}
				return (next);
			}

			node_pointer	_previous() {
				if (_current->left != _end)
					return (_max(_current->left));
				node_pointer	previous = _current->parent;
				while (previous != _end && _current == previous->left) {
					_current = previous;
					previous = previous->parent;
				}
				return (previous);
			}

			node_pointer	_max(node_pointer p) const {
				if (!p || p == _end)
					return (_end);
				while (p->right != _end)
					p = p->right;
				return (p);
			}

			node_pointer	_min(node_pointer p) const {
				if (!p || p == _end)
					return (_end);
				while (p->left != _end)
					p = p->left;
				return (p);
			}

	};

};

#endif
