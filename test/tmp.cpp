#include "../srcs/set.hpp"
#include "../srcs/map.hpp"

int	main() {

	// ft::set<int>	a;
	// for (int i = 1; i < 50; i++)
	// 	a.insert(i);
	// a.erase(60);

	ft::map<char, int>	m;
	m.insert(ft::pair<char, int>('a', 1.0));
	std::cout << m.erase('a') << std::endl;
	// m.erase(m.begin());

	return (0);

}
