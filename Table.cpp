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

void Table::readFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::in);

	if (!ifs.is_open())
		throw std::invalid_argument("File not found!");

	size_t linesCount = countCharacterOccurances(ifs, '\n');
	_rowsCount = linesCount;
	_rows = new Row[linesCount];

	for (int i = 0; i < linesCount; i++)
	{
		_rows[i].readRowFromFile(ifs);
	}
}
