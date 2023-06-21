#include "CommandFactory.h"

CommandFactory* CommandFactory::instance = nullptr;


CommandType CommandFactory::getCommandType(std::stringstream& ss)
{
    MyString commandName;
    ss >> commandName;
    if (commandName == "open") return CommandType::OPEN;
    else if (commandName == "print") return CommandType::PRINT;
    else if (commandName == "save") return CommandType::SAVE;
    else if (commandName == "saveas") return CommandType::SAVE_AS;
    else if (commandName == "edit") return CommandType::EDIT;
    else if (commandName == "close") return CommandType::CLOSE;
    else if (commandName == "exit") return CommandType::EXIT;

    throw std::invalid_argument("Unknown command type!");

}

Open* CommandFactory::createOpenCommand(std::stringstream& ss)
{
    MyString fileName;
    ss >> fileName; 
    return new Open(fileName);
}

SaveAs* CommandFactory::createSaveAsCommand(std::stringstream& ss)
{
    MyString fileName;
    ss >> fileName;
    return new SaveAs(fileName);
}

Edit* CommandFactory::createEditCommand(std::stringstream& ss)
{
    MyString cellLocation, newValue;
    ss >> cellLocation;
    while (ss.peek() == ' ') ss.ignore();

    char buffer[BUFFER_LEN];
    ss.getline(buffer, BUFFER_LEN);
    newValue = buffer;
    
    return new Edit(cellLocation, newValue);
}

Command* CommandFactory::createCommand()
{
    char buffer[BUFFER_LEN] = { 0 };
    std::cin.getline(buffer, BUFFER_LEN);
    CommandType type;
    std::stringstream ss(buffer);
    try
    {
        type = getCommandType(ss); // shifts the stringstream 
    }
    catch (std::invalid_argument& ex) // unknown command type
    {
        throw;
    }
    switch (type)
    {
    case CommandType::OPEN:
        return createOpenCommand(ss); break;
    case CommandType::PRINT:
        return new Print(); break;
    case CommandType::SAVE:
        return new Save(); break;
    case CommandType::SAVE_AS:
        return createSaveAsCommand(ss); break;
    case CommandType::EDIT:
        return createEditCommand(ss); break;
    case CommandType::CLOSE:
        return new Close(); break;
    case CommandType::EXIT:
        return new Exit(); break;
    }
    return nullptr;
}

CommandFactory* CommandFactory::getInstance()
{
    if (instance == nullptr) {
        instance = new CommandFactory();
    }

    return instance;
}

void CommandFactory::freeInstance()
{
    delete instance;
    instance = nullptr;
}
