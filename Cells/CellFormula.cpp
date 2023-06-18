#include "CellFormula.h"


CellFormula::CellFormula() : Cell(CellType::formula)
{}

CellFormula::CellFormula(const MyString& expression) : Cell(CellType::formula), _expressionString(expression) {}

void CellFormula::printCell(size_t len, std::ostream& os) const
{
	double result = evaluate();
	size_t valueLen = PrintHelper::doubleLen(result);
	os << result;
	PrintHelper::printWhitespaces(len - valueLen, os);
}

void CellFormula::saveToFile(std::ofstream& ofs) const
{
	ofs << _expressionString; // needs to save the expression string rather than the coresponding value
}

Cell* CellFormula::clone() const
{
	return new CellFormula(*this);
}

size_t CellFormula::getLenght() const
{
	return PrintHelper::doubleLen(_expression->evaluate());
}

double CellFormula::evaluate() const
{
	try
	{
		return _expression->evaluate();
	}
	catch (std::logic_error& ex)
	{
		throw;
	}
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
	if (_expression) delete _expression; // if _expression string isn't nullptr we delete it
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