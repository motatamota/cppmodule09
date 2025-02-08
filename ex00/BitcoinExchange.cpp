#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	rate_data_.clear();
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
	std::string str;

	str = day.substr(0, 10);
	if (str[4] != '-' || str[7] != '-')
	{
		std::cerr << "Error: " << day << ": unknown format" << std::endl;
		return (1);
	}
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
	rate_data_[str] = data;
	return (0);
}

int BitcoinExchange::SearchRate(const std::string &day)
{
	std::string::const_iterator i;
	std::istringstream oss(day);
	std::istringstream oss1(day);
	std::string str;
	t_data	data;
	char	c;

	oss1 >> str;
	if (str[4] != '-' || str[7] != '-')
	{
		std::cerr << "Error: " << day << ": unknown format" << std::endl;
		return (1);
	}
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
	std::map<std::string, t_data>::iterator tmp = rate_data_.lower_bound(str);
	if (tmp == rate_data_.end()) {
		if (!rate_data_.empty()) {
			--tmp;
		} else {
			std::cerr << "Error: No exchange rate data available." << std::endl;
			return (1);
		}
	}
	else if (tmp->first != str) {
		if (tmp == rate_data_.begin()) {
			std::cerr << "Error: No earlier date found for " << str << std::endl;
			return (1);
		}
		--tmp;
	}

	std::cout << str << " => " << data.rate << " = " << data.rate * tmp->second.rate << std::endl;
	return (0);
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
