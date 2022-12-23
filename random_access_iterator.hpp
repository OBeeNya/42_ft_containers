#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"

namespace	ft {

	template <class T>
	class random_access_iterator:
		public ft::iterator<std::random_access_iterator_tag, T> {

		public:


	};

};

#endif
