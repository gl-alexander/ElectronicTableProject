#include "Command.h"

const char* exit_exception::what() const
{
    return "Exiting the program...";
}
