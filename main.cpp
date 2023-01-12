#include "vector.hpp"
#include "stack.hpp"
#include "test.hpp"

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