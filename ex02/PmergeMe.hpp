#pragma once
# include <vector>
# include <deque>
# include <string>
# include <iostream>
# include <limits>
# include <ctime>
# include <cstdlib>
# include <algorithm>
# include <iomanip>
# define DEBUG 0

class PmergeMe
{
private:
	std::vector<int>	vec_;
	std::vector<int>	ans_vec_;
	std::deque<int>		deq_;
	std::deque<int>		ans_deq_;

	void	SortVector();
	void	SortDeque();
	void	CalculateVector(long unsigned int num);
	void	CalculateDeque(long unsigned int num);

public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
	void	SortAll(int ac, char **av);
};
