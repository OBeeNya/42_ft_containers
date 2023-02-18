#include "../srcs/map.hpp"

void	printMap(LIB::map<char, double> m) {
	std::cout << "Is map empty: " << std::boolalpha << m.empty() << std::endl;
	std::cout << "Size of the map: " << m.size() << std::endl;
	std::cout << "Max size of the map: " << m.max_size() << std::endl;
	std::cout << "Content of the map: " << std::endl;
	LIB::map<char, double>::iterator	it = m.begin();
	while (it != m.end()) {
		std::cout << it->first << " // " << it->second << std::endl;
		it++;
	}
}

int	main() {

	std::cout << "MEMBER FUNCTIONS" << std::endl;

	{
		LIB::map<char, double>	m1;
		m1.insert(LIB::pair<char, double>('a', 1.0));
		m1.insert(LIB::pair<char, double>('b', 2.0));
		m1.insert(LIB::pair<char, double>('c', 3.0));
		m1.insert(LIB::pair<char, double>('d', 4.0));
		m1.insert(LIB::pair<char, double>('e', 5.0));
		printMap(m1);
		LIB::map<char, double>	m2 = LIB::map<char, double>(std::less<char>());
		m2.insert(LIB::pair<char, double>('a', 1.0));
		printMap(m2);
		LIB::map<char, double>	m3(m1.begin(), m1.end());
		printMap(m3);
		LIB::map<char, double>	m4(m3);
		printMap(m4);
		LIB::map<char, double>	m5 = m4;
		printMap(m5);
	}

	std::cout << "Element access" << std::endl;

	{
		LIB::map<char, double>	m;
		m.insert(LIB::pair<char, double>('a', 1.0));
		m.insert(LIB::pair<char, double>('b', 2.0));
		m.insert(LIB::pair<char, double>('c', 3.0));
		m.insert(LIB::pair<char, double>('d', 4.0));
		m.insert(LIB::pair<char, double>('e', 5.0));
		std::cout << m.at('a') << std::endl;
		std::cout << m.at('c') << std::endl;
		std::cout << m.at('e') << std::endl;
		// try {
		// 	std::cout << m.at('f') << std::endl;
		// }
		// catch (std::exception &e) {
		// 	std::cout << e.what() << std::endl;
		// }
	}

	std::cout << "Iterators" << std::endl;

	{
		LIB::map<char, double>	m;
		m.insert(LIB::pair<char, double>('a', 1.0));
		m.insert(LIB::pair<char, double>('b', 2.0));
		m.insert(LIB::pair<char, double>('c', 3.0));
		m.insert(LIB::pair<char, double>('d', 4.0));
		m.insert(LIB::pair<char, double>('e', 5.0));
		LIB::map<char, double>::reverse_iterator	rb = m.rbegin();
		LIB::map<char, double>::reverse_iterator	re = m.rend();
		while (rb != re) {
			std::cout << rb->first << " // " << rb->second << std::endl;
			rb++;
		}
	}

	std::cout << "Modifiers" << std::endl;

	{
		LIB::map<char, double>	m;
		m.insert(LIB::pair<char, double>('a', 1.0));
		m.insert(LIB::pair<char, double>('b', 2.0));
		m.insert(LIB::pair<char, double>('c', 3.0));
		m.insert(LIB::pair<char, double>('d', 4.0));
		m.insert(LIB::pair<char, double>('e', 5.0));
		m.clear();
		printMap(m);
	
		m.insert(m.begin(), LIB::pair<char, double>('f', 6.0));
		printMap(m);
	
		LIB::map<char, double>	m2;
		m2.insert(m.begin(), m.end());
		printMap(m2);
	
		m2.erase(m2.begin());
		m2.erase(m2.begin(), m2.end());
		printMap(m2);
	
		m.erase('f');
		printMap(m);
	
		m.erase('h');
		printMap(m);
	
		m.clear();
		m2.clear();
		m.insert(LIB::pair<char, double>('a', 1.0));
		m.insert(LIB::pair<char, double>('b', 2.0));
		m2.insert(LIB::pair<char, double>('c', 3.0));
		m2.insert(LIB::pair<char, double>('d', 4.0));
		m2.insert(LIB::pair<char, double>('e', 5.0));
		m.swap(m2);
		printMap(m);
		printMap(m2);
	}

	std::cout << "Lookup" << std::endl;

	{
		LIB::map<char, double>	m;
		m.insert(LIB::pair<char, double>('a', 1.0));
		m.insert(LIB::pair<char, double>('b', 2.0));
		m.insert(LIB::pair<char, double>('c', 3.0));
		m.insert(LIB::pair<char, double>('d', 4.0));
		m.insert(LIB::pair<char, double>('e', 5.0));
		std::cout << m.count('a') << std::endl;
		std::cout << m.count('f') << std::endl;
	}

	{
		LIB::map<char, double>	m;
		m.insert(LIB::pair<char, double>('a', 1.0));
		m.insert(LIB::pair<char, double>('b', 2.0));
		m.insert(LIB::pair<char, double>('c', 3.0));
		LIB::map<char, double>::iterator	i1 = m.find('a');
		std::cout << "i1: " << i1->first << " // " << i1->second << std::endl;
		LIB::map<char, double>::iterator	i2 = m.find('d');
		std::cout << "i2: " << i2->first << " // " << i2->second << std::endl;
	}

	return (0);

}
