#pragma once
#include <iostream>
#include "../Utilities/MyString.h"
#include <sstream>
#include <fstream>
#include "../Utilities/PrintHelper/PrintHelper.h" // for printing



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
	CellType _type;

public:
	Cell() = default;
	Cell(const CellType& type);

	const CellType& getType() const;

	virtual void printCell(size_t len, std::ostream& os) const = 0;

	virtual void saveToFile(std::ofstream& ofs) const = 0;

	virtual Cell* clone() const = 0;

	virtual ~Cell() = default;

	virtual double evaluate() const = 0;

	virtual size_t getLenght() const = 0;
};

