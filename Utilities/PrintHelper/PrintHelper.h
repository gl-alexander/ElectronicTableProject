#include <iostream>
#include <fstream>
#include <sstream>



struct PrintHelper
{
	static void printTitle();
	static void printHelp();

	static size_t intLen(int n);
	static size_t doubleLen(double d);

	static void printCharNTimes(char ch, int count, std::ostream& os);
	static void printWhitespaces(int count, std::ostream& os);

};