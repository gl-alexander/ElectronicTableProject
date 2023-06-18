#include "Table.h"


#define MAX(a, b) ((a) > (b) ? (a) : (b))


static int countCharacterOccurances(std::ifstream& ifs, char ch)
{
	unsigned counter = 0;
	int originalPosition = ifs.tellg();
	ifs.seekg(0, std::ios::beg);
	while (!ifs.eof())
	{
		if (ifs.get() == ch) counter++;
	}
	ifs.clear();
	ifs.seekg(originalPosition);
	return counter;
}

void Table::readFromFile(const MyString& fileName)
{
	std::ifstream ifs(fileName.c_str(), std::ios::in);

	if (!ifs.is_open())
		throw std::invalid_argument("File not found!");

	_filePath = fileName; // saving the filename
	size_t linesCount = countCharacterOccurances(ifs, '\n');

	_rows = MyVector<Row>(linesCount + 1);

	for (int i = 0; i <= linesCount; i++)
	{
		try
		{
			_rows.push_back(Row(ifs));
		}
		catch (std::invalid_argument& ex)
		{
			// exception message looks like col: # [invalid value string]
			std::stringstream ss(ex.what());
			char buffer[BUFFER_LEN] = { 0 };
			ss >> buffer; // skips "col::
			ss >> buffer; // skips the column#
			ss >> buffer; // gets the invalid value;
			size_t valueLen = strlen(buffer);
			for (int j = 1; j < valueLen; j++)
			{
				char removed = buffer[i];
				buffer[i] = '\0';
				if (Validation::validValue(buffer))
				{
					MyString errorMessage = "Missing comma (,) at row " + MyString(intToString(i)) + " " + MyString(intToString(i));
					throw std::runtime_error(errorMessage.c_str());
				}		
			}

			MyString errorMsg = "Error: row " + MyString(intToString(i)) + ex.what() + " is unknown data type\n";
			throw std::runtime_error(errorMsg.c_str());
		}
	}
	
	ifs.close();
}

Table::Table(const MyString& fileName)
{
	try
	{
		readFromFile(fileName);
	}
	catch (std::invalid_argument& ex) // invalid file name
	{
		throw;
	}
	catch (std::runtime_error& ex) // invalid value
	{
		throw;
	}

	try
	{
		parseFromulas();
	}
	catch (std::logic_error& ex)
	{
		MyString errorMsg = "Invalid Formula at cell location ";
		errorMsg += ex.what();
		throw std::logic_error(errorMsg.c_str());
	}
	setPrintingWidths();
}

unsigned Table::getLongestRowLenght() const
{
	unsigned longestRow = 0;
	size_t rowsCount = _rows.size();
	for (int i = 0; i < rowsCount; i++)
	{
		longestRow = MAX(longestRow, _rows[i].lenght());
	}
	return longestRow;
}

unsigned Table::getLongestCell() const
{
	unsigned longestCell = 0;
	size_t rowsCount = _rows.size();
	for (int i = 0; i < rowsCount; i++)
	{
		longestCell = MAX(longestCell, _rows[i].getLongestCell());
	}
	return longestCell;
}

void Table::printFirstRow(std::ostream& os) const
{
	size_t cellsLen = _printingWidths.size();
	for (int i = 0; i < cellsLen; i++)
	{
		PrintHelper::printCharNTimes('_', _printingWidths[i] + 1, os);
	}
}

void Table::printSeparatorRow(std::ostream& os) const
{
	size_t cellsLen = _printingWidths.size();
	os << PRINT_SEPARATOR;
	for (int i = 0; i < cellsLen; i++)
	{
		PrintHelper::printCharNTimes('_', _printingWidths[i], os);
		os << PRINT_SEPARATOR;
	}
	os << std::endl;
}


void Table::print(std::ostream& os) const
{
	
	unsigned longestRowLen = getLongestRowLenght();
	unsigned longestCell = getLongestCell();

	os << '>' << _filePath;

	os << std::endl << std::endl;;

	printFirstRow(os);
	os << std::endl;

	size_t rowsCount = _rows.size();
	for (int i = 0; i < rowsCount; i++)
	{
		//os << i + 1;
		_rows[i].printRow(longestRowLen, _printingWidths, os);
		os << std::endl;
		printSeparatorRow(os);
	}
}

const Cell* Table::getCellByLocation(size_t rowInd, size_t colInd) const
{
	if (rowInd > _rows.size()) return nullptr;
	if (colInd > _rows[rowInd - 1].lenght()) return nullptr;
	//if we reach this part then the coordinates are within range
	return _rows[rowInd - 1][colInd - 1]; // we start counting from 1, 1
}

void Table::saveToFile(const MyString& filePath) const
{
	std::ofstream ofs(filePath.c_str(), std::ios::out | std::ios::trunc);

	if (!ofs.is_open())
		throw std::invalid_argument("Cannot open file for editing!");
	size_t rowsCount = _rows.size();
	for (int i = 0; i < rowsCount; i++)
	{
		_rows[i].saveToFile(ofs);
		if(i < rowsCount - 1) ofs << std::endl;
	}

}

