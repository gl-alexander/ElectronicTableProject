#include <iostream>
#include "Factory/CommandFactory.h"

int main()
{
	PrintHelper::printTitle();
	PrintHelper::printHelp();
	Table* table = nullptr;
	while (true)
	{
		try
		{
			CommandFactory::getInstance()->createCommand()->execute(table);
		}
		catch (std::runtime_error& ex) // invalid values 
		{
			std::cout << ex.what() << std::endl; break;
		}
		catch (std::logic_error& ex) // invalid formula expression
		{
			std::cout << ex.what() << std::endl;
		}
		catch (std::invalid_argument& ex) // invalid value passed
		{
			std::cout << ex.what() << std::endl;
		}
		catch (exit_exception& ex)
		{
			std::cout << ex.what() << std::endl; break;
		}
	}

}
