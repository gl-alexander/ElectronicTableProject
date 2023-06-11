#include <iostream>
#include <fstream>
#include <sstream>

struct PrintHelper
{
	static const unsigned DECIMAL_PLACES_TO_PRINT = 3;
	static size_t intLen(int n);
	static size_t doubleLen(double d, size_t decimalPlaces = DECIMAL_PLACES_TO_PRINT);

	static void printCharNTimes(char ch, int count, std::ostream& os);
	static void printWhitespaces(int count, std::ostream& os);

};
