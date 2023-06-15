#pragma once
#include <iostream>
#include "Cell.h"

class CellInteger : public Cell
{
	int _value = 0;
public:
	CellInteger();

	CellInteger(int value);

	void printCell(size_t len, std::ostream& os) const override;
	void saveToFile(std::ofstream& ofs) const override;

	Cell* clone() const override;

	size_t getLenght() const;

	void setValue(int value);

	int getValue() const;

	double evaluate() const override;
};