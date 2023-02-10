#ifndef MAP_HPP
# define MAP_HPP

# include "../includes/ft_containers.hpp"
# include "../includes/pair.hpp"
# include "../includes/reverse_iterator.hpp"
# include "../includes/rbt.hpp"
# include "../includes/map_iterator.hpp"
# include "../includes/equal.hpp"
# include "../includes/lexicographical_compare.hpp"

namespace	ft {

	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class	map {

		public:

			/*** MEMBER TYPES ***/

			typedef Key																key_type;
			typedef T																mapped_type;
			typedef typename ft::pair<const Key, T>									value_type;
			typedef std::size_t														size_type;
			typedef std::ptrdiff_t													difference_type;
			typedef Compare															key_compare;
			typedef Allocator														allocator_type;
			typedef value_type&														reference;
			typedef const value_type&												const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef typename ft::map_iterator< value_type, node<value_type> >		iterator;
			typedef typename ft::map_iterator< const value_type, node<value_type> >	const_iterator;
			typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;

			/*** MEMBER CLASSES ***/

			class	value_compare:
				public std::binary_function<value_type, value_type, bool> {

					friend class	map;

					public:

						/*** MEMBER TYPES ***/

						typedef bool		result_type;
						typedef value_type	first_argument_type;
						typedef value_type	second_argument_type;

						/*** MEMBER FUNCTIONS ***/

						bool	operator()(const first_argument_type &lhs, const second_argument_type &rhs) const {
							return (comp(lhs.first, rhs.first));
						}

					protected:

						/*** MEMBER OBJECTS ***/

						key_compare	comp;

						/*** MEMBER FUNCTIONS ***/

						value_compare(key_compare c):
							comp(c) {}

			};

			/*** MEMBER TYPES ***/

			typedef typename ft::rbt<value_type, value_compare>		rbt;

			/*** MEMBER FUNCTIONS ***/

			map():
				_comp(),
				_a(),
				_t(NULL) {}

			explicit map(const key_compare &comp, const allocator_type &alloc = Allocator()):
				_comp(value_compare(comp)),
				_a(alloc),
				_t(_comp) {}

			template<class InputIt>
			map(InputIt first, InputIt last, const key_compare &comp = Compare(), const allocator_type &alloc = Allocator()):
				_comp(value_compare(comp)),
				_a(alloc),
				_t(_comp) {
				insert(first, last);
			}

			map(const map &other):
				_comp(other._comp),
				_a(other._a),
				_t(_comp) {
				*this = other;
			}

			~map() {}

			map	&operator=(const map &other) {
				if (this != &other) {
					_comp = other._comp;
					_a = other._a;
					_t.clear();
					insert(other.begin(), other.end());
				}
				return (*this);
			}

			allocator_type	get_allocator() const {
				return (_a);
			}

			/*** Element access ***/

			mapped_type	&at(const key_type &key) {
				iterator	it = find(key);
				if (it == end())
					throw(std::out_of_range("map::at"));
				return (it->second);
			}

			const mapped_type	&at(const key_type &key) const {
				const_iterator	it = find(key);
				if (it == end())
					throw(std::out_of_range("map::at"));
				return (it->second);
			}

			mapped_type	&operator[](const key_type &key) {
				const_iterator	it = find(key);
				if (it == end())
					it = insert(NULL, value_type(key, mapped_type()));
				return (it->second);
			}

			/*** Iterators ***/

			iterator	begin() {
				return (iterator(_t.begin(), _t.root(), _t.end()));
			}

			const_iterator	begin() const {
				return (const_iterator(_t.begin(), _t.root(), _t.end()));
			}

			iterator	end() {
				return (iterator(_t.end(), _t.root(), _t.end()));
			}

			const_iterator	end() const {
				return (const_iterator(_t.end(), _t.root(), _t.end()));
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
				return (_t.empty());
			}

			size_type	size() const {
				return (_t.size());
			}

			size_type	max_size() const {
				return (_t.max_size());
			}

			/*** Modifiers ***/

			void	clear() {
				_t.clear();
			}

			ft::pair< iterator, bool >	insert(const value_type &value) {
				bool	b = false;
				if (_t.insert(value))
					b = true;
				return (ft::make_pair(iterator(_t.find(value), _t.root(), _t.end()), b));
			}

			iterator	insert(iterator pos, const value_type &value) {
				(void) pos;
				_t.insert(value);
				return (iterator(_t.find(value), _t.root(), _t.end()));
			}

			template<class InputIt>
			void	insert(InputIt first, InputIt last) {
				while (first != last) {
					_t.insert(*first);
					first++;
				}
			}

			iterator	erase(iterator pos) {
				iterator	it = find(pos->second);
				iterator	next = NULL;
				if (it)
					next = it + 1;
				_t.erase(*pos);
				return (next);
			}

			iterator	erase(iterator first, iterator last) {
				while (first != last) {
					_t.erase(*first);
					first++;
				}
			}

			size_type	erase(const key_type &key) {
				return (_t.erase(value_type(key, mapped_type())));
			}


			void	swap(map &other) {
				_swap(_t, other._t);
			}

			/*** Lookup ***/

			size_type	count(const key_type &key) const {
				return (_t.find(key));
			}

			iterator	find(const key_type &key) {
				return (iterator(_t.find(_t.root(), value_type(key, mapped_type())), _t.root(), _t.end()));
			}

			const_iterator	find(const key_type &key) const {
				return (const_iterator(_t.find(_t.root(), value_type(key, mapped_type())), _t.root(), _t.end()));
			}

			ft::pair<iterator, iterator>	equal_range(const key_type &key) {
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}

			ft::pair<const_iterator, const_iterator>	equal_range(const key_type &key) const {
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}

			iterator	lower_bound(const key_type &key) {
				return (iterator(_t.lower_bound(value_type(key, mapped_type())), _t.root(), _t.end()));
			}

			const_iterator	lower_bound(const key_type &key) const {
				return (const_iterator(_t.lower_bound(value_type(key, mapped_type())), _t.root(), _t.end()));
			}

			iterator	upper_bound(const key_type &key) {
				return (iterator(_t.upper_bound(value_type(key, mapped_type())), _t.root(), _t.end()));
			}

			const_iterator	upper_bound(const key_type &key) const {
				return (const_iterator(_t.upper_bound(value_type(key, mapped_type())), _t.root(), _t.end()));
			}

			/*** Observers ***/

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

			/*** MEMBER FUNCTIONS ***/

			template<class tree>
			void	_swap(tree &lhs, tree &rhs) {
				tree	tmp = rhs;
				rhs = lhs;
				lhs = tmp;
			}

	};

	/*** NON-MEMBER FUNCTIONS ***/

	template<class Key, class T, class Compare, class Alloc>
	bool	operator==(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator!=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (!(lhs == rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator<(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator<=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (!(lhs > rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator>(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool	operator>=(const ft::map<Key, T, Compare, Alloc> &lhs, const ft::map<Key, T, Compare, Alloc> &rhs) {
		return (!(lhs < rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	void	swap(ft::map<Key, T, Compare, Alloc> &lhs, ft::map<Key, T, Compare, Alloc> &rhs) {
		lhs.swap(rhs);
	}

};

#endif
