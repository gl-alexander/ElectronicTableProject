#pragma once
#include <iostream>
#include "Cell.h"

class CellEmpty : public Cell
{
public:
	CellEmpty();

	void printCell(size_t len, std::ostream& os) const override;
	void saveToFile(std::ofstream& ofs) const override;

	Cell* clone() const override;

	double evaluate() const override;

	size_t getLenght() const;
};