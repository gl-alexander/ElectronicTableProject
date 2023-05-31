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

	void setCellType(const char* str);
public:
	Cell() = default;
	Cell(std::stringstream& ss);

	void setValue(std::stringstream& ss);

	const CellType& getType() const;
	const MyString& getValue() const;
};

