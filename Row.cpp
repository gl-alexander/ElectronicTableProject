#include "Row.h"
#define MAX(a, b) ((a) > (b) ? (a) : (b))


Row::Row(std::ifstream& ifs)
{
	readRowFromFile(ifs);
}

Cell*& Row::operator[](int ind)
{
	if (ind >= _cells.size()) throw std::out_of_range("Index was out of range");
	return _cells[ind];
}

const Cell* Row::operator[](int ind) const
{
	if (ind >= _cells.size()) throw std::out_of_range("Index was out of range");
	return _cells[ind];
}

void Row::add(Cell* cell) // adds a cell to the end of the row
{
	_cells.add(cell);
}

void Row::readRowFromFile(std::ifstream& ifs)
{
	char buffer[BUFFER_LEN];
	ifs.getline(buffer, BUFFER_LEN);

	size_t inputLenght = strlen(buffer);
	size_t separatorsCount = countCharOccurances(buffer, SEPARATOR);

	if (inputLenght == 0)
	{
		return; // empty row
	}
	
	_cells = MyCollection<Cell>(separatorsCount + 1); // if there are n separators, we have n + 1 cells
	
	std::stringstream ss(buffer);

	for (int i = 0; i <= separatorsCount; i++)
	{
		try
		{
			_cells.add(CellFactory::createCell(ss));

		}
		catch (std::invalid_argument& ex)
		{
			const char* columnIndStr = intToString(i);

			MyString errorMessage = "col: " + MyString(columnIndStr) + " " + MyString(ex.what());
			delete[] columnIndStr;

			throw std::invalid_argument(errorMessage.c_str());
		}
		//possibly add logic_error catch for too many arguments
	}
}




unsigned Row::lenght() const
{
	return _cells.size();
}

unsigned Row::getLongestCell() const
{
	size_t cellsCount = _cells.size();
	unsigned longestCell = 0;
	for (int i = 0; i < cellsCount; i++)
	{
		longestCell = MAX(longestCell, _cells[i]->getLenght());
	}
	return longestCell;
}

void Row::printRow(size_t rowLen, const MyVector<int>& printWidths, std::ostream& os) const
{
	size_t cellsCount = _cells.size();
	os << PRINT_SEPARATOR;
	for (int i = 0; i < rowLen; i++)
	{
		if (i < cellsCount)
		{
			_cells[i]->printCell(printWidths[i], os);
		}
		else
		{
			PrintHelper::printWhitespaces(printWidths[i], os);
		}
		os << PRINT_SEPARATOR;
	}
}

void Row::saveToFile(std::ofstream& ofs) const
{
	size_t cellsCount = _cells.size();
	for (int i = 0; i < cellsCount; i++)
	{
		_cells[i]->saveToFile(ofs);
		if (i < cellsCount - 1)
			ofs << SEPARATOR;
	}
}
