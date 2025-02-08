#pragma once
# include <stack>
# include <string>
# include <iostream>
# include <limits>

class RPN
{
private:
	std::stack<int> cal;

	int	ErrorSegment(char c);

public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();

	void	Calculate(std::string &str);
};
