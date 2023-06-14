#include "ExpressionFactory.h"
#include "../Utilities/ParseHelper/ParseHelper.h"

ExpressionFactory* ExpressionFactory::instance = nullptr;




void ExpressionFactory::freeInstance()
{
    delete instance;
    instance = nullptr;
}

ExpressionFactory* ExpressionFactory::getInstance()
{
	if (instance == nullptr) {
		instance = new ExpressionFactory();
	}

	return instance;
}

ExpressionFactory::ExpressionFactory() : obj(nullptr), getCellFunction(nullptr)
{}


void ExpressionFactory::passGetCellFunction(FunctionPointer func, Table* obj)
{
	this->getCellFunction = func;
	this->obj = obj;
}

const Cell* ExpressionFactory::getCell(const StringView& str) const
{
	size_t row = 0;
	size_t col = 0;
	getRowAndColumn(str, row, col);
	return (obj->*getCellFunction)(row, col);
}

Expression* ExpressionFactory::createExpression(const StringView& str) const
{
	if (str.length() == 0) 
	{
		return nullptr;
	}

	if (Validation::validDouble(str)) 
	{
		return new SimpleExpression(toDouble(str));
	}

	if (Validation::validCellLocation(str))
	{
		return new SimpleExpression(getCell(str));
	}

	StringView strWithoutBrackets = str.substr(1, str.length() - 2);
	size_t length = strWithoutBrackets.length();
	size_t bracketsCounter = 0;
	for (size_t i = 0; i < length; i++) 
	{
		if (strWithoutBrackets[i] == '(') 
		{
			bracketsCounter++;
		}
		else if (strWithoutBrackets[i] == ')') 
		{
			bracketsCounter--;
		}
		else if (Validation::isOperator(strWithoutBrackets[i]) && bracketsCounter == 0)
		{
			return new BinaryExpression(
				strWithoutBrackets[i],
				createExpression(strWithoutBrackets.substr(0, i)),
				createExpression(strWithoutBrackets.substr(i + 1, length - i - 1))
			);
		}
	}


	return nullptr;
}
