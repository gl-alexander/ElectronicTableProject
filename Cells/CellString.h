#pragma once
#include <iostream>
#include "Cell.h"
#include "../Utilities/MyString.h"
#include "../Utilities/Validation/Validation.h"

class CellString : public Cell
{
	MyString _value;
public:
	CellString();

	CellString(const MyString& value);

	void printCell(size_t len, std::ostream& os) const override;

	Cell* clone() const override;

	size_t getLenght() const;

	void setValue(const MyString& value);

	const MyString& getValue() const;

	double evaluate() const override;
};