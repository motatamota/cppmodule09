#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	BitcoinExchange exchanger;

	if (ac != 2)
	{
		std::cout << "Usage:" << std::endl;
		std::cout << "./btc inputfilepath" << std::endl;
		return (1);
	}
	if (exchanger.CreateRateList("cpp_09/data.csv"))
		return (1);
	exchanger.OutputExchangeResult(*(av + 1));
}
