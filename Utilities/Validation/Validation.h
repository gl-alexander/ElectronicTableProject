#pragma once
#include <iostream>
#include <sstream>

const size_t BUFFER_LEN = 1024;

struct Validation
{
	static int countLeadingSymbols(const char* str, char sym);

	static int countEndSymbols(const char* str, int len, char sym);

	static bool emptyString(const char* str);


	static bool isDigit(char ch);

	static bool validInteger(const char* str);

	static bool validDouble(const char* str);

	static bool validCellLocation(const char* str);

	static bool validOperator(const char* str);

	static bool validFormula(const char* str);

	static bool validString(const char* str);
};

