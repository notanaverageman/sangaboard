#pragma once

#include "Arduino.h"

class Command
{
public:
    virtual bool CanExecute(const String &commandName) const = 0;
    virtual void Execute(const String &commandName, const String &parameters) const = 0;

    static String GetParameter(const String &parameters, int parameterIndex)
    {
        int numberOfPassedParameters = 0;
        int startIndex = -1;
        int endIndex = -1;

        for (size_t i = 0; i < parameters.length(); i++)
        {
            if (parameters.charAt(i) == ' ')
            {
                numberOfPassedParameters++;
                continue;
            }

            if (numberOfPassedParameters == parameterIndex)
            {
                if (startIndex < 0)
                {
                    startIndex = i;
                }

                endIndex = i;
                continue;
            }
            else if (numberOfPassedParameters > parameterIndex)
            {
                break;
            }
        }

        if (startIndex >= 0)
        {
            return parameters.substring(startIndex, endIndex + 1);
        }

        return "";
    }
};