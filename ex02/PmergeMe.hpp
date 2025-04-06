#pragma once
# include <vector>
# include <deque>
# include <string>
# include <iostream>
# include <limits>
# include <ctime>
# include <cstdlib>
# include <cmath>
# include <algorithm>
# include <iomanip>
# define DEBUG 1

extern int count;
class PmergeMe
{
private:
	std::vector<std::vector<int> >	vec_;
	std::vector<std::vector<int> >	ans_vec_;
	std::deque<std::deque<int> >	deq_;
	std::deque<std::deque<int> >	ans_deq_;
	int					tmp;

	void				SortVector();
	void				SortDeque();
	int					Jacob(int n);
	template<typename T>
	T MyBound(T first, T last, int val);
	std::vector<std::vector<int> >				CalculateVector(std::vector<std::vector<int> >& origin);
	std::deque<std::deque<int> >				CalculateDeque(std::deque<std::deque<int> >& origin);

public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
	void	SortAll(int ac, char **av);
};

template<typename T>
T PmergeMe::MyBound(T first, T last, int val)
{
while (first < last) {
	T mid = first + (last - first) / 2;
	if (mid->back() < val) {
		first = mid + 1;
	} else {
		last = mid;
	}
	count++;
}
return first;
}
