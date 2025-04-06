#include "PmergeMe.hpp"

int count = 0;
int count_tmp = 0;

PmergeMe::PmergeMe()
{
	vec_.clear();
	deq_.clear();
}

PmergeMe::PmergeMe(const PmergeMe &other)
{
	vec_ = other.vec_;
	deq_ = other.deq_;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		vec_ = other.vec_;
		deq_ = other.deq_;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{

}

std::vector<std::vector<int> >	PmergeMe::CalculateVector(std::vector<std::vector<int> >& origin)
{
	if (origin.size() == 1)
	{
		return origin;
	}
	std::vector<std::vector<int> > arg;
	for (size_t n = 0; n + 1 < origin.size(); n += 2)
	{
		std::vector<int> tmp;
		if (origin[n].back() < origin[n + 1].back())
		{
			tmp.insert(tmp.end(), origin[n].begin(), origin[n].end());
			tmp.insert(tmp.end(), origin[n + 1].begin(), origin[n + 1].end());
		}
		else
		{
			tmp.insert(tmp.end(), origin[n + 1].begin(), origin[n + 1].end());
			tmp.insert(tmp.end(), origin[n].begin(), origin[n].end());
		}
		count++;
		arg.push_back(tmp);
	}
	count_tmp = count;
	std::vector<int> tmp = origin.back();
	std::vector<std::vector<int> > sorted = CalculateVector(arg);

	std::vector<std::vector<int> > ans;
	int flag = 1;
	int start = 0;
	int j = 1;
	size_t end = 1;
	while (flag)
	{
		if (end >= sorted.size())
		{
			end = sorted.size();
			flag = false;
		}
		for (size_t p = start; p < end; p++)
		{
			std::vector<int> big(sorted[p].begin() + sorted[p].size() / 2, sorted[p].end());
			ans.push_back(big);
		}
		int sub = 0;
		if (flag == false && origin.size() % 2)
		{
			ans.insert(MyBound(ans.begin(), ans.end(), tmp.back()), tmp);
			sub = 1;
		}
		std::vector<int> it_ve;
		for (int p = end; p > start; p--)
		{
			size_t it_end = start + p + sub - 1;
			for (std::vector<int>::iterator it = it_ve.begin(); it != it_ve.end(); it++)
			{
				if (sorted[p - 1][sorted[p - 1].size() - 1] >= *it)
					it_end++;
			}
			std::vector<int> small(sorted[p - 1].begin(), sorted[p - 1].begin() + sorted[p - 1].size() / 2);
			it_ve.push_back(sorted[p - 1][sorted[p - 1].size() / 2 - 1]);
			std::vector<std::vector<int> >::iterator pos = MyBound(ans.begin(), ans.begin() + it_end, sorted[p - 1][sorted[p - 1].size() / 2 - 1]);
			ans.insert(pos, small);
		}
		start = end;
		end = start + Jacob(j);
		j++;
	}
	count_tmp = count;
	return (ans);
}

std::deque<std::deque<int> >	PmergeMe::CalculateDeque(std::deque<std::deque<int> >& origin)
{
	if (origin.size() == 1)
	{
		return origin;
	}
	std::deque<std::deque<int> > arg;
	for (size_t n = 0; n + 1 < origin.size(); n += 2)
	{
		std::deque<int> tmp;
		if (origin[n].back() < origin[n + 1].back())
		{
			tmp.insert(tmp.end(), origin[n].begin(), origin[n].end());
			tmp.insert(tmp.end(), origin[n + 1].begin(), origin[n + 1].end());
		}
		else
		{
			tmp.insert(tmp.end(), origin[n + 1].begin(), origin[n + 1].end());
			tmp.insert(tmp.end(), origin[n].begin(), origin[n].end());
		}
		count++;
		arg.push_back(tmp);
	}
	count_tmp = count;
	std::deque<int> tmp = origin.back();
	std::deque<std::deque<int> > sorted = CalculateDeque(arg);

	std::deque<std::deque<int> > ans;
	int flag = 1;
	int start = 0;
	int j = 1;
	size_t end = 1;
	while (flag)
	{
		if (end >= sorted.size())
		{
			end = sorted.size();
			flag = false;
		}
		for (size_t p = start; p < end; p++)
		{
			std::deque<int> big(sorted[p].begin() + sorted[p].size() / 2, sorted[p].end());
			ans.push_back(big);
		}
		int sub = 0;
		if (flag == false && origin.size() % 2)
		{
			ans.insert(MyBound(ans.begin(), ans.end(), tmp.back()), tmp);
			sub = 1;
		}
		std::deque<int> it_ve;
		for (int p = end; p > start; p--)
		{
			size_t it_end = start + p + sub - 1;
			for (std::deque<int>::iterator it = it_ve.begin(); it != it_ve.end(); it++)
			{
				if (sorted[p - 1][sorted[p - 1].size() - 1] >= *it)
					it_end++;
			}
			std::deque<int> small(sorted[p - 1].begin(), sorted[p - 1].begin() + sorted[p - 1].size() / 2);
			it_ve.push_back(sorted[p - 1][sorted[p - 1].size() / 2 - 1]);
			std::deque<std::deque<int> >::iterator pos = MyBound(ans.begin(), ans.begin() + it_end, sorted[p - 1][sorted[p - 1].size() / 2 - 1]);
			ans.insert(pos, small);
		}
		start = end;
		end = start + Jacob(j);
		j++;
	}
	count_tmp = count;
	return (ans);
}

void	PmergeMe::SortVector()
{
	count = 0;
	clock_t	start = clock();
	ans_vec_ = CalculateVector(vec_);
	clock_t	end = clock();

	std::cout << "After:\t";
	for (long unsigned int n = 0; n < ans_vec_.size(); n++)
		std::cout << ans_vec_[n][0] << " ";
	std::cout << std::endl;
	double elapsed = double(end - start) / CLOCKS_PER_SEC * 1000;
	std::cout << "Time to process a range of " << std::setw(4) << std::setfill(' ') << ans_vec_.size() << " elements with std::vector : " << elapsed << " msec" << std::endl;
	#if DEBUG
	std::cout << count << std::endl;
	#endif
}

void	PmergeMe::SortDeque()
{
	count = 0;
	clock_t	start = clock();
	ans_deq_ = CalculateDeque(deq_);
	clock_t	end = clock();

#if DEBUG
	std::cout << "After:\t";
	for (long unsigned int n = 0; n < ans_deq_.size(); n++)
		std::cout << ans_deq_[n][0] << " ";
	std::cout << std::endl;
#endif
	double elapsed = double(end - start) / CLOCKS_PER_SEC * 1000;
	std::cout << "Time to process a range of " << std::setw(4) << std::setfill(' ') << ans_deq_.size() << " elements with std::deque  : " << elapsed << " msec" << std::endl;
	#if DEBUG
	std::cout << count << std::endl;
	#endif
}

int PmergeMe::Jacob(int n)
{
	return (static_cast<int>(pow(2, n) - pow((-1), n)) / 3 * 2);
}

void	PmergeMe::SortAll(int ac, char **av)
{
	long	tmp;
	char	*endptr;

	std::cout << "Before:\t";
	for (int n = 1; n < ac; n++)
	{
		tmp = strtol(*(av + n), &endptr, 10);
		if (*endptr != '\0' || tmp < 0 || tmp > std::numeric_limits<int>::max()) {
			std::cerr << "Error" << std::endl;
			return ;
		}
		std::cout << tmp << " ";
		vec_.push_back(std::vector<int>(1, tmp));
		deq_.push_back(std::deque<int>(1, tmp));
	}
	std::cout << std::endl;
	SortVector();
	SortDeque();
}
