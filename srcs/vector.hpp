#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "../includes/ft_containers.hpp"
# include "../includes/reverse_iterator.hpp"
# include "../includes/enable_if.hpp"
# include "../includes/is_integral.hpp"
# include "../includes/equal.hpp"
# include "../includes/lexicographical_compare.hpp"

namespace ft {

	template < class T, class Allocator = std::allocator<T> >
	class	vector {

		public:

			/*** MEMBER TYPES ***/

			typedef T														value_type;
			typedef Allocator												allocator_type;
			typedef std::size_t												size_type;
			typedef std::ptrdiff_t											difference_type;
			typedef value_type&												reference;
			typedef const value_type&										const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef T*														iterator;
			typedef const T*												const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/*** MEMBER FUNCTIONS ***/

			vector():
				_alloc(),
				_count(0),
				_capacity(0),
				_first(NULL),
				_last(NULL) {}

			explicit vector(const Allocator &alloc):
				_alloc(alloc),
				_count(0),
				_capacity(0),
				_first(NULL),
				_last(NULL) {
					_first = _alloc.allocate(1);
					_last = _first;
				}

			explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator()):
				_alloc(alloc),
				_count(count),
				_capacity(count),
				_first(NULL),
				_last(NULL) {
					_first = _alloc.allocate(_capacity);
					_last = _first;
					for (size_type i = 0; i < _capacity; i++) {
						_alloc.construct(_last, value);
						++_last;
					}
				}

			template <class InputIt>
			vector(InputIt first, InputIt last, const Allocator &alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL):
				_alloc(alloc),
				_count(std::distance(first, last)),
				_capacity(std::distance(first, last)),
				_first(NULL),
				_last(NULL) {
					_first = _alloc.allocate(_capacity);
					_last = _first;
					for (size_type i = 0; i < _capacity; i++) {
						_alloc.construct(_last, *first);
						++first;
						++_last;
					}
				}

			vector(const vector &other):
				_alloc(other._alloc),
				_count(other._count),
				_capacity(other._capacity),
				_first(NULL),
				_last(NULL) {
					_first = _alloc.allocate(_capacity);
					_last = _first;
					for (pointer i = other._first; i < other._last; ++i, ++_last)
						_alloc.construct(_last, *i);
				}

			~vector() {
				clear();
				if (_first != NULL || _first == _last)
					_alloc.deallocate(_first, _capacity);
			}

			vector	&operator=(const vector &other) {
				if (this == &other)
					return (*this);
				clear();
				_alloc.deallocate(_first, _capacity);
				if (other._count > _capacity)
					_capacity = other._count;
				_first = _alloc.allocate(_capacity);
				_last = _first;
				_count = other._count;
				for (pointer i = other._first; i < other._last; ++i, ++_last)
					_alloc.construct(_last, *i);
				return (*this);
			}

