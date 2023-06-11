#include "PrintHelper.h"

size_t PrintHelper::intLen(int n)
{
	if (n == 0) return 1;
	size_t len = 0;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	if (n < 0) len++; // if n is negative, then we need to print the minus sign
	return len;
}

size_t PrintHelper::doubleLen(double d, size_t decimalPlaces = DECIMAL_PLACES_TO_PRINT)
{
	int converted = (int)d;

	size_t len = intLen(converted);
	
	len += decimalPlaces + 1; // +1 because we need to print the decimal point .

	return len
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
