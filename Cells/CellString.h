#pragma once
#include <iostream>
#include "Cell.h"
#include "../MyString.h"

class CellString : public Cell
{
	int _value = 0;
public:
	CellString();

	void printCell(size_t len) const override;

	Cell* clone() const override;

	void setValue(const MyString& value);

	const MyString& getValue() const;
};