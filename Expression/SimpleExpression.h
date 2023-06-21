#pragma once
#include "Expression.h"



class SimpleExpression : public Expression
{
	const Cell* cell = nullptr;
	double fraction = 0;
public: 
	SimpleExpression() = default;
	SimpleExpression(double value);
	SimpleExpression(const Cell* value);

	double evaluate() const override;
	Expression* clone() const override;
};

