#include "CellFormula.h"


CellFormula::CellFormula() : Cell(CellType::formula)
{}

CellFormula::CellFormula(const MyString& expression) : Cell(CellType::formula), _expressionString(expression) {}

void CellFormula::printCell(size_t len, std::ostream& os) const
{
	os.precision(PrintHelper::DECIMAL_PLACES_TO_PRINT);
	double result = evaluate();
	size_t valueLen = PrintHelper::doubleLen(result, PrintHelper::DECIMAL_PLACES_TO_PRINT);
	os << result;
	PrintHelper::printWhitespaces(len - valueLen, os);
	os << PRINT_SEPARATOR;
}

Cell* CellFormula::clone() const
{
	return new CellFormula(*this);
}



double CellFormula::evaluate() const
{
	return _expression->evaluate();
}

const MyString& CellFormula::getExpressionString() const
{
	return _expressionString;
}

void CellFormula::setExpressionString(const MyString& value)
{
	_expressionString = value;
}

void CellFormula::setExpressionString(MyString&& value)
{
	_expressionString = std::move(value);
}

void CellFormula::setExpressionObject(Expression* expr)
{
	_expression = expr;
}



//Big 6

void CellFormula::copyFrom(const CellFormula& other)
{
	this->_expression = other._expression->clone();
}
void CellFormula::moveFrom(CellFormula&& other)
{
	this->_expression = other._expression;
	other._expression = nullptr;
}
void CellFormula::free()
{
	delete this->_expression;
}

CellFormula::CellFormula(const CellFormula& other)
{
	copyFrom(other);
}
CellFormula::CellFormula(CellFormula&& other)
{
	moveFrom(std::move(other));
}
CellFormula& CellFormula::operator=(const CellFormula& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}
CellFormula& CellFormula::operator=(CellFormula&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
CellFormula::~CellFormula()
{
	free();
}