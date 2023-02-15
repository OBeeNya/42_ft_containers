#ifndef NULL_PTR_HPP
# define NULL_PTR_HPP

# include "ft_containers.hpp"

namespace	ft {

	const class	null_ptr_t {

		public:

			template<class T>
			operator	T*() const {
				return (0);
			}

			template<class C, class T>
			operator	T C::*() const {
				return (0);
			}

			private:

				void	operator&() const;

	} null_ptr = {};

};

#endif
