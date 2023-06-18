#pragma once
#include "../Commands/Include.h"

enum class CommandType
{
	OPEN,
	PRINT,
	SAVE,
	SAVE_AS,
	EDIT,
	CLOSE,
	EXIT
};

class CommandFactory
{
	static CommandFactory* instance;

	CommandFactory() = default;
	static CommandType getCommandType(std::stringstream& ss);
	static Open* createOpenCommand(std::stringstream& ss);
	static SaveAs* createSaveAsCommand(std::stringstream& ss);
	static Edit* createEditCommand(std::stringstream& ss);
public:
	static Command* createCommand();

	static CommandFactory* getInstance();
	static void freeInstance();

	CommandFactory(const CommandFactory& other) = delete;
	CommandFactory& operator=(const CommandFactory& other) = delete;
	
};

