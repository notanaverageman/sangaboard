#pragma once

#include "Command.h"
#include "../Motor.h"

class ResetPositionsCommand : public Command
{
public:
    ResetPositionsCommand(
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
        return commandString.equalsIgnoreCase("zero");
    }

    void Execute(const String& commandName, const String& parameters) const override
    {
        _motorX.ResetPosition();
        _motorY.ResetPosition();
        _motorZ.ResetPosition();
    }

private:
    Motor& _motorX;
    Motor& _motorY;
    Motor& _motorZ;
};