#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(Expression* left, Expression* right, char operation) : left(left), right(right), operation(operation)
{}

double BinaryExpression::evaluate() const
{
	switch (operation)
	{
	case '+': return left->evaluate() + right->evaluate(); break;
	case '-': return left->evaluate() - right->evaluate(); break;
	case '*': return left->evaluate() * right->evaluate(); break;
	case '/': return left->evaluate() / right->evaluate(); break; // throw if 0
	case '^': return pow(left->evaluate(), right->evaluate()); break;
	}
}

Expression* BinaryExpression::clone() const
{
	return new BinaryExpression(*this);
}
