#include "Cell.h"

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

void Cell::setValue(std::stringstream& ss)
{
	char buffer[BUFFER_LEN] = { 0 };
	ss.getline(buffer, BUFFER_LEN, SEPARATOR);

	if (emptyString(buffer))
	{
		_type = CellType::empty;
		return;
	}

}
