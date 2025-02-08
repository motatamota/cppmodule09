#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	rate_data_ = other.rate_data_;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		rate_data_ = other.rate_data_;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{

}

int	BitcoinExchange::IsThisDay(const t_data &data)
{
	if (data.year < 0 || data.month < 0 || data.date < 0 || data.rate < 0 ||
		data.year > 2025 || data.month > 12 || data.date > 31)
		return (0);
	if (data.year > 2025 ||
		(data.year == 2025 && data.month > 1) ||
		(data.year == 2025 && data.month == 1 && data.date > 1))
		return (0);
	return (1);
}

int BitcoinExchange::CreateRate(const std::string &day)
{
	std::string::const_iterator i;
	std::istringstream oss(day);
	t_data	data;
	char	c;

	if (!(oss >> data.year))
	{
		std::cerr << "Error: " << day << ": is not year" << std::endl;
		return (1);
	}
	oss >> c;
	if (c != '-')
	{
		std::cerr << "Error: " << day << ": unknown format" << std::endl;
		return (1);
	}
	if (!(oss >> data.month))
	{
		std::cerr << "Error: " << day << ": is not month" << std::endl;
		return (1);
	}
	oss >> c;
	if (c != '-')
	{
		std::cerr << "Error: " << day << ": unknown format" << std::endl;
		return (1);
	}
	if (!(oss >> data.date))
	{
		std::cerr << "Error: " << day << ": is not date" << std::endl;
		return (1);
	}
	oss >> c;
	if (c != ',')
	{
		std::cerr << "Error: " << day << ": unknown format" << std::endl;
		return (1);
	}
	if (!(oss >> data.rate))
	{
		std::cerr << "Error: " << day << ": is not rate" << std::endl;
		return (1);
	}
	if (!std::isfinite(data.rate))
	{
		std::cerr << "Error: " << day << ": is not rate" << std::endl;
		return (1);
	}
	if (!IsThisDay(data))
	{
		std::cerr << "Error: " << day << ": out of range day" << std::endl;
		return (1);
	}
	rate_data_.push_back(data);
	return (0);
}

int	BitcoinExchange::IsLate(const t_data &src, const t_data &list)
{
	if (src.year > list.year ||
		(src.year == list.year && src.month > list.month) ||
		(src.year == list.year && src.month == list.month && src.date >= list.date))
		return (1);
	return (0);
}

int BitcoinExchange::SearchRate(const std::string &day)
{
	std::string::const_iterator i;
	std::istringstream oss(day);
	t_data	data;
	char	c;

	if (!(oss >> data.year))
	{
		std::cerr << "Error: " << day << ": is not year" << std::endl;
		return (1);
	}
	oss >> c;
	if (c != '-')
	{
		std::cerr << "Error: bad input => " << day << std::endl;
		return (1);
	}
	if (!(oss >> data.month))
	{
		std::cerr << "Error: " << day << ": is not month" << std::endl;
		return (1);
	}
	oss >> c;
	if (c != '-')
	{
		std::cerr << "Error: bad input => " << day << std::endl;
		return (1);
	}
	if (!(oss >> data.date))
	{
		std::cerr << "Error: " << day << ": is not date" << std::endl;
		return (1);
	}
	oss >> c;
	if (c != '|')
	{
		std::cerr << "Error: bad input => " << day << std::endl;
		return (1);
	}
	if (!(oss >> data.rate))
	{
		std::cerr << "Error: " << day << ": is not rate" << std::endl;
		return (1);
	}
	if (data.rate > std::numeric_limits<int>::max())
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (1);
	}
	if (data.rate < std::numeric_limits<int>::min())
	{
		std::cerr << "Error: too minimam a number." << std::endl;
		return (1);
	}
	if (data.rate < 0)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (1);
	}
	if (!IsThisDay(data))
	{
		std::cerr << "Error: " << day << ": out of range day" << std::endl;
		return (1);
	}
	std::vector<t_data>::iterator p;
	for (p = rate_data_.begin(); p < rate_data_.end(); p++)
	{
		if (!IsLate(data, *p))
		{
			p--;
			std::cout << data.year << "-";
			if (data.month < 10)
				std::cout << "0" << data.month << "-";
			else
				std::cout << data.month << "-";
			if (data.date < 10)
				std::cout << "0" << data.date << " => ";
			else
				std::cout << data.date << " => ";
			std::cout << data.rate << " = " << data.rate * (*p).rate << std::endl;
			return (0);
		}
	}
	p--;
	std::cout << data.year << "-";
	if (data.month < 10)
		std::cout << "0" << data.month << "-";
	else
		std::cout << data.month << "-";
	if (data.date < 10)
		std::cout << "0" << data.date << " => ";
	else
		std::cout << data.date << " => ";
	std::cout << data.rate << " = " << data.rate * (*p).rate << std::endl;
	return (0);
}

void	BitcoinExchange::Debug()
{
	for (std::vector<t_data>::iterator i = rate_data_.begin(); i < rate_data_.end(); i++)
	{
		std::cout << (*i).year << ", " << (*i).month << ", " << (*i).date << ", " << (*i).rate << std::endl;
	}
}

int	BitcoinExchange::CreateRateList(const char *file_path)
{
	std::ifstream file(file_path);
	std::string data;

	if (!file)
	{
		std::cerr << "Error: Can't open .csv file" << std::endl;
		return (1);
	}
	if (std::getline(file, data) && data != "date,exchange_rate")
	{
		std::cerr << "Error: .csv unknown first line format" << std::endl;
		return (1);
	}
	while (std::getline(file, data))
	{
		if (CreateRate(data))
			return (1);
	}
	if (!file.eof())
		std::cerr << "Fatal Error: Can't read all of file(unreachable)" << std::endl;
	file.close();
	return (0);
}

void	BitcoinExchange::OutputExchangeResult(const char *file_path)
{
	std::fstream file(file_path);
	std::string data;

	if (!file)
	{
		std::cerr << "Error: Can't open .txt file" << std::endl;
		return ;
	}
	if (std::getline(file, data) && data != "date | value")
	{
		std::cerr << "Error: inputfile unknown first line format" << std::endl;
		return ;
	}
	while (std::getline(file, data))
		SearchRate(data);
	if (!file.eof())
		std::cerr << "Fatal Error: Can't read all of file(unreachable)" << std::endl;
	file.close();
}
