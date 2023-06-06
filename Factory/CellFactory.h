#pragma once
#include <iostream>
#include <fstream>
#include "../Cells/IncludeCells.h"

const char COMMA_SYMBOL = '.';

class CellFactory
{
	static const CellType& getType(const char* str);

	static Cell* createIntegerCell(std::stringstream& ss);
	static Cell* createStringCell(std::stringstream& ss);
	static Cell* createFractionCell(std::stringstream& ss);
	static Cell* createFormulaCell(std::stringstream& ss);

public:
	static Cell* createCell(std::stringstream& ss);
};
