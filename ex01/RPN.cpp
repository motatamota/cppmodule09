#include "RPN.hpp"

RPN::RPN()
{

}

RPN::RPN(const RPN &other)
{
	cal = other.cal;
}

RPN &RPN::operator=(const RPN &other)
{
	if (this != &other)
	{
		cal = other.cal;
	}
	return (*this);
}

RPN::~RPN()
{

}

int	RPN::ErrorSegment(char c)
{
	if ((c > '9' || c < '0') && c != '+' && c != '-' && c != '*' && c != '/')
		return (1);
	return (0);
}

void	RPN::Calculate(std::string &str)
{
	long tmp;

	for (std::string::iterator itr = str.begin(); itr != str.end(); itr++)
	{
		if (itr == str.end() || ErrorSegment(*itr))
		{
			std::cerr << "Error" << std::endl;
			return ;
		}
		if (*itr >= '0' && *itr <= '9')
			cal.push(*itr - '0');
		else
		{
			if (cal.size() < 2)
			{
				std::cout << "Error: less contents" << std::endl;
				return ;
			}
			tmp = cal.top();
			cal.pop();
			if (*itr == '+')
				tmp += cal.top();
			else if (*itr == '-')
				tmp = cal.top() - tmp;
			else if (*itr == '*')
				tmp *= cal.top();
			else if (*itr == '/')
			{
				if (tmp == 0)
				{
					std::cout << "Error: div by zero" << std::endl;
					return ;
				}
				tmp = cal.top() / tmp;
			}
			else
				std::cout << "Error" << std::endl;
			cal.pop();
			if (tmp <  std::numeric_limits<int>::min() || tmp > std::numeric_limits<int>::max())
			{
				std::cerr << "Error: over flow" << std::endl;
				return ;
			}
			cal.push(tmp);
		}
		itr++;
		if (itr == str.end())
		{
			if (cal.size() != 1)
			{
				std::cerr << "Error" << std::endl;
				return ;
			}
			std::cout << cal.top() << std::endl;
			return ;
		}
		if (*itr != ' ')
		{
			std::cerr << "Error" << std::endl;
			return ;
		}
	}
}
