#include "Validation.h"

const char DECIMAL_SYMBOL = '.';

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

int Validation::countEndSymbols(const char* str, int len, char sym)
{
	int count = 0;
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
	int endingWhitSpaces = countEndSymbols(str, len, ' ');

	if (leadingWhiteSpaces + endingWhitSpaces == len) return true;

	return false;
}


//Type Verification:
bool Validation::isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
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

bool Validation::validOperator(const char* str)
{
	return *str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '^';
}

bool Validation::validExpression(const char* str)
{
	return false;
}

bool Validation::validFormula(const char* str)
{
	return true;
	// = ({CELL/VALUE} {OPERATOR} {CELL/VALUE})
	if (*str != '=') return false;
	str += 2; //we skip the '= '

	std::stringstream ss(str);
	char buffer[BUFFER_LEN];

	ss.getline(buffer, BUFFER_LEN, ' '); // first value / cell
	if (!validCellLocation(buffer) && !validInteger(buffer)) return false;

	ss.getline(buffer, BUFFER_LEN, ' '); // operator
	if (!validOperator(buffer)) return false;

	ss.getline(buffer, BUFFER_LEN, ' '); // second value / cell
	if (!validCellLocation(buffer) && !validInteger(buffer)) return false;

	//if (!ss.eof()) return false; // if the string hasn't ended it's not a valid formula
	return true;
}

bool Validation::validString(const char* str)
{
	if (*str != '"') return false;
	if (*(str + strlen(str) - 1) != '"') return false; //strings start and end with "
	return true;
}