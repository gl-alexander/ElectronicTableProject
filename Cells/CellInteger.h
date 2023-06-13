#include "CellString.h"

CellString::CellString(const MyString& value) : _value(value) {}


void CellString::printCell(size_t len, std::ostream& os) const
{
	os << _value;
	PrintHelper::printWhitespaces(len - _value.length(), os);
	os << PRINT_SEPARATOR;
}

Cell* CellString::clone() const
{
	return new CellString(*this);
}

void CellString::setValue(const MyString& value)
{
	_value = value;
}

const MyString& CellString::getValue() const
{
	return _value;
}

double CellString::evaluate() const
{
	if (Validation::validDouble(_value.c_str())) // if the value the string holds is a valid double, we parse and return it
	{
		std::stringstream ss(_value.c_str());
		double parsedValue;
		ss >> parsedValue;
		return parsedValue;
	}
	else
	{
		return 0.0;
	}
}
