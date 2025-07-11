// Arduino MCP9800 Library
// https://github.com/JChristensen/MCP9800
// Copyright (C) 2014-2025 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch. Demonstrates reading of ambient temperature
// in Celsius and Fahrenheit, conversion to floating-point,
// changing device options via the Cofiguration register,
// and changing the Limit-Set and Hysteresis registers.
 
#include <MCP9800.h>        // https://github.com/JChristensen/MCP9800
#include <Streaming.h>      // https://github.com/janelia-arduino/Streaming

MCP9800 mySensor;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial << F( "\n" __FILE__ " " __DATE__ " " __TIME__ "\n" );

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
