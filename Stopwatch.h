#pragma once

class Stopwatch
{
public:
    Stopwatch()
    {
        Reset();
    }

    unsigned long Elapsed()
    {
        // Overflows do not affect this calculation:
        // https://www.norwegiancreations.com/2018/10/arduino-tutorial-avoiding-the-overflow-issue-when-using-millis-and-micros/
        unsigned long now = micros();
        return now - _offset;
    }

    void Reset()
    {
        _offset = micros();
    }

private:
    unsigned long _offset;
};