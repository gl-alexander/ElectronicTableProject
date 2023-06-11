#pragma once
#include <iostream>
#include "../Utilities/MyString.h"
#include <sstream>
#include <fstream>
#include "../Utilities/PrintHelper/PrintHelper.h" // for printing

const size_t BUFFER_LEN = 1024;
const char SEPARATOR = ',';
const char PRINT_SEPARATOR = '|';

enum class CellType
{
	empty,
	integer,
	fraction,
	string,
	formula
};

class Cell
{
//	MyString _value;
	CellType _type;

public:
	Cell() = default;
	Cell(const CellType& type);

	const CellType& getType() const;

	virtual void printCell(size_t len, std::ostream& os) const = 0;

	virtual Cell* clone() const = 0;

	virtual ~Cell() = default;
};

