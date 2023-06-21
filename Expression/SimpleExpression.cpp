#include "SimpleExpression.h"

SimpleExpression::SimpleExpression(double value) 
{
	this->fraction = value;
}

SimpleExpression::SimpleExpression(const Cell* value)
{
	this->cell = value;
}

double SimpleExpression::evaluate() const
{
	if (cell) // if the SimpleExpression holds a cell we return its value
	{
		return cell->evaluate();
	}
	return fraction; // otherwise we return the value of the fraction, which by default is 0
}

Expression* SimpleExpression::clone() const
{
	return new SimpleExpression(*this);
}
