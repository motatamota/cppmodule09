#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	PmergeMe	merge;

	if (ac == 1)
	{
		std::cout << "Error: No arguments" << std::endl;
		return (0);
	}
	merge.SortAll(ac, av);
}
