#pragma once
# include <map>
# include <string>
# include <sstream>
# include <fstream>
# include <iostream>
# include <limits>
# include <cmath>
# include <iomanip>


class BitcoinExchange
{
private:
	typedef struct s_data
	{
		int		year;
		int		month;
		int		date;
		double	rate;
	}	t_data;

	std::map<std::string, t_data> rate_data_;

	int	CreateRate(const std::string &day);
	int	SearchRate(const std::string &day);
	int IsThisDay(const t_data &data);
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	// create rate list from filepath
	int	CreateRateList(const char *file_path);
	// output exchange result from filepath
	void	OutputExchangeResult(const char *file_path);
};
