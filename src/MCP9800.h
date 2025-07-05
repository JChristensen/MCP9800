// Arduino MCP9800 Library
// https://github.com/JChristensen/MCP9800
// Copyright (C) 2014-2025 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Arduino Library for Microchip MCP9800/1/2/3 2-Wire High-Accuracy
// Temperature Sensors

#pragma once
#include <Arduino.h>
#include <Wire.h>

class MCP9800
{
    public:
        static constexpr uint8_t BASE_ADDR {0x48};  // device i2c address
        static constexpr uint8_t CONFIG_REG {1};    // register addresses
        enum MCP9800_REGS_t {AMBIENT=0, HYSTERESIS=2, LIMITSET=3};

        // bit definitions for config register
        static constexpr uint8_t
            ONE_SHOT {0x80},
            ADC_RES_9BITS {0x00},
            ADC_RES_10BITS {0x20},
            ADC_RES_11BITS {0x40},
            ADC_RES_12BITS {0x60},
            FAULT_QUEUE_1 {0x00},
            FAULT_QUEUE_2 {0x08},
            FAULT_QUEUE_4 {0x10},
            FAULT_QUEUE_6 {0x18},
            ALERT_POLARITY_HIGH {0x04},
            INTERRUPT_MODE {0x02},
            SHUTDOWN {0x01};

        // Constructor: Instantiates a temperature sensor object given the
        // least three significant bits (A2:0) of its I2C address (0-7),
        // and a reference to the I2C peripheral to use. The LS address bits
        // default to zero and the I2C peripheral defaults to Wire.
        MCP9800(uint8_t LS_ADDR_BITS=0, TwoWire& tw=Wire)
            : m_devAddr{static_cast<uint8_t>(BASE_ADDR + (LS_ADDR_BITS & 0x07))}, wire{tw} {}
        MCP9800(TwoWire& tw) : m_devAddr{BASE_ADDR}, wire{tw} {}

        void begin();
        int readTempC16(MCP9800_REGS_t reg);
        int readTempF10(MCP9800_REGS_t reg);
        void writeTempC2(MCP9800_REGS_t reg, const int value);
        uint8_t readConfig();
        void writeConfig(const uint8_t value);

    private:
        uint8_t m_devAddr;
        TwoWire& wire;      // reference to Wire, Wire1, etc.
};
