//--------------------------------------------------------------------------
//
//
//

// Arduino Libraries
#include <Wire.h>


#include <../Common/ADRF5250/ADRF5250>

//----------------------------------------------------------------------
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


//----------------------------------------------------------------------
// Master Commands
//
// A list of all the commands that the master can send to the slave.
// If the command is not one of these then we should ignore the command.
//
enum eMasterCommands
{
    //----------------------------------------------------------------------
    // Misc commands
    
    // The VSG can be in CW (just a sine wave) mode OR vector mod mode.
    // In CW mode, the output power is fixed at a given frequency, and the
    // LO portions of the synthesizer are all stutdown.
    SetVSGToCWMode,

    SetVSGToVectorMode,

    // Turn off the synth for power savings.
    ShutdownSynth,

    //----------------------------------------------------------------------
    // CW Commands

    // Set the filter bank filter for the CW output.
    SetCWFilter,

    // Set the CW output power using the attenuator.
    SetCWPower,

    //----------------------------------------------------------------------
    // LO commands

    // Set the LO power to a given power level using the attenuator.
    SetLOPower,

    //----------------------------------------------------------------------
    // Synthesizer commands

    // Set the frequency output from the synth IC. This effects both CW and
    // LO outputs.
    SetSynthFrequency,

    // Set the output power coming from the synth IC. There are only 4 power
    // levels that can be chosen from.
    SetSynthPower,

    // Mute the RF outputs from the synth IC.
    SynthMuteRF,
};


//----------------------------------------------------------------------
// Global variables
//
//

// I2C data received from the master.
volatile byte I2CPacket[32] = {0};

// I2C event happened and we need to do something.
volatile bool I2CInterruptOccured = false;

// Initialize the filter bank switch.
// Digital circuitry onboard takes care of the other filter bank IC.
ADRF5250 LOFilterBankSwitch(SP5T_V1_PIN, SP5T_V2_PIN, SP5T_V3_PIN);


//----------------------------------------------------------------------
// Setup
//
// The setup function runs once and setup... No way!
//

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


//----------------------------------------------------------------------
//
// Loop
//
// The loop runs continuously.

void loop()
{
    // If an event happened then we need to process the event!
    if(I2CInterruptOccured)
    {
        // Set the flag back to false so we only handle it once.
        I2CInterruptOccured = false;

        // Check the command byte first to see what happened.
        switch(I2CPacket[0])
        {
            case eMasterCommands::SetVSGToCWMode:

                // Turn off the LO circuitry.

            break;

            case eMasterCommands::SetVSGToVectorMode:

            break;
            
            case eMasterCommands::ShutdownSynth:

            break;

            case eMasterCommands::SetCWFilter:

            break;

            case eMasterCommands::SetCWPower:

            break;

            case eMasterCommands::SetLOPower:

            break;

            case eMasterCommands::SetSynthFrequency:

            break;

            case eMasterCommands::SetSynthPower:

            break;

            case eMasterCommands::SynthMuteRF:

            break;
        }

    }

    // Just hang out and do nothing if no event has happened.
    delay(100);
}


// Interrupt handlers
//
// When the master interrupt goes high, it means that the master device
// is trying to send a new command to this device. We should stop what
// we are doing and receive data over I2C.

void MasterInterruptHandler(int NumberOfBytes)
{
    // Read the information from the master device over I2C.
    // The wire library uses a 32 byte buffer so thats all we have.

    while(1 < Wire.available())
    {
        I2CPacket[i] = Wire.read();
    }

    int x = Wire.read(); // Read the last byte out.

    I2CInterruptOccured = true;
}


void DigitalExpanderInterruptHandler()
{

}
