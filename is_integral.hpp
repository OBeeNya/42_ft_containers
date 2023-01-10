#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include "ft_containers.hpp"

namespace	ft {

	template <class T, T v>
	struct integral_constant {
		typedef T									value_type;
		typedef integral_constant<value_type, v>	type;
		static const value_type						value = v;

		operator	value_type() {
			return (v);
		}
	};

	typedef integral_constant<bool, true>	int_type;
	typedef integral_constant<bool, false>	not_int_type;

	template <class T>
	struct is_integral:
		public not_int_type {};
	template <> struct is_integral<bool>:
		public int_type {};
	template <> struct is_integral<char>:
		public int_type {};
	template <> struct is_integral<wchar_t>:
		public int_type {};
	template <> struct is_integral<signed char>:
		public int_type {};
	template <> struct is_integral<short int>:
		public int_type {};
	template <> struct is_integral<int>:
		public int_type {};
	template <> struct is_integral<long int>:
		public int_type {};
	template <> struct is_integral<long long int>:
		public int_type {};
	template <> struct is_integral<unsigned char>:
		public int_type {};
	template <> struct is_integral<unsigned short int>:
		public int_type {};
	template <> struct is_integral<unsigned int>:
		public int_type {};
	template <> struct is_integral<unsigned long int>:
		public int_type {};
	template <> struct is_integral<unsigned long long int>:
		public int_type {};

};

#endif
