#ifndef EQUAL_HPP
# define EQUAL_HPP

# include "ft_containers.hpp"

namespace	ft {

	template <class I1, class I2>
	bool	equal(I1 first1, I1 last1, I2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2))
				return (false);
		}
    	return (true);
	};

	template <class I1, class I2, class BinaryPredicate>
	bool	equal(I1 first1, I1 last1, I2 first2, BinaryPredicate pred) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!pred(*first1, *first2))
				return (false);
		}
		return (true);
	};

};

#endif
