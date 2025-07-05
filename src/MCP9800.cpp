// Arduino MCP9800 Library
// https://github.com/JChristensen/MCP9800
// Copyright (C) 2014-2025 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Arduino Library for Microchip MCP9800/1/2/3 2-Wire High-Accuracy
// Temperature Sensors

#include <MCP9800.h>

void MCP9800::begin()
{
    wire.begin();
}

// read one of the sensor's three temperature registers.
// returns the temperature as an integer which is °C times 16.
int MCP9800::readTempC16(MCP9800_REGS_t reg)
{
    wire.beginTransmission(m_devAddr);
    wire.write(reg);
    wire.endTransmission();

    wire.requestFrom(m_devAddr, (uint8_t)2);
    int8_t msb = wire.read();
    uint8_t lsb = wire.read();
    return (msb << 4) + (lsb >> 4);
}

// read one of the sensor's three temperature registers.
// returns the temperature as an integer which is °F times 10.
int MCP9800::readTempF10(MCP9800_REGS_t reg)
{
    long tF160 = (long)readTempC16(reg) * 18L;
    int tF10 = tF160 / 16;
    if ( (tF160 & 15) >= 8) ++tF10;    // round up to the next tenth if needed
    tF10 += 320;                       // add in the offset (*10)
    return tF10;
}

void MCP9800::writeTempC2(MCP9800_REGS_t reg, const int value)
{
    union intByte_t {int i; byte b[2];} t;

    if (reg > AMBIENT) {    // ambient temp reg is read-only
        t.i = value << 7;
        wire.beginTransmission(m_devAddr);
        wire.write(reg);
        wire.write(t.b[1]);
        wire.write(t.b[0]);
        wire.endTransmission();
    }
}

// read the sensor's configuration register
uint8_t MCP9800::readConfig()
{
    wire.beginTransmission(m_devAddr);
    wire.write(CONFIG_REG);
    wire.endTransmission();

    wire.requestFrom(m_devAddr, (uint8_t)1);
    return Wire.read();
}

// write the sensor's configuration register
void MCP9800::writeConfig(const uint8_t value)
{
    wire.beginTransmission(m_devAddr);
    wire.write(CONFIG_REG);
    wire.write(value);
    wire.endTransmission();
}
