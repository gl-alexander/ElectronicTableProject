#pragma once
#include <iostream>
#include "Cell.h"

class CellEmpty : public Cell
{
public:
	CellEmpty();

	void printCell(size_t len) const override;

	Cell* clone() const override;
};