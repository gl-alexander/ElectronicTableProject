#pragma once
#include "../StringView.h"
#include <iostream>
#include <sstream>

const size_t BUFFER_LEN = 1024;

struct Validation
{
	static int countLeadingSymbols(const char* str, char sym);

	static int countEndSymbols(const char* str, char sym);

	static bool emptyString(const char* str);


	static bool isDigit(char ch);

	static bool isOperator(char ch);

	static bool validInteger(const char* str);
	static bool validInteger(const StringView& str);

	static bool validDouble(const char* str);
	static bool validDouble(const StringView& str);

	static bool validCellLocation(const char* str);
	static bool validCellLocation(const StringView& str);

	static bool validOperator(char ch);

	static bool validExpression(const char* str);

	static bool validFormula(const char* str);

	static bool validString(const char* str);

	static bool validValue(const char* str);
};

