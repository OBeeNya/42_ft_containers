#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "ft_containers.hpp"
# include "iterator_traits.hpp"
# include "iterator.hpp"

namespace	ft {

	template <class Iterator>
	class	reverse_iterator:
		public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
					typename ft::iterator_traits<Iterator>::value_type,
					typename ft::iterator_traits<Iterator>::difference_type,
					typename ft::iterator_traits<Iterator>::pointer,
					typename ft::iterator_traits<Iterator>::reference> {

		public:

			/*** MEMBER TYPES ***/

			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			/*** MEMBER FUNCTIONS ***/

			reverse_iterator(): current() {}

			explicit reverse_iterator(Iterator x): current(x) {}
	
			template <class U>
			reverse_iterator(const reverse_iterator<U> &u): current(u.base()) {}

			reference	operator*() const {
				Iterator	tmp = current;
				return (*--tmp);
			}

			reverse_iterator	operator+(difference_type d) const { return (reverse_iterator(current - d)); }

			reverse_iterator	&operator++() {
				--current;
				return (*this);
			}

			reverse_iterator	operator++(int) {
				reverse_iterator	tmp(*this);
				--current;
				return (tmp);
			}

			reverse_iterator	&operator+=(difference_type d) {
				current -= d;
				return (*this);
			}

			reverse_iterator	operator-(difference_type d) const { return (reverse_iterator(current + d)); }

			reverse_iterator	&operator--() {
				++current;
				return (*this);
			}

			reverse_iterator	operator--(int) {
				reverse_iterator	tmp(*this);
				++current;
				return (tmp);
			}

			reverse_iterator	&operator-=(difference_type d) {
				current += d;
				return (*this);
			}

			pointer	operator->() const {return &(operator*());}

			reference	operator[](difference_type d) const { return *(*this + d); }

			template <class U>
			reverse_iterator	&operator=(const reverse_iterator<U> &u) {
				current = u.base();
				return (*this);
			}

			Iterator	base() const { return (current); }

		protected:

			/*** ATTRIBUTES ***/

			Iterator	current;

	};

	/*** NON-MEMBER FUNCTIONS ***/

	template <class Iterator>
	reverse_iterator<Iterator>	operator+(typename reverse_iterator<Iterator>::difference_type d, const reverse_iterator<Iterator> &r) { return (reverse_iterator<Iterator>(r.base() - d)); }

	template <class I1, class I2>
	typename reverse_iterator<I1>::difference_type	operator-(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) { return (rhs.base() - lhs.base()); }

	template <class I1, class I2>
	bool	operator==(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) { return (lhs.base() == rhs.base()); }

	template <class I1, class I2>
	bool	operator!=(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) { return (lhs.base() != rhs.base()); }

	template <class I1, class I2>
	bool	operator<(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) { return (lhs.base() > rhs.base()); }

	template <class I1, class I2>
	bool	operator>(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) { return (lhs.base() < rhs.base()); }

	template <class I1, class I2>
	bool	operator<=(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) { return (lhs.base() >= rhs.base()); }

	template <class I1, class I2>
	bool	operator>=(const reverse_iterator<I1> &lhs, const reverse_iterator<I2> &rhs) { return (lhs.base() <= rhs.base()); }

};

#endif
