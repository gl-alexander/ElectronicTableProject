#pragma once
#include "MyString.h"

enum class CellType
{
	integer,
	fraction,
	string,
	formula
};

class Cell
{
	MyString _value;
	CellType _type;
public:
	void setValue(MyString str);
	void setValue(std::stringstream& ss);

	const CellType& getType() const;
	const MyString& getValue() const;
};

