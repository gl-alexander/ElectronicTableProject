#pragma once
#include "Expression.h"

union Value
{
	const Cell* cell = nullptr;
	double fraction;
};

class SimpleExpression : public Expression
{
	Value value;
public: 
	SimpleExpression() = default;
	SimpleExpression(double value);
	SimpleExpression(const Cell* value);

	double evaluate() const override;
	Expression* clone() const override;
};

