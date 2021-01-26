#include "Logging.h"
#include "Motor.h"
#include "Settings.h"

#include "Commands/MoveRelative.h"
#include "Commands/Print.h"
#include "Commands/PrintPositions.h"
#include "Commands/ReleaseMotors.h"
#include "Commands/ResetPositions.h"

constexpr int motorXPinNumber = 2;  // D2,  D3,  D4,  D5
constexpr int motorYPinNumber = 6;  // D6,  D7,  D8,  D9
constexpr int motorZPinNumber = 10; // D10, D11, D12, D13

Motor motorX("X", motorXPinNumber, Settings::Key::XPosition);
Motor motorY("Y", motorYPinNumber, Settings::Key::YPosition);
Motor motorZ("Z", motorZPinNumber, Settings::Key::ZPosition);

Command* commands[] =
{
    (Command*)new PrintCommand("version", "Sangaboard Firmware v0.5"),
    (Command*)new PrintCommand("board", "Sangaboard v0.2"),
    (Command*)new MoveRelativeCommand(motorX, motorY, motorZ),
    (Command*)new ReleaseMotorsCommand(motorX, motorY, motorZ),
    (Command*)new ResetPositionsCommand(motorX, motorY, motorZ),
    (Command*)new PrintPositionsCommand(motorX, motorY, motorZ),
    (Command*)new PrintCommand("dt?", "0"),
    (Command*)new PrintCommand("ramp_time?", "0"),
    (Command*)new PrintCommand("list_modules", "--END--"),
};

int numberOfCommands = (sizeof(commands) / sizeof(commands[0]));

void setup()
{
    Serial.begin(115200);
    Serial.println("Sangaboard Firmware v0.5");
}

void loop()
{
    String line = Serial.readStringUntil('\n');
    line.trim();

    if(line.length() == 0)
    {
        return;
    }

    DEBUG("Received input: ", line)

    String commandString = Command::GetParameter(line, 0);
    bool executed = false;

    for (size_t i = 0; i < numberOfCommands; i++)
    {
        Command* command = commands[i];

        if(!command->CanExecute(commandString))
        {
            continue;
        }

        DEBUG("Executing command: ", commandString)

        String parameters = line.substring(commandString.length());
        parameters.trim();

        command->Execute(commandString, parameters);

        executed = true;
        break;
    }

    if(!executed)
    {
        INFO("Unknown command: ", line)
    }

    DEBUG("------------------------------")
    DEBUG("")
}