#include "CellFactory.h"
#pragma warning(disable : 4996)


const char* readAndFormatData(std::stringstream& ss)
{
	char buffer[BUFFER_LEN] = { 0 };
	ss.getline(buffer, BUFFER_LEN, SEPARATOR); // this is what moves the get pointer to the next cell

	size_t len = strlen(buffer);
	int leadingWhiteSpaces = Validation::countLeadingSymbols(buffer, ' ');
	int endingWhiteSpaces = Validation::countEndSymbols(buffer, len, ' ');

	buffer[len - endingWhiteSpaces] = '\0'; // this 'cuts' the buffer at the last non-whitespace symbol
	return buffer + leadingWhiteSpaces;
}


Cell* CellFactory::createIntegerCell(const char* str)
{
	std::stringstream ss(str);
	int value;
	ss >> value;

	return new CellInteger(value);
}
Cell* CellFactory::createStringCell(const char* str)
{
	return new CellString(str);
}
Cell* CellFactory::createFractionCell(const char* str)
{
	std::stringstream ss(str);
	double value;
	ss >> value;

	return new CellFraction(value);
}
Cell* CellFactory::createFormulaCell(const char* str)
{
	return new CellFormula(str);
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


Cell* CellFactory::createCell(std::stringstream& ss)
{
	
	char buffer[BUFFER_LEN] = { 0 };
	strcpy(buffer, readAndFormatData(ss));
	 // reads and formats the data to the next separator ','

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
		return createIntegerCell(buffer); break;
	case CellType::fraction:
		return createFractionCell(buffer); break;
	case CellType::string:
		return createStringCell(buffer); break;
	case CellType::formula:
		return createFormulaCell(buffer); break;
	}
}