#pragma once
#include "MyString.h"
#include <sstream>

const size_t BUFFER_LEN = 1024;
const char SEPARATOR = ',';

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
	MyString _value;
	CellType _type;

public:
	void setValue(MyString str);
	void setValue(std::stringstream& ss);

	const CellType& getType() const;
	const MyString& getValue() const;
};

