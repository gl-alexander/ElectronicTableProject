#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(char operation, Expression* left, Expression* right) : left(left), right(right), operation(operation)
{}

double BinaryExpression::evaluate() const
{
	try
	{
		switch (operation)
		{
		case '+': return left->evaluate() + right->evaluate(); break;
		case '-': return left->evaluate() - right->evaluate(); break;
		case '*': return left->evaluate() * right->evaluate(); break;
		case '/':
		{
			if (right->evaluate() == 0) throw std::logic_error("Cannot Divide by 0");
			return left->evaluate() / right->evaluate();
			break;
		}
		case '^': return pow(left->evaluate(), right->evaluate()); break;
		}
	}
	catch (std::logic_error& ex)
	{
		throw;
	}
}

Expression* BinaryExpression::clone() const
{
	return new BinaryExpression(operation, left->clone(), right->clone());
}


BinaryExpression::~BinaryExpression()
{
	delete left;
	delete right;
}
