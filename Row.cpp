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
		_cells[i].setValue(ss);
	}
}
