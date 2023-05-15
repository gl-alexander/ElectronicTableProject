#include "Cell.h"

const char COMMA_SYMBOL = '.';

static int countLeadingSymbols(const char* str, char sym)
{
	int count = 0;
	while (*str)
	{
		if (*(str++) != sym) break;
		count++;
	}
	return count;
}

static int countEndSymbols(const char* str, int len, char sym)
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
static bool emptyString(const char* str)
{
	size_t len = strlen(str);
	if (len == 0) return true;

	int leadingWhiteSpaces = countLeadingSymbols(str, ' ');
	int endingWhitSpaces = countEndSymbols(str, len, ' ');

	if (leadingWhiteSpaces + endingWhitSpaces == len) return true;

	return false;
}

static bool isDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

static bool validInteger(const char* str)
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

static bool validDouble(const char* str)
{
	unsigned countCommas = 0;
	if (str[0] == '-' || str[0] == '+') // we can skip the first symbol if it's either a + or -
		str++; 
	while (*str)
	{
		if (!isDigit(*str))
		{
			if (*str == COMMA_SYMBOL)
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

static bool validCellLocation(const char* str)
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

static bool validOperator(const char* str)
{
	return *str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '^';
}

static bool validFormula(const char* str)
{
	//= {CELL/VALUE} {OPERATOR} {CELL/VALUE}
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

	if (!ss.eof()) return false; // if the string hasn't ended it's not a valid formula
	return true;
}

static bool validString(const char* str)
{
	if (*str != '"') return false;
	if (*(str + strlen(str) - 1) != '"') return false; //strings start and end with "
	return true;
}

void Cell::setCellType(const char* str)
{
	if (validInteger(str)) _type = CellType::integer;
	else if (validDouble(str)) _type = CellType::fraction;
	else if (validFormula(str)) _type = CellType::formula;
	else if(validString(str)) _type = CellType::string;
	else
	{
		throw std::invalid_argument(str);
	}
}
		

void Cell::setValue(std::stringstream& ss)
{
	char buffer[BUFFER_LEN] = { 0 };
	ss.getline(buffer, BUFFER_LEN, SEPARATOR);

	if (emptyString(buffer))
	{
		_type = CellType::empty;
		return;
	}

	// if we've reached this part, the buffer is a non-empty string

	size_t len = strlen(buffer);
	int leadingWhiteSpaces = countLeadingSymbols(buffer, ' ');
	int endingWhiteSpaces = countEndSymbols(buffer, len, ' ');

	buffer[len - endingWhiteSpaces - 1] = '\0'; // this 'cuts' the buffer at the last non-whitespace symbol

	_value = buffer + leadingWhiteSpaces;// we shift the buffer with the number of leading white spaces,
	try
	{
		setCellType(buffer + leadingWhiteSpaces); // so we only pass the actual text
	}
	catch (std::invalid_argument& ex)
	{
		throw;
	}
}


const CellType& Cell::getType() const
{
	return _type;
}
const MyString& Cell::getValue() const
{
	return _value;
}
