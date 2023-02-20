#ifndef EQUAL_HPP
# define EQUAL_HPP

# include "ft_containers.hpp"

namespace	ft {

	template <class I1, class I2>
	bool	equal(I1 first1, I1 last1, I2 first2, I2 last2) {
		while (first1 != last1 && first2 != last2) {
			if (*first1 != *first2)
				return (false);
			first1++;
			first2++;
		}
		if (first1 != last1 || first2 != last2)
			return (false);
    	return (true);
	};

};

#endif
