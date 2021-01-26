#pragma once

#include "Command.h"
#include "../Motor.h"

class PrintPositionsCommand : public Command
{
public:
    PrintPositionsCommand(
        Motor& motorX,
        Motor& motorY,
        Motor& motorZ)
        :
        _motorX(motorX),
        _motorY(motorY),
        _motorZ(motorZ)
    {
    }

    bool CanExecute(const String& commandString) const override
    {
        return
            commandString.equalsIgnoreCase("p?") ||
            commandString.equalsIgnoreCase("position?");
    }

    void Execute(const String& commandName, const String& parameters) const override
    {
        Serial.print(_motorX.Position());
        Serial.print(" ");
        Serial.print(_motorY.Position());
        Serial.print(" ");
        Serial.print(_motorZ.Position());
        Serial.println();
    }

private:
    Motor& _motorX;
    Motor& _motorY;
    Motor& _motorZ;
};