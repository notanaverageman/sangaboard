#pragma once

#include "Command.h"
#include "../Motor.h"

class ReleaseMotorsCommand : public Command
{
public:
    ReleaseMotorsCommand(
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
        return commandString.equalsIgnoreCase("release");
    }

    void Execute(const String& commandName, const String& parameters) const override
    {
        _motorX.Release();
        _motorY.Release();
        _motorZ.Release();
    }

private:
    Motor& _motorX;
    Motor& _motorY;
    Motor& _motorZ;
};