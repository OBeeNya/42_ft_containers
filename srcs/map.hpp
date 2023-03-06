#ifndef MAP_HPP
# define MAP_HPP

# include "../includes/ft_containers.hpp"
# include "../includes/reverse_iterator.hpp"
# include "../includes/lexicographical_compare.hpp"
# include "../includes/pair.hpp"
# include "../includes/equal.hpp"
# include "../includes/rbt.hpp"
# include "../includes/map_iterator.hpp"

namespace ft {

    template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map {

	   public:

	   		/*** MEMBER TYPES ***/

        	typedef Key					                                 			key_type;	                                
        	typedef T																mapped_type;
        	typedef ft::pair<const Key, T> 		             						value_type;	                          
        	typedef std::size_t                         							size_type;	                                 
        	typedef std::ptrdiff_t                      							difference_type;
        	typedef Compare                             							key_compare;                              
        	typedef typename Allocator::template rebind< node<value_type> >::other	allocator_type;	                            
        	typedef value_type&                         							reference;	                                
        	typedef const value_type&                   							const_reference;	                            
        	typedef typename allocator_type::pointer         						pointer;
        	typedef typename allocator_type::const_pointer   						const_pointer;	
        	typedef typename ft::map_iterator<value_type, node<value_type> >		iterator;	
        	typedef typename ft::map_iterator<const value_type, node<value_type> >	const_iterator;	
        	typedef ft::reverse_iterator<iterator>									reverse_iterator;           
        	typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;  

			/*** MEMBER CLASSES ***/

			class value_compare:
				public std::binary_function<value_type, value_type, bool> {

				friend class map;
		
				public:

					/*** MEMBER TYPES ***/

					typedef	bool		result_type;
					typedef value_type	first_arg;
					typedef value_type	second_arg;

					/*** MEMBER FUNCTIONS ***/

					result_type	operator()(const first_arg &x, const second_arg &y) const {
						return (comp(x.first, y.first));
					}

				protected:

					/*** MEMBER OBJECTS ***/

					key_compare	comp;

					/*** MEMBER FUNCTIONS ***/

					value_compare(key_compare c):
						comp(c) {}

			};           

	   		/*** MEMBER TYPES ***/

			typedef	typename ft::rbt<value_type, value_compare>						rbt;

			/*** MEMBER FUNCTIONS ***/

			explicit	map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()):
				_alloc(alloc),
				_comp(value_compare(comp)),
				_size(0),
				_t(_comp) {}

        	template <class InputIt>
        	map(InputIt first, InputIt last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()):
				_alloc(alloc),
				_comp(value_compare(comp)),
				_size(0),
				_t(_comp) {
				insert(first, last);
			} 

        	map(const map &src):
				_alloc(src._alloc),
				_comp(src._comp),
				_size(src._size),
				_t(_comp) { 
				*this = src;
			}

			~map() {
				if (_size)
					_t.delete_tree(_t.getRoot());
				_t.delete_null();
			}

			map	&operator=(const map &rhs) {
				if (this == &rhs)
					return (*this);
				_comp = rhs._comp;
				_alloc = rhs._alloc;
				_t.delete_tree(_t.getRoot());
				insert(rhs.begin(), rhs.end());
        		_size = rhs._size;
				return (*this);
			}

			allocator_type	get_allocator() const {
				return (_alloc);
			}

			/*** Element access ***/

			mapped_type	&operator[](const key_type &key) {
				iterator it = find(key);
				if (it == end()) {
					insert(value_type(key, mapped_type()));
					it = find(key);
				}
				return (it->second);
			}

			mapped_type	&at(const key_type &key);

			const mapped_type	&at(const key_type &key) const;

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

			ft::pair<iterator, bool>	insert(const value_type &val) { 
				if (!(_t.insert(val))) {
					return (ft::make_pair(iterator(_t.find(_t.getRoot(), val), _t.getRoot(), _t.getNull()), false));
				}
				_size++;
				return (ft::make_pair(iterator(_t.find(_t.getRoot(), val), _t.getRoot(), _t.getNull()), true));
			}

			iterator	insert(iterator pos, const value_type &val) {
				(void) pos;
				insert(val);
				return (iterator(_t.find(_t.getRoot(), val), _t.getRoot(), _t.getNull()));
			}

			template <class InputIt>
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
		
			size_type	erase(const key_type &key) {
				if (!_size)
					return (0);
				iterator	it = find(key);
				if (it == end())
					return (0);
				erase(it);
				return (1);
			}
		
			void	erase(iterator first, iterator last) {
				iterator	tmp = first;
				while (first != last) {
					tmp = first;
					first++;
					erase(tmp->first);
				}
			}

			void	swap(map &other) {
				size_t	tmp = other._size;
				other._size = _size;
				_size = tmp;
				_swap(_t, other._t);
			}
		
			void	clear()	{
				if (_size) {
					_t.clear();
					_size = 0;
				}
			}

			/*** Lookup ***/

			iterator	find(const key_type &key) {
				return (iterator(_t.find(_t.getRoot(), value_type(key, mapped_type())), _t.getRoot(), _t.getNull()));
			}
		
			const_iterator	find(const key_type &key) const {
				return (iterator(_t.find(_t.getRoot(), value_type(key, mapped_type())), _t.getRoot(), _t.getNull()));
			}
		
			size_type	count(const key_type &key) const {
				if (find(key) == end())
					return (0);
				return (1);
			}
		
			/*** Observers ***/

			key_compare	key_comp() const {
				return (key_compare());
			}
		
			value_compare	value_comp() const {
				return (_comp);
			}

			iterator	lower_bound(const key_type &key) {
				return (iterator(_t.lower_bound(value_type(key, mapped_type())), _t.getRoot(), _t.getNull()));
			}

			const_iterator	lower_bound(const key_type &key) const {
				return (const_iterator(_t.lower_bound(value_type(key, mapped_type())), _t.getRoot(), _t.getNull()));
			}

			iterator	upper_bound(const key_type &key) {
				return (iterator(_t.upper_bound(value_type(key, mapped_type())), _t.getRoot(), _t.getNull()));
			}

			const_iterator	upper_bound(const key_type &key) const {
				return (const_iterator(_t.upper_bound(value_type(key, mapped_type())), _t.getRoot(), _t.getNull()));
			}
		
			ft::pair<const_iterator,const_iterator>	equal_range(const key_type &key) const {
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}
		
			ft::pair<iterator,iterator>	equal_range(const key_type &key) {
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}

    	protected:

			/*** MEMBER OBJECTS ***/

			allocator_type	_alloc;
			value_compare	_comp;
        	size_type		_size;
			rbt				_t;

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

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
		return (!(lhs < rhs) && !(lhs > rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
		return (! ( lhs > rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs) {
		return (!( lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void	swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs) {
		return (lhs.swap(rhs));
	}

};

#endif
