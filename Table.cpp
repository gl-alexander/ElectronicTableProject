#include "Table.h"
#include "Utilities/ParseHelper/ParseHelper.h"

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

void Table::readFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::in);

	if (!ifs.is_open())
		throw std::runtime_error("File not found!");

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
			// check for missing comma . . .
			// for cycle, checking for valid value type from the input ex.what()
			// if not found, output unknown data type error

			std::cout << "Error: row " << i << ", " << ex.what() << " is unknown data type\n";
		}
	}
}

Table::Table(const char* fileName)
{
	try
	{
		readFromFile(fileName);
	}
	catch (std::runtime_error& ex)
	{
		std::cout << ex.what();
	}


	try
	{
		parseFromulas();
	}
	catch (std::logic_error& ex)
	{
		std::cout << "Invalid Formula at cell location " << ex.what();
	}

}

void Table::printTypes() const
{
	size_t rowsCount = _rows.size();
	for (int i = 0; i < rowsCount; i++)
	{
		_rows[i].printValueTypes();
	}
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

void Table::print(std::ostream& os) const
{
	unsigned longestRowLen = getLongestRowLenght();
	unsigned longestCell = getLongestCell();
	size_t rowsCount = _rows.size();

	for (int i = 0; i < rowsCount; i++)
	{
		_rows[i].printRow(longestRowLen, longestCell, os);
		std::cout << std::endl;
	}
}

const Cell* Table::getCellByLocation(size_t rowInd, size_t colInd) const
{
	if (rowInd > _rows.size()) return nullptr;
	if (colInd > _rows[rowInd - 1].lenght()) return nullptr;
	//if we reach this part then the coordinates are within range
	return _rows[rowInd - 1][colInd - 1]; // we start counting from 1, 1
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
			if (_rows[i][j]->getType() == CellType::formula)
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
