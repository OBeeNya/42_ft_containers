#include "../srcs/vector.hpp"

// random_access_iterator.hpp useless after all?

template<typename T>
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

int	main() {

	/*** MEMBER FUNCTIONS ***/

	{
		LIB::vector<int>	v1;
		std::allocator<int>	a;
		LIB::vector<int>	v2(a);
		LIB::vector<int>	v3(5);
		int					i[4] = {0, 1, 2, 3};
		LIB::vector<int>	v4(i[1], i[2]);
		LIB::vector<int>	v5(v4);

		printVector(v1);
		printVector(v2);
		printVector(v3);
		printVector(v4);
		printVector(v5);
	}

	{
		int					i[4] = {0, 1, 2, 3};
		LIB::vector<int>	v1(i[1], i[2]);
		LIB::vector<int>	v2;
		v2 = v1;
		printVector(v2);
	}


	{
		int					i[4] = {0, 1, 2, 3};
		LIB::vector<int>	v;
		v.assign(i[1], i[2]);
		printVector(v);
	}

	/*** Element access ***/

	{
		int					i[4] = {0, 1, 2, 3};
		LIB::vector<int>	v(i[1], i[2]);
		std::cout << v.at(0) << std::endl;
		try {
			std::cout << v.at(6) << std::endl;
		}
		catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}

	{
		int					i[4] = {0, 1, 2, 3};
		LIB::vector<int>	v(i[1], i[3]);
		std::cout << v[0] << std::endl;
		std::cout << v.front() << std::endl;
		std::cout << v.back() << std::endl;
		std::cout << *(v.data()) << std::endl;
	}

	/*** Iterators ***/

	{

	}

	return (0);
}
