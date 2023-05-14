#include "Row.h"

static int countCharOccurances(const char* buffer, char ch)
{
	unsigned count = 0;
	while (*buffer)
	{
		if (*(buffer++) == ch) count++;
	}
	return count;
}

static char convertToChar(int n)
{
	return '0' + n;
}

static unsigned countDigits(int num)
{
	if (num == 0) return 1;
	int count = 0;
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return count;
}

static const char* converToString(int num)
{
	unsigned len = countDigits(num);
	char* str = new char[len + 1];
	for (int i = len - 1; i >= 0; i--)
	{
		str[i] = convertToChar(num % 10);
		num /= 10;
	}
	str[len] = '\0';
	return str;
}


void Row::copyFrom(const Row& other)
{
	_cellCount = other._cellCount;
	_cells = new Cell[other._cellCount];
	for (int i = 0; i < other._cellCount; i++)
	{
		_cells[i] = other._cells[i];
	}
}

void Row::free()
{
	delete[] _cells;
	_cells = nullptr;
	_cellCount = 0;
}

void Row::moveFrom(Row&& other)
{
	_cells = other._cells;
	_cellCount = other._cellCount;
	delete[] other._cells;
}

Row::Row(const Row& other)
{
	copyFrom(other);
}
Row& Row::operator=(const Row& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Row::~Row()
{
	free();
}

void Row::readRowFromFile(std::ifstream& ifs)
{
	char buffer[BUFFER_LEN] = { 0 };
	ifs.getline(buffer, BUFFER_LEN);
	size_t inputLenght = strlen(buffer);
	size_t separatorsCount = countCharOccurances(buffer, SEPARATOR);

	if (inputLenght == 0)
	{
		_cells = nullptr;
		_cellCount = 0;
		return;
	}
	
	_cellCount = separatorsCount + 1;
	_cells = new Cell[separatorsCount + 1]; // if there are n separators, we have n + 1 cells
	
	std::stringstream ss(buffer);

	for (int i = 0; i <= separatorsCount; i++)
	{
		try
		{
			_cells[i].setValue(ss);
		}
		catch (std::invalid_argument& ex)
		{
			const char* columnIndStr = converToString(i);
			MyString errorMessage = "col ";
			errorMessage += columnIndStr;
			errorMessage += " ";
			errorMessage += ex.what();
			delete[] columnIndStr;
			throw std::invalid_argument(errorMessage.c_str());
		}
	}
}
