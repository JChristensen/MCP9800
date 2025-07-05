# Arduino MCP9800 Temperature Sensor Library
https://github.com/JChristensen/MCP9800  
README file  
Jack Christensen
Jul 2025

## License
Arduino MCP9800 Library Copyright (C) 2014-2025 by Jack Christensen GNU GPL v3.0

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License v3.0 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/gpl.html>

## Introduction
**Arduino Library for Microchip MCP9800/1/2/3 2-Wire High-Accuracy Temperature Sensors**

A lightweight implementation that exposes all functionality of the [Microchip MCP9800/1/2/3 sensors](https://www.microchip.com/en-us/product/MCP9800). Temperatures are dealt with in the integer domain to avoid the code size and runtime overhead associated with floating-point. Still, it is straightforward to perform the necessary conversions should the user wish to work in floating-point format.

Temperatures read from the device's registers are returned as °C\*16. (If the device resolution is set to less than 12 bits, the corresponding lower order bits are simply returned as zero.) Temperatures can alternately be read as °F\*10.

When writing the Hysteresis and Limit-Set registers, the value must be given as °C*2, which corresponds to the internal representation in these registers.

Bit masks for the control register are provided in the **MCP9800.h** file.     

"Arduino Library for Microchip MCP9800/1/2/3" by Jack Christensen is licensed under [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/).


## Examples
The following example sketch is included with the **MCP9800** library:

- **MCP9800_EX1:** Demonstrates basic reading of ambient temperature in Celsius and Fahrenheit, conversion to floating-point, changing device options via the Cofiguration register, and changing the Limit-Set and Hysteresis registers.  

- **MCP9800_RTC:** Displays the date and time from an MCP7941x RTC and the temperature from an MCP980x  

- **pico_ex1:** Like MCP9800_EX1, but for Raspberry Pi Pico with the sensor on the I2C-1 (Wire1) bus.  

## Enumeration

### MCP9800_REGS_t
##### Description
Symbolic names for the MCP9800 registers.
##### Values
- AMBIENT -- for the Ambient Temperature Register  
- HYSTERESIS -- for the Temperature Hysteresis Register  
- LIMITSET -- for the Temperature Limit-Set Register

## Constructor

### MCP9800(uint8_t LS_ADDR_BITS=0, tw=Wire)
##### Description
Instantiates an MCP9800 sensor object.
##### Syntax
```c++
// any of the following examples:
MCP9800 mySensor;           // address 0x48, primary I2C bus
MCP9800 mySensor(1);        // address 0x49, primary I2C bus
MCP9800 mySensor(Wire1);    // address 0x48, alternate I2C bus
MCP9800 mySensor(2, Wire1); // address 0x4A, alternate I2C bus
```
##### Parameters
**LS_ADDR_BITS:** An unsigned 8-bit integer *(uint8_t or byte)* representing the least-significant three bits of the I2C device address (i.e. a value between 0 and 7). Defaults to zero if omitted. (Note that some devices in the MCP9800 family allow the user to select the least significant three bits of the address, and some have a fixed address from the factory. See the datasheet for details.)

**tw** For microcontrollers with more than one I2C peripheral (e.g. Wire1, etc.), an optional reference to the *TwoWire* object for the I2C bus the sensor is connected to. Defaults to *Wire* if omitted.

## Methods
### begin()
##### Description
Initializes the library. Call this method once in the setup code.
##### Syntax
`mySensor.begin();`
##### Parameters
None.
##### Returns
None.
##### Example
```c++
MCP9800 mySensor;
mySensor.begin();
```
### readTempC16(MCP9800_REGS_t reg)
##### Description
Reads one of the three temperature registers from the sensor.
##### Syntax
`mySensor.readTempC16(MCP9800_REGS_t reg);`
##### Parameters
**reg:** The temperature register to read, AMBIENT, HYSTERESIS or LIMITSET *(MCP9800_REGS_t)*
##### Returns
Temperature as degrees Celsius times 16 *(int)*.
##### Example
```c++
MCP9800 mySensor;
mySensor.begin();
int c16 = mySensor.readTempC16(MCP9800::AMBIENT);
float C = c16 / 16.0;
```
### readTempF10(MCP9800_REGS_t reg)
##### Description
Reads one of the three temperature registers from the sensor.
##### Syntax
`mySensor.readTempF10(MCP9800_REGS_t reg);`
##### Parameters
**reg:** The temperature register to read, AMBIENT, HYSTERESIS or LIMITSET *(MCP9800_REGS_t)*
##### Returns
Temperature as degrees Fahrenheit times 10 *(int)*.
##### Example
```c++
MCP9800 mySensor;
mySensor.begin();
int f10 = mySensor.readTempF10(MCP9800::AMBIENT);
float F = f10 / 10.0;
```
### writeTempC2(MCP9800_REGS_t reg, int value)
##### Description
Sets the Temperature Hysteresis Register or the Temperature Limit-Set Register.
##### Syntax
`mySensor.writeTempC2(MCP9800_REGS_t reg, int value);`
##### Parameters
**reg:** The temperature register to write, HYSTERESIS or LIMITSET *(MCP9800_REGS_t)*. If given the AMBIENT temperature register, no action is taken (AMBIENT is a read-only register).  
**value:** The temperature value to set, in degrees Celsius times two *(int)*
##### Returns
None.
##### Example
```c++
MCP9800 mySensor;
mySensor.begin();
mySensor.writeTempC2(MCP9800::HYSTERESIS, 25 * 2);  //set hysteresis register to 25°C
mySensor.writeTempC2(MCP9800::LIMITSET, 100 * 2);   //set limit-set register to 100°C
```
### readConfig()
##### Description
Reads the value of the configuration register.
##### Syntax
`mySensor.readConfig();`
##### Parameters
None.
##### Returns
Configuration register value *(byte)*
##### Example
```c++
MCP9800 mySensor;
mySensor.begin();
byte config = mySensor.readConfig();
```
### writeConfig(uint8_t value)
##### Description
Writes a value to the configuration register.
##### Syntax
`mySensor.writeConfig(byte value);`
##### Parameters
**value:** The value to be written to the register. See the MCP9800.h file for symbolic definitions for the bits in the configuration register *(byte)*
##### Returns
None.
##### Example
```c++
MCP9800 mySensor;
mySensor.begin();
//set ADC resolution to 12 bits and the fault queue length to 6
byte config = MCP9800::ADC_RES_12BITS | MCP9800::FAULT_QUEUE_6;
mySensor.writeConfig(config);
```
