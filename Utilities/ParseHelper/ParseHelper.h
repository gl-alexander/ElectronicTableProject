#pragma once
#include <iostream>
#include <sstream>
#include "../Validation/Validation.h"


const char DECIMAL_SYMBOL = '.';

static StringView extractExpression(const MyString& string)
{
	StringView sv(string);
	size_t charsToSkip = 0; 
	while (sv[charsToSkip] != '(')
	{
		charsToSkip++;
	}

	return sv.substr(charsToSkip, sv.length() - charsToSkip);
}

static void skipWhiteSpeces(std::istream& is)
{
	while (is.peek() == ' ')
		is.ignore();
}

static size_t toDigit(char ch)
{
	if (ch < '0' || ch > '9') return 0;
	return ch - '0';
}

static size_t intLen(int n)
{
	int len = 0;
	if (n == 0) return 1;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	return len;
}

static int toInt(const char* str)
{
	int res = 0;
	bool negative = false;
	if (*str == '-')
	{
		negative = true;
		str++;
	}
	while (*str)
	{
		if (!Validation::isDigit(*str)) break;
		res *= 10;
		res += toDigit(*(str++));
	}
	if (negative) res *= -1;
	return res;
}

static double toDouble(const char* str)
{
	int integerPart = 0;
	bool negative = false;
	if (*str == '-')
	{
		negative = true;
		str++;
	}
	while (*str)
	{
		if (*str == DECIMAL_SYMBOL) break;
		integerPart *= 10;
		integerPart += toDigit(*(str++));
	}
	str++; // skips the decimal
	int decimalPart = toInt(str);
	double decimalRes = decimalPart / pow(10, intLen(decimalPart));
	decimalRes += integerPart;
	return decimalRes;
}

static int toInt(const StringView& str)
{
	int res = 0;
	bool negative = false;
	size_t i = 0;
	if (str[0] == '-')
	{
		negative = true;
		i++;
	}
	size_t size = str.length();
	for (; i < size; i++)
	{
		if (!Validation::isDigit(str[i])) break;
		res *= 10;
		res += toDigit(str[i]);
	}
	if (negative) res *= -1;
	return res;
}

static double toDouble(const StringView& str)
{
	int integerPart = 0;
	bool negative = false;
	size_t i = 0;
	if (str[0] == '-')
	{
		negative = true;
		i++;
	}
	size_t size = str.length();
	for (; i < size; i++)
	{
		if (str[i] == DECIMAL_SYMBOL) break;
		integerPart *= 10;
		integerPart += toDigit(str[i]);
	}
	
	i++; // skips the decimal
	int decimalPart = toInt(str.substr(i, size - i));
	double decimalRes = decimalPart / pow(10, intLen(decimalPart));
	decimalRes += integerPart;
	return decimalRes;
}




static void getRowAndColumn(const char* str, size_t& row, size_t& column)
{
	row = column = 0;
	str++; // skips the 'R'
	row = toInt(str);
	str += intLen(row); // skips the digits we've already read
	str++; // skips the 'C'
	column = toInt(str);
}
static void getRowAndColumn(const StringView& str, size_t& row, size_t& column)
{
	row = column = 0;
	row = toInt(str.substr(1, str.length() - 1)); // this get the StringView, skippinig the first char 'R'
	size_t startingInd = intLen(row) + 2; // we need to skip the characters representing the int row as well as the 'R' and 'C'
	size_t howMany = str.length() - startingInd;
	column = toInt(str.substr(startingInd, howMany));
}
