#pragma once

#include "Command.h"
#include "../Stopwatch.h"
#include "../Motor.h"

class MoveRelativeCommand : public Command
{
public:
    MoveRelativeCommand(
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
            commandString.equalsIgnoreCase("mrx") ||
            commandString.equalsIgnoreCase("mry") ||
            commandString.equalsIgnoreCase("mrz") ||
            commandString.equalsIgnoreCase("mr");
    }

    void Execute(const String& commandName, const String& parameters) const override
    {
        int stepsX = 0;
        int stepsY = 0;
        int stepsZ = 0;

        if(commandName.equalsIgnoreCase("mr"))
        {
            if(
                !GetParameter(parameters, 0, stepsX) ||
                !GetParameter(parameters, 1, stepsY) ||
                !GetParameter(parameters, 2, stepsZ))
            {
                return;
            }
        }
        else if(
            !GetParameter(commandName, "mrx", parameters, 0, stepsX) ||
            !GetParameter(commandName, "mry", parameters, 0, stepsY) ||
            !GetParameter(commandName, "mrz", parameters, 0, stepsZ))
        {
            return;
        }

        ExecutionData x(_motorX, stepsX);
        ExecutionData y(_motorY, stepsY);
        ExecutionData z(_motorZ, stepsZ);

        int maxSteps = max(max(abs(stepsX), abs(stepsY)), abs(stepsZ));
        int steps = 0;

        Stopwatch stopwatch;

        while(steps <= maxSteps)
        {
            unsigned long elapsed = stopwatch.Elapsed();

            if(elapsed < Motor::MinimumDelayInMilliseconds * 1000)
            {
                continue;
            }

            double progress = steps / (double)maxSteps;

            x.Execute(progress);
            y.Execute(progress);
            z.Execute(progress);

            steps++;

            stopwatch.Reset();
        }

        x.Finish();
        y.Finish();
        z.Finish();

        // Server expects an answer.
        Serial.println("Done.");
    }

private:
    bool GetParameter(
        const String& commandName,
        const String& expectedCommandName,
        const String& parameters,
        int parameterIndex,
        int& parameter) const
    {
        if(!commandName.equalsIgnoreCase(expectedCommandName))
        {
            parameter = 0;
            return true;
        }

        return GetParameter(parameters, parameterIndex, parameter);
    }

    bool GetParameter(const String& parameters, int parameterIndex, int& parameter) const
    {
        String parameterString = Command::GetParameter(parameters, parameterIndex);

        if(parameterString.length() == 0)
        {
            INFO("Invalid parameters: ", parameters);
            return false;
        }

        parameter = parameterString.toInt();

        return true;
    }

    class ExecutionData
    {
    public:
        ExecutionData(Motor& motor, int totalSteps)
            :
            _motor(motor),
            _direction(totalSteps > 0 ? Direction::Clockwise : Direction::CounterClockwise),
            _totalSteps(abs(totalSteps)),
            _currentSteps(0)
        {
        }

        void Execute(double progress)
        {
            int steps = (int)(_totalSteps * progress);
            int stepsToMove = steps - _currentSteps;

            for (int i = 0; i < stepsToMove; i++)
            {
                _motor.Step(_direction);
            }

            _currentSteps = steps;
        }

        void Finish()
        {
            _motor.Release();
            _motor.Save();
        }

    private:
        Motor& _motor;
        Direction _direction;
        int _totalSteps;
        int _currentSteps;
    };

    Motor& _motorX;
    Motor& _motorY;
    Motor& _motorZ;
};