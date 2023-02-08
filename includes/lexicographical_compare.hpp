#ifndef LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

# include "ft_containers.hpp"

namespace	ft {

	template <class I1, class I2>
	bool	lexicographical_compare(I1 first1, I1 last1, I2 first2, I2 last2) {
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
			if (*first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	};

	template <class I1, class I2, class Compare>
	bool	lexicographical_compare(I1 first1, I1 last1, I2 first2, I2 last2, Compare comp) {
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return ((first1 == last1) && (first2 != last2));
	};

};

#endif
