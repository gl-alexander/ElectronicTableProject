#include "SimpleExpression.h"

SimpleExpression::SimpleExpression(double value) 
{
	this->value.fraction = value;
}

SimpleExpression::SimpleExpression(const Cell* value)
{
	this->value.cell = value;
}

double SimpleExpression::evaluate() const
{
	if (value.cell) // if the SimpleExpression holds a cell we return its value
	{
		return value.cell->evaluate();
	}
	return value.fraction; // otherwise we return the value of the fraction, which by default is 0
}

Expression* SimpleExpression::clone() const
{
	return new SimpleExpression(*this);
}
