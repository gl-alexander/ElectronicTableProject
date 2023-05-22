#include "Table.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))


static int countCharacterOccurances(std::ifstream& ifs, char ch)
{
	unsigned counter = 0;
	int originalPosition = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	while (!ifs.eof())
	{
		if (ifs.get() == ch) counter++;
	}
	ifs.clear();
	ifs.seekg(originalPosition);
	return counter;
}

void Table::readFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("File not found!");

	size_t linesCount = countCharacterOccurances(ifs, '\n');

	_rows = MyVector<Row>(linesCount + 1);

	for (int i = 0; i <= linesCount; i++)
	{
		try
		{
			_rows.push_back(Row(ifs));
		}
		catch (std::invalid_argument& ex)
		{
			std::cout << "Error: row " << i << ", " << ex.what() << " is unknown data type\n";
		}
	}
}

Table::Table(const char* fileName)
{
	readFromFile(fileName);
}

void Table::printTypes() const
{
	size_t rowsCount = _rows.size();
	for (int i = 0; i < rowsCount; i++)
	{
		_rows[i].printValueTypes();
	}
}

unsigned Table::getLongestRowLenght() const
{
	unsigned max = 0;
	size_t rowsCount = _rows.size();
	for (int i = 0; i < rowsCount; i++)
	{
		max = MAX(max, _rows[i].lenght());
	}
	return max;
}

void Table::print() const
{
	unsigned longestRowLen = getLongestRowLenght();
	size_t rowsCount = _rows.size();
	for (int i = 0; i < rowsCount; i++)
	{
		_rows[i].printRow(longestRowLen);
		std::cout << std::endl;
	}
}
