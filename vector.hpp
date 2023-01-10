#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_containers.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft {

	template <class T, class Allocator = std::allocator<T>>
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
			typedef typename ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			/*** MEMBER FUNCTIONS ***/

			vector():
				_alloc(NULL),
				_count(0),
				_capacity(0),
				_first(nullptr),
				_last(nullptr) {}

			explicit vector(const Allocator &alloc):
				_alloc(alloc),
				_count(0),
				_capacity(0),
				_first(nullptr),
				_last(nullptr) {
					_first = _alloc.allocate(1);
					_last = _first;
				}

			explicit vector(size_type count, const T &value = T(), const Allocator &alloc = Allocator()):
				_alloc(alloc),
				_count(count),
				_capacity(count),
				_first(nullptr),
				_last(nullptr) {
					_first = _alloc.allocate(_capacity);
					_last = _first;
					for (size_type i = 0; i < _capacity; i++) {
						_alloc.construct(_last, value);
						++_last;
					}
				}

			template <class InputIt>
			vector(InputIt first, InputIt last, const Allocator &alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr):
				_alloc(alloc),
				_count(std::distance(first, last)),
				_capacity(std::distance(first, last)),
				_first(nullptr),
				_last(nullptr) {
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
				_first(nullptr),
				_last(nullptr) {
					_first = _alloc.allocate(_capacity);
					_last = _first;
					for (pointer i = other._first; i < other._last; ++i, ++_last)
						_alloc.construct(_last, *i);
				}

			~vector() {
				clear();
				if (_first != nullptr || _first == _last)
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
			void	assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr) {
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
				if (!(pos < size()))
					throw (std::out_of_range("vector::at"));
				return (*(_first + pos));
			}

			const_reference	at(size_type pos) const {
				if (!(pos < size()))
					throw (std::out_of_range("vector::at"));
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
				return (size());
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
					+b;
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

			iterator	insert(const_iterator pos, const T &value) {
				difference_type	first_pos = std::distance(begin(), pos);
				insert(pos, 1, value);
				return (iterator(begin() + first_pos));
			}

			iterator	insert(const_iterator pos, size_type count, const T &value) {
				if (!count)
					return (pos);
				difference_type	first_pos = std::distance(begin(), pos);
				difference_type	pos_last = std::distance(pos, end());
				difference_type	first_last = size();
				if (count + _count >= _capacity * VECTOR_CAPACITY_ADJUSTMENT)
					reserve(count + _count);
				else if (count + _count > _capacity)
					reserve(_count * VECTOR_CAPACITY_ADJUSTMENT);
				for (difference_type i = 1; i <= pos_last; i++) {
					_alloc.construct(_first + first_last + count - i, *(_first + first_last - i));
					_alloc.destroy(_first, first_last - i);
				}
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_first + first_pos + i, value);
				_last = _first + _count + count;
				_count += count;
				return (iterator(begin() + first_pos));
			}

			template <class InputIt>
			iterator	insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = nullptr) {
				if (first == last)
					return (pos);
				difference_type	first_pos = std::distance(begin(), pos);
				difference_type	pos_last = std::distance(pos, end());
				difference_type	first_last = size();
				size_type	count = static_cast<size_type>(std::distance(first, last));
				if (count + _count >= _capacity * VECTOR_CAPACITY_ADJUSTMENT)
					reserve(count + _count);
				else if (count + _count > _capacity)
					reserve(_count * VECTOR_CAPACITY_ADJUSTMENT);
				for (difference_type i = 1; i <= pos_last; i++) {
					_alloc.construct(_first + first_last + count - i, *(_first + first_last - i));
					_alloc.destroy(_first + first_last - i);
				}
				for (size_type i = 0; i < count; i++) {
					_alloc.construct(_first + first_last + i, *first);
					++first;
				}
				_last = _first + _count + count;
				_count += count;
				return (iterator(begin() + first_pos));
			}

			iterator	erase(iterator pos) {
				iterator	ret = pos;
				while (pos != end() - 1) {
					_alloc.destroy(pos);
					_alloc.construct(pos, *(pos + 1));
					++pos;
				}
				_alloc.destroy(pos);
				_count--;
				--_last;
				return (ret);
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
				_alloc.construct(++_last, value);
				_count++;
			}

			void	pop_back() {
				_count--;
				_alloc.destroy(_first + _count);
			}

			// void	resize(size_type count, T value = T()) {
			// 	if (count > max_size())
			// 		throw (std::length_error("vector::resize"));

			// }

		private:

			/*** ATTRIBUTES ***/

			allocator_type	_alloc;
			size_type		_count;
			size_type		_capacity;
			pointer			_first;
			pointer			_last;

	};

};

/*** NON-MEMBER FUNCTIONS ***/

#endif
