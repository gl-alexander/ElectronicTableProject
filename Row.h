#pragma once
#include "Cells/IncludeCells.h"
#include "Factory/CellFactory.h"
#include "Utilities/MyCollection.hpp"
#include "Utilities/MyVector.hpp"
#include "Utilities/ParseHelper/ParseHelper.h"
#include <fstream>

const char SEPARATOR = ',';
const char PRINT_SEPARATOR = '|';

class Row
{
	MyCollection<Cell> _cells;

	void readRowFromFile(std::ifstream& ifs);
public:
	Row() = default;
	Row(std::ifstream& ifs);
	

	Cell*& operator[](int ind);
	const Cell* operator[](int ind) const;
	void add(Cell* cell);

	unsigned lenght() const;
	unsigned getLongestCell() const;

	void printRow(size_t rowLen, const MyVector<int>& printWidths, std::ostream& os) const;

	void saveToFile(std::ofstream& ofs) const;
};

