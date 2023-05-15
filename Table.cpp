#include "Table.h"

static int countCharacterOccurances(std::ifstream& ifs, char ch)
{
	unsigned counter = 0;
	int originalPosition = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	while (!ifs.eof())
	{
		if (ifs.get() == ch) counter++;
	}

	ifs.seekg(originalPosition);
	return counter;
}

void Table::copyFrom(const Table& other)
{
	_rowsCount = other._rowsCount;
	_rows = new Row[other._rowsCount];
	for (int i = 0; i < other._rowsCount; i++)
	{
		_rows[i] = other._rows[i];
	}
}
void Table::free()
{
	delete[] _rows;
	_rows = nullptr;
	_rowsCount = 0;
}
void Table::moveFrom(Table&& other)
{
	_rows = other._rows;
	_rowsCount = other._rowsCount;
	delete[] other._rows;
}


Table::Table(const Table& other)
{
	copyFrom(other);
}
Table& Table::operator=(const Table& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
Table::~Table() noexcept
{
	free();
}

Table::Table(Table&& other) noexcept
{
	moveFrom(std::move(other));
}
Table& Table::operator=(Table&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void Table::readFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("File not found!");

	size_t linesCount = countCharacterOccurances(ifs, '\n');
	_rowsCount = linesCount;
	_rows = new Row[linesCount];

	for (int i = 0; i < linesCount; i++)
	{
		try
		{
			_rows[i].readRowFromFile(ifs);
		}
		catch (std::invalid_argument& ex)
		{
			std::cout << "Error: row " << i << ", " << ex.what() << " Unknown data type";
		}
	}
}

Table::Table(const char* fileName)
{
	readFromFile(fileName);
}

