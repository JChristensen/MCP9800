// Arduino MCP9800 Library
// https://github.com/JChristensen/MCP9800
// Copyright (C) 2014-2025 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch for Raspberry Pi Pico with sensor connected to
// the I2C-1 bus, GP26 and GP27.
// Demonstrates reading ambient temperature in Celsius and Fahrenheit,
// conversion to floating-point, changing device options via the
// Cofiguration register, and changing the Limit-Set and Hysteresis registers.
// Tested with the Arduino-Pico core, https://github.com/earlephilhower/arduino-pico
 
#include <MCP9800.h>        // https://github.com/JChristensen/MCP9800
#include <Streaming.h>      // https://github.com/janelia-arduino/Streaming

MCP9800 mySensor(Wire1);
constexpr int wire1SdaPin {26}, wire1SclPin {27};   // I2C pins for Wire1

void setup()
{
    while (!Serial && millis() < 2000) delay(50);
    Serial.printf("\n%s\nCompiled %s %s %s @ %d MHz\n",
        __FILE__, __DATE__, __TIME__, BOARD_NAME, F_CPU/1000000);

    Wire1.setSDA(wire1SdaPin); Wire1.setSCL(wire1SclPin); Wire1.setClock(400000);
    mySensor.begin();        // initialize the hardware
    displayRegs();           // print the initial register values
    Serial << endl;

    mySensor.writeConfig(MCP9800::ADC_RES_12BITS);       // max resolution, 0.0625 °C
    mySensor.writeTempC2(MCP9800::HYSTERESIS, 0 * 2);    // freezing
    mySensor.writeTempC2(MCP9800::LIMITSET, 100 * 2);    // boiling
}

void loop()
{
    delay(2000);
    displayRegs();
}

// print the values of all four registers on the serial monitor
void displayRegs(void)
{
    uint8_t config = mySensor.readConfig();
    float C = mySensor.readTempC16(MCP9800::AMBIENT) / 16.0;
    float F = mySensor.readTempF10(MCP9800::AMBIENT) / 10.0;
    Serial << F("Config=") << (config < 16 ? F("0x0") : F("0x")) << _HEX(config) << F(", Ambient ") << C << F("C ") << F << 'F';
    
    C = mySensor.readTempC16(MCP9800::HYSTERESIS) / 16.0;
    F = mySensor.readTempF10(MCP9800::HYSTERESIS) / 10.0;
    Serial << F(", Hysteresis ") << C << F("C ") << F << 'F';

    C = mySensor.readTempC16(MCP9800::LIMITSET) / 16.0;
    F = mySensor.readTempF10(MCP9800::LIMITSET) / 10.0;
    Serial << F(", Limit-Set ") << C << F("C ") << F << 'F' << endl;
}
