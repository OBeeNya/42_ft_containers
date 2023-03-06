#ifndef SET_HPP
# define SET_HPP

# include "../includes/ft_containers.hpp"
# include "../includes/map_iterator.hpp"
# include "../includes/rbt.hpp"
# include "../includes/reverse_iterator.hpp"
# include "../includes/pair.hpp"
# include "../includes/equal.hpp"
# include "../includes/lexicographical_compare.hpp"

namespace	ft {

	template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class	set {

		public:

			/*** MEMBER TYPES ***/

			typedef Key																key_type;
			typedef Key																value_type;
			typedef std::size_t														size_type;
			typedef std::ptrdiff_t													difference_type;
			typedef Compare															key_compare;
			typedef Compare															value_compare;
			typedef typename Allocator::template rebind< node<value_type> >::other	allocator_type;
			typedef value_type&														reference;
			typedef const value_type&												const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef typename ft::map_iterator< const value_type, node<value_type> >	iterator;
			typedef typename ft::map_iterator< const value_type, node<value_type> >	const_iterator;
			typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef typename ft::rbt<value_type, value_compare>						rbt;

			/*** MEMBER FUNCTIONS ***/

			set():
				_comp(),
				_a(),
				_t(value_compare()),
				_size(0) {}

			explicit set(const key_compare &comp, const allocator_type &alloc = Allocator()):
				_comp(comp),
				_a(alloc),
				_t(_comp),
				_size(0) {}

			template<class InputIt>
			set(InputIt first, InputIt last, const key_compare &comp = Compare(), const allocator_type &alloc = Allocator()):
				_comp(comp),
				_a(alloc),
				_t(_comp),
				_size(0) {
				insert(first, last);
			}

			set(const set &other):
				_comp(other._comp),
				_a(other._a),
				_t(_comp),
				_size(other._size) {
				*this = other;
			}

			~set() {
				if (_size)
					_t.delete_tree(_t.getRoot());
				_t.delete_null();
			}

			set	&operator=(const set &other) {
				if (this != &other) {
					_comp = other._comp;
					_a = other._a;
					_t.delete_tree(_t.getRoot());
					insert(other.begin(), other.end());
					_size = other._size;
				}
				return (*this);
			}

			/*** Iterators ***/

			iterator	begin() {
				return (iterator(_t.begin(), _t.getRoot(), _t.getNull()));
			}

			const_iterator	begin() const {
				return (const_iterator(_t.begin(), _t.getRoot(), _t.getNull()));
			}

			iterator	end() {
				return (iterator(_t.getNull(), _t.getRoot(), _t.getNull()));
			}

			const_iterator	end() const {
				return (const_iterator(_t.getNull(), _t.getRoot(), _t.getNull()));
			}

			reverse_iterator	rbegin() {
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(end()));
			}

			reverse_iterator	rend() {
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const {
				return (const_reverse_iterator(begin()));
			}

			/*** Capacity ***/

			bool	empty() const {
				return (_t.getRoot() == _t.getNull());
			}

			size_type	size() const {
				return (_size);
			}

			size_type	max_size() const {
				return (_t.max_size());
			}

			/*** Modifiers ***/

			void	clear() {
				if (_size) {
					_t.clear();
					_size = 0;
				}
			}

			ft::pair<iterator, bool>	insert(const value_type &value) {
				if (!(_t.insert(value))) {
					return (ft::make_pair(iterator(_t.find(_t.getRoot(), value), _t.getRoot(), _t.getNull()), false));
				}
				_size++;
				return (ft::make_pair(iterator(_t.find(_t.getRoot(), value), _t.getRoot(), _t.getNull()), true));
			}

			iterator	insert(iterator pos, const value_type &value) {
				(void) pos;
				insert(value);
				return (iterator(_t.find(_t.getRoot(), value), _t.getRoot(), _t.getNull()));
			}

			template<class InputIt>
			void	insert(InputIt first, InputIt last) {
				while (first != last) {
					insert(*first);
					first++;
				}
			}

			void	erase(iterator pos) {
				if (!_size)
					return ;
				if ( _t.deleteNode(*pos))
					_size--;
			}

			void	erase(iterator first, iterator last) {
				iterator	tmp = first;
				while (first != last) {
					tmp = first;
					first++;
					erase(tmp);
				}
			}

			size_type	erase(const key_type &key) {
				if (!_size)
					return (0);
				iterator	it = find(key);
				if (it == end())
					return (0);
				erase(it);
				return (1);
			}

			void	swap(set &other) {
				size_t	tmp = other._size;
				other._size = _size;
				_size = tmp;
				_swap(_t, other._t);
			}

			/*** Lookup ***/

			size_type	count(const key_type &key) const {
				if (find(key) == end())
					return (0);
				return (1);
			}

			iterator	find(const key_type &key) {
				return (iterator(_t.find(_t.getRoot(), key), _t.getRoot(), _t.getNull()));
			}

			const_iterator	find(const key_type &key) const {
				return (iterator(_t.find(_t.getRoot(), key), _t.getRoot(), _t.getNull()));
			}

			/*** Observers ***/

			ft::pair<iterator, iterator>	equal_range(const key_type &key) {
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}

			ft::pair<const_iterator, const_iterator>	equal_range(const key_type &key) const {
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}

			iterator	lower_bound(const key_type &key) {
				return (iterator(_t.lower_bound(key), _t.getRoot(), _t.getNull()));
			}

			const_iterator	lower_bound(const key_type &key) const {
				return (const_iterator(_t.lower_bound(key), _t.getRoot(), _t.getNull()));
			}

			iterator	upper_bound(const key_type &key) {
				return (iterator(_t.upper_bound(key), _t.getRoot(), _t.getNull()));
			}

			const_iterator	upper_bound(const key_type &key) const {
				return (const_iterator(_t.upper_bound(key), _t.getRoot(), _t.getNull()));
			}

			key_compare	key_comp() const {
				return (key_compare());
			}

			value_compare	value_comp() const {
				return (_comp);
			}

		private:

			/*** MEMBER OBJECTS ***/

			value_compare	_comp;
			allocator_type	_a;
			rbt				_t;
			size_type		_size;

			/*** MEMBER FUNCTIONS ***/

			/*** Modifiers ***/

			template <class tree>
			void	_swap(tree &t1, tree &t2) {
				tree	tmp = t2;
				t2 = t1;
				t1 = tmp;
			}

	};

	/*** NON-MEMBER FUNCTIONS ***/

	template<class Key, class Compare, class Alloc>
	bool	operator==(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class Compare, class Alloc>
	bool	operator!=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return (!(lhs == rhs));
	}

	template<class Key, class Compare, class Alloc>
	bool	operator<(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class Compare, class Alloc>
	bool	operator<=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return (!(lhs > rhs));
	}

	template<class Key, class Compare, class Alloc>
	bool	operator>(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template<class Key, class Compare, class Alloc>
	bool	operator>=(const ft::set<Key, Compare, Alloc> &lhs, const ft::set<Key, Compare, Alloc> &rhs) {
		return (!(lhs < rhs));
	}

	template<class Key, class Compare, class Alloc>
	void	swap(ft::set<Key, Compare, Alloc> &lhs, ft::set<Key, Compare, Alloc> &rhs) {
		lhs.swap(rhs);
	}

};

#endif
