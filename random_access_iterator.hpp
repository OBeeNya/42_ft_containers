#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "ft_containers.hpp"
# include "iterator.hpp"

namespace	ft {

	template <class T>
	class random_access_iterator:
		public ft::iterator<std::random_access_iterator_tag, T> {

		public:
		
			/*** ATTRIBUTES ***/

			typedef T																				iterator_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category	iterator_category;

			/*** CONSTRUCTOR / DESTRUCTOR ***/

			random_access_iterator(): _i() {}
			random_access_iterator(const random_access_iterator &src): \
				_i(src.base()) {}
			~random_access_iterator() {}

			/*** OPERATOR OVERLOAD ***/

			random_access_iterator	&operator=(const random_access_iterator &rhs) {
				if (this != &rhs) _i = rhs._i;
				return (*this);
			}

			reference				operator*() const {return (*_i);}

			pointer					operator->() const { return &(operator*()); }

			random_access_iterator	&operator++() {
				++_i;
				return (*this);
			}

			random_access_iterator	operator++(int) {
				random_access_iterator	r(*this);
				++(*this);
				return (r);
			}

			random_access_iterator	&operator--() {
				--_i;
				return (*this);
			}

			random_access_iterator	operator--(int) {
				random_access_iterator	r(*this);
				--(*this);
				return (r);
			}

			random_access_iterator	&operator+=(difference_type d) {
				_i += d;
				return (*this);
			}

			random_access_iterator	&operator-=(difference_type d) {
				*this += -d;
				return (*this);
			}

			reference	operator[](difference_type d) const { return (_i[d]); }

			/*** MEMBER FUNCTIONS ***/

			iterator_type	base() const { return (_i); }

		private:

			/*** ATTRIBUTES ***/

			iterator_type	_i;

	};

};

template <class I1>
bool	operator==(const random_access_iterator<I1> lhs, const random_access_iterator<I1> rhs) {
	return (lhs.base() == rhs.base());
}

template <class I1, class I2>
bool	operator==(const random_access_iterator<I1> lhs, const random_access_iterator<I2> rhs) {
	return (lhs.base() == rhs.base());
}

template <class I1>
bool	operator!=(const random_access_iterator<I1> lhs, const random_access_iterator<I1> rhs) {
	return !(lhs.base() == rhs.base());
}

template <class I1, class I2>
bool	operator!=(const random_access_iterator<I1> lhs, const random_access_iterator<I2>rhs) {
	return !(lhs.base() == rhs.base());
}

random_access_iterator	operator+(difference_type d) const {
	random_access_iterator	r(*this);
	r += d;
	return (r);
}

template <class I1>
random_access_iterator<I1>	operator+(typename random_access_iterator<I1>::difference_type d, random_access_iterator<I1> rhs) {
	rhs += d;
	return (r);
}

random_access_iterator	operator-(difference_type d) const { return (*this + (-d)); }

template <class I1, class I2>
typename random_access_iterator<I1>::difference_type	operator-(const random_access_iterator<I1> &lhs, const random_access_iterator<I2> &rhs) {
	return (lhs.base() - rhs.base());
}

template <class I1>
bool	operator<(const random_access_iterator<I1> &lhs, const random_access_iterator<I1> &rhs) {
	return (lhs.base() < rhs.base());
}

template <class I1, class I2>
bool	operator<(const random_access_iterator<I1> &lhs, const random_access_iterator<I2> &rhs) {
	return (lhs.base() < rhs.base());
}

template <class I1>
bool	operator>(const random_access_iterator<I1> &lhs, const random_access_iterator<I1> &rhs) {
	return (rhs < lhs);
}

template <class I1, class I2>
bool	operator>(const random_access_iterator<I1> &lhs, const random_access_iterator<I2> &rhs) {
	return (rhs < lhs);
}

template <class I1>
bool	operator<=(const random_access_iterator<I1> &lhs, const random_access_iterator<I1> &rhs) {
	return !(rhs < lhs);
}

template <class I1, class I2>
bool	operator<=(const random_access_iterator<I1> &lhs, const random_access_iterator<I2> &rhs) {
	return !(rhs < lhs);
}

template <class I1>
bool	operator>=(const random_access_iterator<I1> &lhs, const random_access_iterator<I1> &rhs) {
	return !(lhs < rhs);
}

template <class I1, class I2>
bool	operator>=(const random_access_iterator<I1> &lhs, const random_access_iterator<I2> &rhs) {
	return !(lhs < rhs);
}

#endif
