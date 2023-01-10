#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_containers.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"

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
						++_end;
					}
				}

			template <class InputIt>
			vector(InputIt first, InputIt last, const Allocator &alloc = Allocator()):
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

			}

			/*** Element access ***/

			/*** Iterators ***/

			/*** Capacity ***/

			/*** Modifiers ***/

			void	clear() {
				while (_count--)
					_alloc.destroy(_first + _count);
				_last = _first;
				_count = 0;
			}

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
