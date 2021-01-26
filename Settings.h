#pragma once

#include <EEPROM.h>

class Settings
{
public:
    enum class Key
    {
        // Next = Previous + SizeOfPrevious
        XPosition = 0,
        YPosition = XPosition + sizeof(int),
        ZPosition = YPosition + sizeof(int)
    };

    template<typename T>
    static void Write(Key key, T value)
    {
        EEPROM.put((int)key, value);
    }

    template<typename T>
    static T Read(Key key)
    {
        T value;
        EEPROM.get((int)key, value);

        return value;
    }
};