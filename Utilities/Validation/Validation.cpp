#include "Validation.h"
#pragma warning(disable : 4996)

const char DECIMAL_SYMBOL = '.';

static void formatData(const char* str, char* dest)
{
	char buffer[BUFFER_LEN];
	strcpy(buffer, str); // this is what moves the get pointer to the next cell

	size_t len = strlen(buffer);
	int leadingWhiteSpaces = Validation::countLeadingSymbols(buffer, ' ');
	int endingWhiteSpaces = Validation::countEndSymbols(buffer, ' ');

	buffer[len - endingWhiteSpaces] = '\0'; // this 'cuts' the buffer at the last non-whitespace symbol
	strcpy(dest, buffer + leadingWhiteSpaces);
}

int Validation::countLeadingSymbols(const char* str, char sym)
{
	int count = 0;
	while (*str)
	{
		if (*(str++) != sym) break;
		count++;
	}
	return count;
}

int Validation::countEndSymbols(const char* str, char sym)
{
	int count = 0;
	size_t len = strlen(str);
	for (int i = len - 1; i >= 0; i--)
	{
		if (str[i] != sym) break;
		count++;
	}
	return count;

}

//checks if the string is empty or consists only of white spaces
bool Validation::emptyString(const char* str)
{
	size_t len = strlen(str);
	if (len == 0) return true;

	int leadingWhiteSpaces = countLeadingSymbols(str, ' ');
	int endingWhitSpaces = countEndSymbols(str, ' ');

	if (leadingWhiteSpaces + endingWhitSpaces == len) return true;

	return false;
}


//Type Verification:
bool Validation::isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool Validation::isOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}


bool Validation::validInteger(const char* str)
{
	if (str[0] == '-' || str[0] == '+') // we can skip the first symbol if it's either a + or -
		str++;
	while (*str)
	{
		if (!isDigit(*str)) return false;
		str++;
	}
	return true;
}

bool Validation::validInteger(const StringView& str)
{
	size_t i = 0;
	if (str[0] == '-' || str[0] == '+') // we can skip the first symbol if it's either a + or -
		i++;

	size_t size = str.length();
	for (; i < size; i++)
	{
		if (!isDigit(str[i])) return false;
	}
	return true;
}

bool Validation::validDouble(const char* str)
{
	unsigned countCommas = 0;
	if (str[0] == '-' || str[0] == '+') // we can skip the first symbol if it's either a + or -
		str++;
	while (*str)
	{
		if (!isDigit(*str))
		{
			if (*str == DECIMAL_SYMBOL)
			{
				countCommas++;
				if (countCommas > 1) return false;
			}
			else
			{
				return false;
			}

		}

		str++;
	}
	return true;
}

bool Validation::validDouble(const StringView& str)
{
	unsigned countCommas = 0;
	size_t i = 0;
	if (str[0] == '-' || str[0] == '+') // we can skip the first symbol if it's either a + or -
		i++;
	size_t size = str.length();
	for (; i < size; i++)
	{
		if (!isDigit(str[i]))
		{
			if (str[i] == DECIMAL_SYMBOL)
			{
				countCommas++;
				if (countCommas > 1) return false;
			}
			else
				return false;

		}
	}
	return true;
}

bool Validation::validCellLocation(const char* str)
{
	if (*str != 'R') return false;
	str++; // we skip the 'R'
	while (isDigit(*str))
	{
		str++; // we skip the digits
	}
	if (*str != 'C') return false;
	str++; // we skip the 'C'
	while (*str)
	{
		if (!isDigit(*str)) return false;
		str++;
	}
	return true;
}
bool Validation::validCellLocation(const StringView& str)
{
	if (str[0] != 'R') return false;
	size_t i = 1; // we start from the 2nd character, skipping the R
	if (!isDigit(str[i])) return false; // if the 2nd character isn't a number then it's an invalid cell location
	while (isDigit(str[i]))
	{
		i++; // we skip the digits
	}
	if (str[i] != 'C') return false;
	i++; // we skip the 'C'
	size_t size = str.length();
	for (; i < size; i++)
	{
		if (!isDigit(str[i])) return false;
	}
	return true;
}

bool Validation::validOperator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

bool Validation::validExpression(const char* str)
{
	return false;
}

bool Validation::validFormula(const char* str)
{
	return (*str == '=');
	// = ({CELL/VALUE} {OPERATOR} {CELL/VALUE})
	if (*str != '=') return false;
	str += 2; //we skip the '= '

	std::stringstream ss(str);
	char buffer[BUFFER_LEN];

	ss.getline(buffer, BUFFER_LEN, ' '); // first value / cell
	if (!validCellLocation(buffer) && !validInteger(buffer)) return false;

	ss.getline(buffer, BUFFER_LEN, ' '); // operator
	//if (!validOperator(buffer)) return false;

	ss.getline(buffer, BUFFER_LEN, ' '); // second value / cell
	if (!validCellLocation(buffer) && !validInteger(buffer)) return false;

	//if (!ss.eof()) return false; // if the string hasn't ended it's not a valid formula
	return true;
}

bool Validation::validString(const char* str)
{
	if (*str != '"' || *(str + strlen(str) - 1) != '"') return false;
	size_t len = strlen(str);
	for (int i = 1; i < len - 1; i++)
	{
		if (str[i] == '"' && str[i - 1] != '\\') return false; // checks for escapes
	}
	return true;
}

bool Validation::validValue(const char* str)
{
	char formatted[BUFFER_LEN];
	formatData(str, formatted);
	return validDouble(formatted) || validInteger(formatted) || validString(formatted) || validFormula(formatted) || emptyString(formatted);
}
