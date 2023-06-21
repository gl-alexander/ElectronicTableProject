#include "PrintHelper.h"

const double EPSILON = 0.00001;

void PrintHelper::printTitle()
{
	std::cout << ">Table Parser Project" << std::endl;
	std::cout << "by: Alexander Glushkov" << std::endl;
	std::cout << "_______________________" << std::endl;
}

void PrintHelper::printHelp()
{
	std::cout << "Supported commands:" << std::endl;
	std::cout << "\topen <filename>" << std::endl;
	std::cout << "\tprint" << std::endl;
	std::cout << "\tsave" << std::endl;
	std::cout << "\tsaveas <filename>" << std::endl;
	std::cout << "\tedit <R#C#> <new value>" << std::endl;
	std::cout << "\tclose" << std::endl;
	std::cout << "\texit" << std::endl;
}

size_t PrintHelper::intLen(int n)
{
	if (n == 0) return 1;
	size_t len = 0;
	if (n < 0) len++; // if n is negative, then we need to print the minus sign
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return len;
}

static size_t decimalPlaces(double d)
{
	size_t len = 0;
	d -= int(d);
	while (d >= EPSILON)
	{
		d *= 10;
		d -= int(d);
		len++;
		
	}
	return len;
}

size_t PrintHelper::doubleLen(double num)
{
	int converted = (int)num;
	if (abs(num - converted) < EPSILON) return intLen(converted); // the double is the same as the its int representation
	size_t len = 0;
	if (num < 0) len++; // if it's negative we account for the minus;
	num = abs(num); // we then work with the positive value

	len += intLen(num);

	double difference = num - int(num);
	
	size_t places = decimalPlaces(abs(difference));
	
	return len + places + 1; // +1, counting the Decimal point
}

void PrintHelper::printCharNTimes(char ch, int count, std::ostream& os)
{
	if (count <= 0) return;
	for (int i = 0; i < count; i++)
	{
		os << ch;
	}
}
void PrintHelper::printWhitespaces(int count, std::ostream& os)
{
	printCharNTimes(' ', count, os);
}
