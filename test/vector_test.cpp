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
	std::cout << "Content of vector:" << std::endl;
	while (first != last) {
		std::cout << *first << std::endl;
		++first;
	}
	std::cout << std::endl;
}

int	main() {

	std::cout << "MEMBER FUNCTIONS" << std::endl;

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

	std::cout << "Element access" << std::endl;

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

	std::cout << "Iterators" << std::endl;

	{
		LIB::vector<int>	v;
		v.assign(5, 5);
		printVector(v);
		typename LIB::vector<int>::reverse_iterator	first = v.rbegin();
		typename LIB::vector<int>::reverse_iterator	last = v.rend();
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

	std::cout << "Modifiers" << std::endl;

	{
		LIB::vector<int>	v;
		v.assign(5, 5);
		printVector(v);
		v.clear();
		std::cout << *(v.begin()) << std::endl;
		printVector(v);
		v.insert(v.end(), 1);
		std::cout << v[0] << std::endl;
		v.insert(v.end(), 2);
		std::cout << v[1] << std::endl;
		printVector(v);
		v.insert(v.end(), 3, 3);
		printVector(v);
		v.insert(v.end(), v[0], v[2]);
		printVector(v);
		v.assign(5, 5);
		v.erase(v.begin() + 1, v.end());
		printVector(v);
		v.clear();
		v.assign(5, 5);
		v.push_back(6);
		printVector(v);
		v.pop_back();
		printVector(v);
		LIB::vector<int>	v2;
		v2.assign(7, 7);
		v.swap(v2);
		printVector(v);
		printVector(v2);
	}


	// std::cout << "NON-MEMBER FUNCTIONS" << std::endl;

	// {
	// 	LIB::vector<int>	v1;
	// 	v1.assign(5, 5);
	// 	LIB::vector<int>	v2;
	// 	v2.assign(7, 7);
	// 	if (v1 == v2)
	// 		std::cout << std::boolalpha << true << std::endl;
	// 	else
	// 		std::cout << std::boolalpha << false << std::endl;
	// 	if (v1 != v2)
	// 		std::cout << std::boolalpha << true << std::endl;
	// 	else
	// 		std::cout << std::boolalpha << false << std::endl;
	// 	if (v1 < v2)
	// 		std::cout << std::boolalpha << true << std::endl;
	// 	else
	// 		std::cout << std::boolalpha << false << std::endl;
	// 	if (v1 <= v2)
	// 		std::cout << std::boolalpha << true << std::endl;
	// 	else
	// 		std::cout << std::boolalpha << false << std::endl;
	// 	if (v1 > v2)
	// 		std::cout << std::boolalpha << true << std::endl;
	// 	else
	// 		std::cout << std::boolalpha << false << std::endl;
	// 	if (v1 >= v2)
	// 		std::cout << std::boolalpha << true << std::endl;
	// 	else
	// 		std::cout << std::boolalpha << false << std::endl;
	// 	LIB::swap(v1, v2);
	// 	printVector(v1);
	// 	printVector(v2);
	// }

	return (0);
}
