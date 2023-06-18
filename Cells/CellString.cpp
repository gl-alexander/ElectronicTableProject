#include "CellString.h"

CellString::CellString() : Cell(CellType::string)
{}

CellString::CellString(const MyString& value) : Cell(CellType::string), _value(value) {}


void CellString::printCell(size_t len, std::ostream& os) const
{
	os << _value;
	PrintHelper::printWhitespaces(len - _value.length(), os);
}

void CellString::saveToFile(std::ofstream& ofs) const
{
	size_t strlen = _value.length();
	ofs << '"';

	for (int i = 0; i < strlen; i++) // we only want to do this for the quotes within the string
	{
		if (_value[i] == '\"') // if there's ' " ' in the string it needs to have '\' before it
			ofs << '\\'; // we need to print the '\' we skipped when reading
		ofs << _value[i];
	}

	ofs << '"';
}

Cell* CellString::clone() const
{
	return new CellString(*this);
}

size_t CellString::getLenght() const
{
	return _value.length();
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
	StringView str = _value;
	// if the value the string holds is a valid double, we parse and return it
	if (Validation::validDouble(str.substr(1, str.length() - 2))) // we skip the beginning and ending quotes
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
