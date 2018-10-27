//--------------------------------------------------------------------------
//
//
//

// Arduino Libraries
#include <Wire.h>


#include "RFSynth.hpp"

// Pinout of Arduino Nano

#define MASTER_INT_PIN  2
#define DEXP_INT_PIN    3
#define SLAVE_INT_PIN   4
#define SYNTH_LE_PIN    5
#define SP5T_V1_PIN     6
#define SP5T_V2_PIN     7
#define SP5T_V3_PIN     8
#define DEXP_RESET_PIN  9
#define DEXP_CS_PIN     10
#define EEPROM_CS_PIN   A0
#define DAC_LOAD_PIN    A1
#define DAC_CS_PIN      A2
#define DAC_CLR_PIN     A3


// Master Commands
//
// A list of all the commands that the master can send to the slave.
// If the command is not one of these then we should ignore the command.
//
enum eMasterCommands
{
    SetFrequency,
    SetPower,
    SetVSGMode,
    MuteRF,
};



void setup()
{
    // Set the master interrupt pin as an input with a pullup.
    pinMode(MASTER_INT_PIN, INPUT_PULLUP);

    // Set the digital expander interrupt as an input.
    pinMode(DEXP_INT_PIN, INPUT);

    // Similar to the master interrupt pin, attach the interrupt handler to the pin.
    attachInterrupt(digitalPinToInterrupt(DEXP_INT_PIN), DigitalExpanderInterruptHandler, CHANGE);

    // Set the remainder of the pins as input/output type pins.
    pinMode(SLAVE_INT_PIN, OUTPUT);
    pinMode(SYNTH_LE_PIN, OUTPUT);

    pinMode(SP5T_V1_PIN, OUTPUT);
    pinMode(SP5T_V2_PIN, OUTPUT);
    pinMode(SP5T_V3_PIN, OUTPUT);

    pinMode(DEXP_RESET_PIN, OUTPUT);
    pinMode(DEXP_CS_PIN, OUTPUT);

    pinMode(EEPROM_CS_PIN, OUTPUT);

    pinMode(DAC_LOAD_PIN, OUTPUT);
    pinMode(DAC_CLR_PIN, OUTPUT);
    pinMode(DAC_CS_PIN, OUTPUT);


    // Setup and libraries that we might need.
    Wire.begin(0x1); // Supply address for the slave devices

    // Attach the interrupt handler to the master int pin.
    // When the master changes the I2C bus, the pin state will change and trigger
    // the interrupt handler that we have provided here.
    Wire.onReceive(MasterInterruptHandler);


    // Try and read from the EEPROM to get the latest settings.
    
}


void loop()
{
    // Do something here.
}


// Interrupt handlers
//
// When the master interrupt goes high, it means that the master device
// is trying to send a new command to this device. We should stop what
// we are doing and receive data over I2C.

void MasterInterruptHandler()
{
    
    // Read the information from the master device over I2C.
    // The wire library uses a 32 byte buffer so thats all we have.



}


void DigitalExpanderInterruptHandler()
{

}
