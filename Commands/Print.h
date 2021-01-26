#pragma once

#include "Command.h"

class PrintCommand : public Command
{
public:
    PrintCommand(String name, String output)
        :
        _name(name),
        _output(output)
    {
    }

    bool CanExecute(const String& commandString) const override
    {
        return commandString.equalsIgnoreCase(_name);
    }

    void Execute(const String& commandName, const String& parameters) const override
    {
        Serial.println(_output);
    }

private:
    String _name;
    String _output;
};