#include <iostream>
#include "Factory/CommandFactory.h"

int main()
{
	Table* table = nullptr;
	while (true)
	{
		try
		{
			CommandFactory::getInstance()->createCommand()->execute(table);
		}
		catch (std::logic_error& ex)
		{
			std::cout << ex.what() << std::endl;
		}
		catch (exit_exception& ex)
		{
			std::cout << ex.what() << std::endl; break;
		}
	}

}
