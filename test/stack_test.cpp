#include "../srcs/stack.hpp"

template<typename T>
void	printStack	(LIB::stack<T> &s) {
	std::cout << "Stack size: " << s.size() << std::endl;
	if (s.size())
		std::cout << "Stack top element: " << s.top() << std::endl;
	std::cout << "Is the stack empty: " << std::boolalpha << s.empty() << std::endl;
	std::cout << std::endl;
}

int	main() {

	std::cout << "MEMBER FUNCTIONS" << std::endl;

	{
		LIB::stack<std::string>	s1;
		s1.push("hello");
		printStack(s1);

		LIB::stack<std::string>	s2(s1);
		printStack(s2);

		LIB::vector<std::string>	v;
		LIB::stack< std::string, LIB::vector<std::string> >	s3(v);
		printStack(s2);
	}

	{
		std::string	l[4] = {"bonjour", "hello", "buenos dias", "konichiwa"};
		LIB::stack<std::string>	s1;
		for (int i = 0; i < 4; i++)
			s1.push(l[i]);
		LIB::stack<std::string>	s2;
		s2 = s1;
		printStack(s2);
	}

	std::cout << "Element access" << std::endl;

	{
		std::string	l[4] = {"bonjour", "hello", "buenos dias", "konichiwa"};
		LIB::stack<std::string>	s1;
		for (int i = 0; i < 4; i++)
			s1.push(l[i]);
		std::cout << "Stack top element: " << s1.top() << std::endl;
	}

	std::cout << "Modifiers" << std::endl;

	{
		LIB::stack<std::string>	s;
		s.push("aaaaaaa");
		s.push("bbbbbbbb");
		s.push("aaaaaaa");
		s.push("bbbbbbbb");
		s.push("aaaaaaa");
		s.push("bbbbbbbb");
		s.push("aaaaaaa");
		s.push("bbbbbbbb");
		s.pop();
		printStack(s);
	}

	std::cout << "NON-MEMBER FUNCTIONS" << std::endl;

	{
		LIB::stack<std::string>	s1;
		s1.push("abc");
		s1.push("def");
		LIB::stack<std::string>	s2;
		s2.push("ghi");
		s2.push("jkl");
		if (s1 == s2)
			std::cout << std::boolalpha << true << std::endl;
		else
			std::cout << std::boolalpha << false << std::endl;
		if (s1 != s2)
			std::cout << std::boolalpha << true << std::endl;
		else
			std::cout << std::boolalpha << false << std::endl;
		if (s1 < s2)
			std::cout << std::boolalpha << true << std::endl;
		else
			std::cout << std::boolalpha << false << std::endl;
		if (s1 <= s2)
			std::cout << std::boolalpha << true << std::endl;
		else
			std::cout << std::boolalpha << false << std::endl;
		if (s1 > s2)
			std::cout << std::boolalpha << true << std::endl;
		else
			std::cout << std::boolalpha << false << std::endl;
		if (s1 >= s2)
			std::cout << std::boolalpha << true << std::endl;
		else
			std::cout << std::boolalpha << false << std::endl;
		printStack(s1);
		printStack(s2);
	}

	return (0);

}
