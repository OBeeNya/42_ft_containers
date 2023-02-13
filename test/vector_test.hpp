#ifndef TEST_HPP
# define TEST_HPP

# include "../includes/ft_containers.hpp"

template< typename T >
void	printVector	(LIB::vector<T> &v) {
	typename LIB::vector<T>::iterator	first = v.begin();
	typename LIB::vector<T>::iterator	last = v.end();
	std::cout << "Vector size: " << v.size() << std::endl;
	std::cout << "Vector max_size: " << v.max_size() << std::endl;
	std::cout << "Vector capacity: " << v.capacity() << std::endl;
	std::cout << "Is the vector empty: " << std::boolalpha << v.empty() << std::endl;
	std::cout << "Content of vector :" << std::endl;
	while (first != last) {
		std::cout << *first << std::endl;
		++first;
	}
	std::cout << std::endl;
}

#endif