			void	assign(size_type count, const T &value) {
				reserve(count);
				for (size_type i = 0; i < _count; i++)
					_alloc.destroy(_first + i);
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_first + i, value);
				_count = count;
				_last = _first + count;
			}

			template <class InputIt>
			void	assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) {
				reserve(std::distance(first, last));
				size_type	i;
				for (i = 0; i < _count; i++)
					_alloc.destroy(_first + i);
				for (i = 0; first != last; ++first, i++)
					_alloc.construct(_first + i, *first);
				_count = i;
				_last = _first + _count;
			}

			allocator_type	get_allocator() const {
				return (_alloc);
			}

			/*** Element access ***/

			reference	at(size_type pos) {
				if (!(pos < size())) {
					std::string	p;
					std::ostringstream	o1;
					std::ostringstream	o2;
					o1 << pos;
					p = o1.str();
					std::string	c;
					o2 << _count;
					c = o2.str();
					throw (std::out_of_range(std::string("vector::_M_range_check: __n (which is ") + p + std::string(") >= this->size() (which is ") + c + std::string(")")));
				}
				return (*(_first + pos));
			}

			const_reference	at(size_type pos) const {
				if (!(pos < size())) {
					std::string	p;
					std::ostringstream	o1;
					std::ostringstream	o2;
					o1 << pos;
					p = o1.str();
					std::string	c;
					o2 << _count;
					c = o2.str();
					throw (std::out_of_range(std::string("vector::_M_range_check: __n (which is ") + p + std::string(") >= this->size() (which is ") + c + std::string(")")));
				}
				return (const_reference(*(_first + pos)));
			}

			reference	operator[](size_type pos) {
				return (*(_first + pos));
			}

			const_reference	operator[](size_type pos) const {
				return (const_reference(*(_first + pos)));
			}

			reference	front() {
				return (*_first);
			}

			const_reference	front() const {
				return (const_reference(*_first));
			}

			reference	back() {
				return (*(_last - 1));
			}
			
			const_reference	back() const {
				return (const_reference(*(_last - 1)));
			}

			T	*data() {
				return (_first);
			}

			const T	*data() const {
				return ((const T)(_first));
			}

			/*** Iterators ***/

			iterator	begin() {
				return (iterator(_first));
			}

			const_iterator	begin() const {
				return (const_iterator(_first));
			}

			iterator	end() {
				return (iterator(_last));
			}

			const_iterator	end() const {
				return (const_iterator(_last));
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
				return (!(size()));
			}

			size_type	size() const {
				return (_count);
			}

			size_type	max_size() const {
				return (_alloc.max_size());
			}

			void	reserve(size_type new_cap) {
				if (new_cap > max_size())
					throw (std::length_error("vector::reserve"));
				if (new_cap < capacity())
					return;
				pointer	free = _first;
				pointer	b = _first;
				_first = _alloc.allocate(new_cap);
				_last = _first;
				for (size_type i = 0; i < _count; i++) {
					_alloc.construct(_last, *b);
					_alloc.destroy(b);
					++_last;
					++b;
				}
				_alloc.deallocate(free, _capacity);
				_capacity = new_cap;
			}

			size_type	capacity() const {
				return (_capacity);
			} 

			/*** Modifiers ***/

			void	clear() {
				while (_count--)
					_alloc.destroy(_first + _count);
				_last = _first;
				_count = 0;
			}

			iterator	insert(const_iterator pos, const value_type &value) {
				difference_type	dist = pos - begin();
				insert(pos, 1, value);
				return (iterator(begin() + dist));
			}

			void	insert(const_iterator pos, size_type count, const value_type &value) {
				difference_type	a = pos - begin();
				difference_type	b = end() - pos;
				difference_type	c = end() - begin();
				if (!count)
					return ;
				if (count + _count <= _capacity);
				else if (count + _count >= _capacity * VECTOR_CAPACITY_ADJUSTMENT)
					reserve(count + _count);
				else
					reserve(_count * VECTOR_CAPACITY_ADJUSTMENT);
				for (difference_type i = 1; i <= b; i++) {
					_alloc.construct((_first + c + count) - i, *(_first + c - i));
					_alloc.destroy(_first + c - i);
				}
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_first + a + i, value);
				_last = _first + _count + count;
				_count += count;
				pos++;
			}

			// iterator	insert(const_iterator pos, const T &value) {
			// 	// difference_type	first_pos = std::distance(begin(), pos);
			// 	difference_type	first_pos = pos - begin();
			// 	if (!_capacity)
			// 		reserve(1);
			// 	else if (_count >= _capacity)
			// 		reserve(_capacity * VECTOR_CAPACITY_ADJUSTMENT);
			// 	size_t	i = 1;
			// 	for (difference_type j = _count; j > first_pos; i++, j--) {
			// 		_alloc.construct(begin() + j, *(end() - i));
			// 		_alloc.destroy(end() - i);
			// 	}
			// 	_alloc.construct(begin() + first_pos, value);
			// 	_count++;
			// 	// return (iterator(begin() + first_pos));
			// 	return (begin() + first_pos);
			// }

			// iterator	insert(const_iterator pos, size_type count, const T &value) {
			// 	if (!count)
			// 		return ((iterator)pos);
			// 	// difference_type	first_pos = std::distance(begin(), pos);
			// 	difference_type	first_pos = pos - begin();
			// 	if (_count + count >= _capacity * VECTOR_CAPACITY_ADJUSTMENT)
			// 		reserve(_count + count);
			// 	else if (_count + count > _capacity)
			// 		reserve(_count * VECTOR_CAPACITY_ADJUSTMENT);
			// 	size_t	i = 1;
			// 	for (difference_type j = 0; j >= first_pos; i++, j--) {
			// 		_alloc.construct(begin() + j + count, *(end() - i));
			// 		_alloc.destroy(end() - i);
			// 	}
			// 	for (size_type j = 0; j < count; first_pos++, j++)
			// 		_alloc.construct(begin() + first_pos, value);
			// 	return (iterator(begin() + first_pos));
			// }

			template <class InputIt>
			iterator	insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) {
				if (first == last)
					return (pos);
				// difference_type	first_pos = std::distance(begin(), pos);
				difference_type	first_pos = pos - begin();
				difference_type	ret = first_pos;
				size_type	count = static_cast<size_type>(std::distance(first, last));
				if (_count + count > _capacity * VECTOR_CAPACITY_ADJUSTMENT)
					_capacity = _count + count;
				else if (_count + count >= _capacity)
					_capacity = _count * VECTOR_CAPACITY_ADJUSTMENT;
				pointer	first_tmp = _alloc.allocate(_capacity);
				difference_type	i = 0;
				while (i < first_pos) {
					_alloc.construct(first_tmp + i, *(_first + i));
					i++;
				}
				while (first != last) {
					_alloc.construct(first_tmp + i, *first);
					++first;
					i++;
				}
				while ((size_type)first_pos < _count) {
					_alloc.construct(first_tmp + i, *(_first + first_pos));
					i++;
					first_pos++;
				}
				if (_capacity) {
					for (size_type i = 0; i < count; i++)
						_alloc.destroy(_first + i);
				}
				_alloc.deallocate(_first, _capacity);
				_first = first_tmp;
				_count += count;
				return (iterator(begin() + ret));
			}

			iterator	erase(iterator i) {
				iterator	tmp = i;
				while (i + 1 != end()) {
					_alloc.destroy(i);
					_alloc.construct(i, *(i + 1));
					i++;
				}
				_alloc.destroy(i);
				_count--;
				_last--;
				return (tmp);
			}

			iterator	erase(iterator first, iterator last) {
				iterator	ret = first;
				while (first != last) {
					erase(first);
					--last;
				}
				return (ret);
			}

			void	push_back(const T &value) {
				if (_count >= _capacity) {
					if (!_capacity)
						reserve(1);
					else
						reserve(_capacity * VECTOR_CAPACITY_ADJUSTMENT);
				}
				_alloc.construct(_last++, value);
				_count++;
			}

			void	pop_back() {
				_count--;
				_alloc.destroy(--_last);
			}

			void	resize(size_type count, T value = T()) {
				if (count > max_size())
					throw (std::length_error("vector::resize"));
				if (count < size()) {
					while (_count > count) {
						_alloc.destroy(_first + _count - 1);
						_count--;
					}
					_last = _first + _count;
				}
				else {
					if (count > _count * VECTOR_CAPACITY_ADJUSTMENT)
						reserve(count);
					else if (count > _capacity)
						reserve(_count * VECTOR_CAPACITY_ADJUSTMENT);
					for (size_type i = _count; i < count; i++, ++_last)
						_alloc.construct(_last, value);
					_count = count;
				}
			}

			void	swap(vector &other) {
				pointer			first_tmp = _first;
				pointer			last_tmp = _last;
				size_type		capacity_tmp = _capacity;
				allocator_type	alloc_tmp = _alloc;
				size_type		count_tmp = _count;
				_first = other._first;
				_last = other._last;
				_capacity = other._capacity;
				_alloc = other._alloc;
				_count = other._count;
				other._first = first_tmp;
				other._last = last_tmp;
				other._capacity = capacity_tmp;
				other._alloc = alloc_tmp;
				other._count = count_tmp;
			}

		private:

			/*** MEMBER OBJECTS ***/

			allocator_type	_alloc;
			size_type		_count;
			size_type		_capacity;
			pointer			_first;
			pointer			_last;

	};

	/*** NON-MEMBER FUNCTIONS ***/

	template< class T, class Alloc >
	bool	operator==(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template< class T, class Alloc >
	bool	operator!=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return (!(lhs == rhs));
	}

	template< class T, class Alloc >
	bool	operator<(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template< class T, class Alloc >
	bool	operator<=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return (!(lhs > rhs));
	}

	template< class T, class Alloc >
	bool	operator>(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
	}

	template< class T, class Alloc >
	bool	operator>=(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs) {
		return (!(lhs < rhs));
	}

	template< class T, class Alloc >
	void	swap(ft::vector<T, Alloc> &lhs, ft::vector<T, Alloc> &rhs) {
		lhs.swap(rhs);
	}

};

#endif
