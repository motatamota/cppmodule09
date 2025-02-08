#pragma once
# include <vector>
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
	typedef struct s_date
	{
		int		year;
		int		month;
		int		date;
		double	rate;
	}	t_data;

	std::vector<t_data> rate_data_;
	int	CreateRate(const std::string &day);
	int	SearchRate(const std::string &day);
	int IsThisDay(const t_data &data);
	int	IsLate(const t_data &src, const t_data &list);
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &other);
	BitcoinExchange &operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	// create rate list from filepath
	int	CreateRateList(const char *file_path);
	// output exchange result from filepath
	void	OutputExchangeResult(const char *file_path);
	void	Debug();
};
