#include "../srcs/vector.hpp"
#include "../srcs/stack.hpp"
#include "test.hpp"
#include "../srcs/map.hpp"

int	main() {

	ft::vector<int>	v;

	printVector(v);
	v.push_back(1);
	printVector(v);
	v.push_back(2);
	printVector(v);
	v.push_back(3);
	printVector(v);
	v.push_back(4);
	printVector(v);
	v.push_back(5);
	printVector(v);

	return (0);
}