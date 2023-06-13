#pragma once
#include <iostream>
#include <fstream>
#include "../Cells/IncludeCells.h"
#include "../Utilities/Validation/Validation.h"

const char COMMA_SYMBOL = '.';

class CellFactory
{
	static const CellType& getType(const char* str);

	static Cell* createIntegerCell(const char* str);
	static Cell* createStringCell(const char* str);
	static Cell* createFractionCell(const char* str);
	static Cell* createFormulaCell(const char* str);

public:
	static Cell* createCell(std::stringstream& ss);
};