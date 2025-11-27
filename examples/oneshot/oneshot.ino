// Arduino MCP9800 Library
// https://github.com/JChristensen/MCP9800
// Copyright (C) 2014-2025 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch. Demonstrates one-shot temperature measurement,
// which significantly reduces the current drawn by the sensor.
 
#include <MCP9800.h>        // https://github.com/JChristensen/MCP9800
#include <Streaming.h>      // https://github.com/janelia-arduino/Streaming

MCP9800 mySensor;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial << F( "\n" __FILE__ " " __DATE__ " " __TIME__ "\n" );

    // start sensor in shutdown mode, with maximum resolution
    mySensor.begin(MCP9800::ADC_RES_12BITS + MCP9800::SHUTDOWN);
}

void loop()
{
    // start the conversion.
    mySensor.startOneShot();

    // wait for it to complete.
    // datasheet says 240ms typical for 12 bit resolution.
    constexpr uint32_t dly {250};
    int nDelay {0};
    do {
        delay(dly);
        ++nDelay;
    } while (!mySensor.oneShotComplete());
    
    float C = mySensor.readTempC16(MCP9800::AMBIENT) / 16.0;
    float F = mySensor.readTempF10(MCP9800::AMBIENT) / 10.0;
    Serial << C << "C " << F << "F " << dly * nDelay << "ms\n";
    delay(10000);
}
