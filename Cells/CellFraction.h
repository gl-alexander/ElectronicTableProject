#pragma once
#include <iostream>
#include "Cell.h"



class CellFraction : public Cell
{
	double _value  = 0;
public:
	CellFraction();

	CellFraction(double value);

	void printCell(size_t len, std::ostream& os) const override;
	void saveToFile(std::ofstream& ofs) const override;

	Cell* clone() const override;

	size_t getLenght() const;

	void setValue(double value);

	double getValue() const;

	double evaluate() const override;

	
};

