#include "CellFactory.h"



static void readAndFormatData(std::stringstream& ss, char* buffer)
{
	size_t initialPosition = ss.tellg();
	ss.getline(buffer, BUFFER_LEN, SEPARATOR);
	ss.seekg(initialPosition);
	ss.clear();

	size_t len = strlen(buffer);
	int leadingWhiteSpaces = countLeadingSymbols(buffer, ' ');
	int endingWhiteSpaces = countEndSymbols(buffer, len, ' ');

	buffer[len - endingWhiteSpaces] = '\0'; // this 'cuts' the buffer at the last non-whitespace symbol
	buffer += leadingWhiteSpaces;
}

const CellType& CellFactory::getType(const char* str)
{
	if (Validation::emptyString(str))
	{
		return CellType::empty;
	}
	// if we've reached this part, the cell is not empty
	//setting the cell type
	if (Validation::validInteger(str)) return CellType::integer;
	else if (Validation::validDouble(str)) return CellType::fraction;
	else if (Validation::validFormula(str)) return CellType::formula;
	else if (Validation::validString(str)) return CellType::string;
	else
	{
		throw std::invalid_argument(str); // no suitable type was found
	}
}

Cell* CellFactory::createIntegerCell(std::stringstream& ss)
{
	int value;
	ss >> value;

	if (!ss.eof()) throw std::logic_error("Too many arguments passed!");

	return new CellInteger(value);
}
Cell* CellFactory::createStringCell(std::stringstream& ss)
{
	MyString value;
	ss >> value;

	if (!ss.eof()) throw std::logic_error("Too many arguments passed!");

	return new CellString(value);
}
Cell* CellFactory::createFractionCell(std::stringstream& ss)
{
	double value;
	ss >> value;
	
	if (!ss.eof()) throw std::logic_error("Too many arguments passed!"); // if we have more data after reading, then the input is incorrect

	return new CellFraction(value);
}
Cell* CellFactory::createFormulaCell(std::stringstream& ss)
{
	//TBD
	return nullptr;
}

Cell* CellFactory::createCell(std::stringstream& ss)
{
	
	char buffer[BUFFER_LEN] = { 0 };

	readAndFormatData(ss, buffer); // reads and formats the data

	CellType type = CellType::empty;

	try 
	{
		type = getType(buffer); // determines the type 
	}
	catch (std::invalid_argument& ex) // catches if getType doesn't find a suitable type
	{
		throw;
	}
	catch (std::logic_error& ex) // catches if too many arguments have been passed 
	{
		std::cout << ex.what();
	}
	
	switch (type)
	{
	case CellType::empty:
		return new CellEmpty(); break;
	case CellType::integer:
		return createIntegerCell(ss); break;
	case CellType::fraction:
		return createFractionCell(ss); break;
	case CellType::string:
		return createStringCell(ss); break;
	case CellType::formula:
		return createFormulaCell(ss); break;
	}
}
