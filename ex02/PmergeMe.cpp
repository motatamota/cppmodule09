#include "PmergeMe.hpp"

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

void	PmergeMe::CalculateVector(long unsigned int num)
{
	if (num > vec_.size())
	{
#if DEBUG
		std::cout << "narabikae owari" << std::endl;
#endif
		return ;
	}
	for (std::vector<int>::iterator n = vec_.begin() + 2 * num - 1; n < vec_.end(); n += 2 * num)
	{
		if (*n < *(n - num))
			std::swap_ranges(n - num + 1, n + 1, n - num - num + 1);
	}
#if DEBUG
	std::cout<< "current sinsuu " << num << ": ";
	for (long unsigned int n = 0; n < vec_.size(); n++)
		std::cout << vec_[n] << ", ";
	std::cout << std::endl;
#endif

	CalculateVector(num * 2);
	int count = tmp;
	for (std::vector<int>::iterator n = vec_.begin() + num - 1; n < vec_.end(); n += 2 * num)
	{
		std::vector<int>::iterator it = std::lower_bound(ans_vec_.begin(), std::min(ans_vec_.begin() + 2 * count, ans_vec_.end()), *n);
		ans_vec_.insert(it, *n);
		count++;
		#if DEBUG
			std::cout<< "current answer box: ";
			for (long unsigned int n = 0; n < ans_vec_.size(); n++)
				std::cout << ans_vec_[n] << ", ";
			std::cout << std::endl;
		#endif
	}
	if ((vec_.size() / num) % 2)
		tmp++;
}

void	PmergeMe::CalculateDeque(long unsigned int num)
{
	if (num > deq_.size())
	{
#if DEBUG
		std::cout << "narabikae owari" << std::endl;
#endif
		return ;
	}
	for (std::deque<int>::iterator n = deq_.begin() + 2 * num - 1; n < deq_.end(); n += 2 * num)
	{
		if (*n < *(n - num))
			std::swap_ranges(n - num + 1, n + 1, n + 1 - num - num);
	}

#if DEBUG
	std::cout<< "current sinsuu " << num << ": ";
	for (long unsigned int n = 0; n < deq_.size(); n++)
		std::cout << deq_[n] << ", ";
	std::cout << std::endl;
#endif

	CalculateDeque(num * 2);
	int count = tmp;
	for (std::deque<int>::iterator n = deq_.begin() + num - 1; n < deq_.end(); n += 2 * num)
	{
		std::deque<int>::iterator it = std::lower_bound(ans_deq_.begin(), std::min(ans_deq_.begin() + 2 * count, ans_deq_.end()), *n);
		ans_deq_.insert(it, *n);
		count++;
		#if DEBUG
			std::cout<< "current answer box: ";
			for (long unsigned int n = 0; n < ans_deq_.size(); n++)
				std::cout << ans_deq_[n] << ", ";
			std::cout << std::endl;
		#endif
	}
	if ((deq_.size() / num) % 2)
		tmp++;
}

void	PmergeMe::SortVector()
{
	tmp = 0;
	clock_t	start = clock();
	CalculateVector(1);
	clock_t	end = clock();

	std::cout << "After:\t";
	for (long unsigned int n = 0; n < ans_vec_.size(); n++)
		std::cout << ans_vec_[n] << " ";
	std::cout << std::endl;
	double elapsed = double(end - start) / CLOCKS_PER_SEC * 1000;
	std::cout << "Time to process a range of " << std::setw(4) << std::setfill(' ') << ans_vec_.size() << " elements with std::vector : " << elapsed << " msec" << std::endl;
}

void	PmergeMe::SortDeque()
{
	tmp = 0;
	clock_t	start = clock();
	CalculateDeque(1);
	clock_t	end = clock();

#if 0
	std::cout << "After:\t";
	for (long unsigned int n = 0; n < ans_vec_.size(); n++)
		std::cout << ans_vec_[n] << " ";
	std::cout << std::endl;
#endif
	double elapsed = double(end - start) / CLOCKS_PER_SEC * 1000;
	std::cout << "Time to process a range of " << std::setw(4) << std::setfill(' ') << ans_deq_.size() << " elements with std::deque  : " << elapsed << " msec" << std::endl;
}

void	PmergeMe::SortAll(int ac, char **av)
{
	long	tmp;
	char	*endptr;

	for (int n = 1; n < ac; n++)
	{
		tmp = strtol(*(av + n), &endptr, 10);
		if (*endptr != '\0' || tmp < 0 || tmp > std::numeric_limits<int>::max()) {
			std::cerr << "Error" << std::endl;
			return ;
		}
		vec_.push_back(tmp);
		deq_.push_back(tmp);
	}
	std::cout << "Before:\t";
	for (long unsigned int n = 0; n < vec_.size(); n++)
		std::cout << vec_[n] << " ";
	std::cout << std::endl;
	SortVector();
	SortDeque();
}
