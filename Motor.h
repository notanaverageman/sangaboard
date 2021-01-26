#pragma once

#include "Direction.h"
#include "Settings.h"

class Motor
{
public:
    static constexpr int NumberOfPins = 4;
    static constexpr int MinimumDelayInMilliseconds = 2;

    Motor(
        const char* name,
        short pinNumber,
        Settings::Key positionSetting)
        :
        _name(name),
        _pinNumber(pinNumber),
        _stepNumber(0),
        _position(0),
        _positionSetting(positionSetting)
    {
        for (size_t i = 0; i < NumberOfPins; i++)
        {
            pinMode(_pinNumber + i, OUTPUT);
        }

        _position = Settings::Read<int>(_positionSetting);
    }

    const char* Name() const
    {
        return _name;
    }

    int Position()
    {
        return _position;
    }

    void Release()
    {
        for (size_t i = 0; i < NumberOfPins; i++)
        {
            digitalWrite(_pinNumber + i, LOW);
        }
    }

    void Save()
    {
        Settings::Write<int>(_positionSetting, _position);
    }

    void ResetPosition()
    {
        _position = 0;
        Save();
    }

    void Step(Direction direction)
    {
        for (size_t i = 0; i < NumberOfPins; i++)
        {
            int value = _stepNumber == i ? HIGH : LOW;

            DEBUG("Motor ", _name, " step number: ", _stepNumber, " pin: ", _pinNumber + i, " value: ", value)

            digitalWrite(_pinNumber + i, value);
        }

        if(direction == Direction::Clockwise)
        {
            _stepNumber++;
            _stepNumber = _stepNumber < NumberOfPins ? _stepNumber : 0;

            _position++;
        }
        else
        {
            _stepNumber--;
            _stepNumber = _stepNumber >= 0 ? _stepNumber : NumberOfPins - 1;

            _position--;
        }
    }

private:
    const char* _name;

    short _pinNumber;
    short _stepNumber;

    int _position;

    Settings::Key _positionSetting;
};