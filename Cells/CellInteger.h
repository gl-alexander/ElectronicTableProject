#pragma once
#include <iostream>
#include "Cell.h"

class CellInteger : public Cell
{
	int _value = 0;
public:
	CellInteger();

	void printCell(size_t len) const override;

	Cell* clone() const override;

	void setValue(int value);

	int getValue() const;
};