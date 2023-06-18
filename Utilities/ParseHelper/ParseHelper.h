#pragma once
#include <iostream>
#include <sstream>
#include "../Validation/Validation.h"
#pragma warning (disable : 4996)


const char DECIMAL_SYMBOL = '.';
const size_t MAX_INT_LEN = 50;

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

static char digitToChar(size_t digit)
{
	return digit + '0';
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

static int countCharOccurances(const char* buffer, char ch)
{
	unsigned count = 0;
	while (*buffer)
	{
		if (*(buffer++) == ch) count++;
	}
	return count;
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


static const char* intToString(int n)
{
	char buffer[MAX_INT_LEN];
	if (n == 0) buffer[0] = '0';
	size_t numLen = intLen(n);
	size_t strEnd = numLen;
	if (n < 0)
	{
		buffer[0] = '-';
		strEnd++;
	}
	
	while (numLen > 0)
	{
		buffer[numLen - 1] = digitToChar(n % 10);
		numLen--;
		n /= 10;
	}
	buffer[strEnd] = '\0';
	return buffer;
}

static MyString parseString(const char* str)
{
	char buffer[BUFFER_LEN];
	size_t current = 0;
	
	size_t size = strlen(str);
	for (int i = 1; i < size - 1; i++)
	{
		if (str[i] == '\\' && str[i+1] == '"')
		{
			i++;
		}
		buffer[current++] = str[i];
	}
	buffer[current] = '\0'; // this cuts the string before the last "

	return MyString(buffer);
}

static void substr(const char* str, size_t beg, size_t len, char* dest)
{
	char temp[BUFFER_LEN];
	for (int i = 0; i < len; i++)
	{
		temp[i] = str[beg + i];
	}
	temp[len] = 0;
	strcpy(dest, temp);
}