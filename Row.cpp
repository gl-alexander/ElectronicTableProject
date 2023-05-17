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


void Row::readRowFromFile(std::ifstream& ifs)
{
	char buffer[BUFFER_LEN];
	ifs.getline(buffer, BUFFER_LEN);

	size_t inputLenght = strlen(buffer);
	size_t separatorsCount = countCharOccurances(buffer, SEPARATOR);

	if (inputLenght == 0)
	{
		_cells.clear();
		_cellCount = 0;
		return;
	}
	
	_cellCount = separatorsCount + 1; // if there are n separators, we have n + 1 cells

	_cells = MyVector<Cell>(_cellCount);
	
	std::stringstream ss(buffer);

	for (int i = 0; i < _cellCount; i++)
	{
		try
		{
			_cells[i].setValue(ss);
		}
		catch (std::invalid_argument& ex)
		{
			const char* columnIndStr = converToString(i);

			MyString errorMessage = "col " + MyString(columnIndStr) + " " + MyString(ex.what());
			delete[] columnIndStr;

			throw std::invalid_argument(errorMessage.c_str());
		}
	}
}


void Row::printValueTypes() const
{
	for (int i = 0; i < _cellCount; i++)
	{
		switch (_cells[i].getType())
		{
		case CellType::empty:
			std::cout << "empty ";
			break;
		case CellType::integer:
			std::cout << "integer ";
			break;
		case CellType::string:
			std::cout << "string ";
			break;
		case CellType::fraction:
			std::cout << "fraction ";
			break;
		case CellType::formula:
			std::cout << "formula ";
			break;
		default:
			std::cout << "Unknown ";
		}
	}
	std::cout << std::endl;
}