const MyString& Table::getTableFilePath() const
{ 
	return _filePath;
}

void Table::editCell(const MyString& cellLocation, const MyString& newValue)
{
	//Validation
	if (!Validation::validCellLocation(cellLocation)) throw std::invalid_argument("Invalid Cell Location");
	if (!Validation::validValue(newValue.c_str())) throw std::invalid_argument("Invalid value passed");

	size_t row, col;
	row = col = 0;
	getRowAndColumn(cellLocation.c_str(), row, col); // saves row and column indexes from the passed location;
	const Cell* cell = getCellByLocation(row, col); // checks if it's within bounds and returns nullptr if it isn't

	if (cell) // there's already a cell at this location
	{
		editExistingCell(row - 1, col - 1, newValue); // we pass row and col as indexes starting from 0
	}
	else
	{
		addNewCell(row - 1, col - 1, newValue);
	}

	parseFromulas(); // we need to parse the formulas again
	setPrintingWidths(); // and check for printing widths
}
void Table::editExistingCell(size_t row, size_t col, const MyString& newValue)
{
	Cell* cell = _rows[row][col];

	if (cell->getType() == CellFactory::getType(newValue.c_str())) // this means we can just change the _value of the cell
	{
		editSameType(cell, newValue);
	}
	else // we get a different cell type
	{
		delete cell; // erase the previous data
		std::stringstream ss(newValue.c_str());
		_rows[row][col] = CellFactory::createCell(ss);
	}
}

void Table::addNewCell(size_t row, size_t col, const MyString& newValue)
{
	// row and col are passed as indexes
	if (row >= _rows.size()) // we need to add more rows
	{
		size_t currentSize = _rows.size();
		for (int i = currentSize; i <= row; i++)
		{
			_rows.push_back(Row()); // we add empty Rows until we have enough
		}
	}
	if (col >= _rows[row].lenght())
	{
		size_t currentSize = _rows[row].lenght();
		for (int i = currentSize; i <= col; i++)
		{
			_rows[row].add(new CellEmpty()); // and we fill the row we need with empty cells
		}
	}
	// by this point we have enough rows and colums to add the new cell
	std::stringstream ss(newValue.c_str());
	_rows[row][col] = CellFactory::createCell(ss);
}

// we make use of the already created cell*, passing only the new values
void Table::editSameType(Cell* cell, const MyString& newValue)
{
	CellInteger* integer = nullptr;
	CellFraction* fraction = nullptr;
	CellString* str = nullptr;
	CellFormula* formula = nullptr;
	switch (cell->getType())
	{
	case CellType::integer:
		integer = static_cast<CellInteger*>(cell);
		*integer = CellInteger(toInt(newValue.c_str())); break;

	case CellType::fraction:
		fraction = static_cast<CellFraction*>(cell);
		*fraction = CellFraction(toDouble(newValue.c_str())); break;

	case CellType::string:
		str = static_cast<CellString*>(cell);
		*str = CellString(parseString(newValue.c_str())); break;

	case CellType::formula:
		formula = static_cast<CellFormula*>(cell);
		formula->setExpressionString(newValue);
		formula->setExpressionObject(ExpressionFactory::getInstance()->createExpression(extractExpression(newValue)));
		break;
	} // if we get an emptyCell we don't need to do anything
}

void Table::setPrintingWidths()
{
	_printingWidths.clear();
	size_t longestRow = getLongestRowLenght();
	for (int i = 0; i < longestRow; i++)
		_printingWidths.push_back(DEFAULT_CELL_LEN);

	size_t rows = _rows.size();
	for (int i = 0; i < rows; i++)
	{
		size_t currentLen = _rows[i].lenght();
		for (int j = 0; j < currentLen; j++)
		{
			_printingWidths[j] = MAX(_printingWidths[j], _rows[i][j]->getLenght()); // gets the longest cell in column
		}
	}
}



void Table::parseFormula(CellFormula* formula)
{
	StringView expressionStrView = extractExpression(formula->getExpressionString()); // skips the '=' and whitespaces before the expression
	Expression* expr = ExpressionFactory::getInstance()->createExpression(expressionStrView);
	formula->setExpressionObject(expr);

	try
	{
		formula->evaluate();
	}
	catch (std::logic_error& ex)
	{
		throw;
	}
}

void Table::parseFromulas()
{
	ExpressionFactory::getInstance()->passGetCellFunction(&Table::getCellByLocation, this);

	for (int i = 0; i < _rows.size(); i++)
	{
		for (int j = 0; j < _rows[i].lenght(); j++)
		{
			if (_rows[i][j] && _rows[i][j]->getType() == CellType::formula)
			{
				try
				{
					parseFormula(static_cast<CellFormula*>(_rows[i][j])); // if the formula is invalid
				}
				catch (std::logic_error& ex)
				{
					MyString errorCellLocationString = "R";
					errorCellLocationString += intToString(i + 1);
					errorCellLocationString += "C";
					errorCellLocationString += intToString(j + 1);
					throw std::logic_error(errorCellLocationString.c_str());
				}
			}
		}
	}
}

