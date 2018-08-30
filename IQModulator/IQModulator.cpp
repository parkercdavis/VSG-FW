//--------------------------------------------------------------------------
//
//
//
//
//

#include "IQModulator.hpp"

namespace IQModulator
{
    //-------------------------------------------------------------
    // IQ Modulator Settings
    //

    #define ISW_RF1 p20
    #define ISW_RF2 p21
    #define ISW_EN  p22

    #define QSW_RF1 p20
    #define QSW_RF2 p21
    #define QSW_EN  p22

    #define LE   p20;
    #define PS   p21;
    #define MOSI p22;
    #define SCLK p23;
    

    //-------------------------------------------------------------
    // IQ Modulator Globals
    //

    float RFPower = 0.0; // Assume units of dBm.

    // Create the SPI device here.
    SPI TheSPI(MOSI, NC,  SCLK, NC);

    // The I switch switches between internal or external signals.
    Common::HMC349 ISwitch(ISW_RF1, ISW_RF2, true, ISW_EN, true);

    // The Q switch switches between internal or external signals.
    Common::HMC349 QSwitch(QSW_RF1, QSW_RF2, true, QSW_EN, true);

    

    // Create an instance of the attenuator and hand off a pointer to the SPI bus.
    Common::PE43711Serial IQAtten(PS, LE, &TheSPI);


    //-------------------------------------------------------------
    // Interrupts (External or Internal)
    //
    // External interrupts = interrupts from the main controller
    // that is telling us what to do with the output.
    //
    // Internal interrupts = interrupts from the board itself
    //
    // Commands
    // 1. Change the RF power level.
    // 2. Change the I/Q switch state.
    // 3. Change the output RF switch.
    //

    void ReceiveCommandFromController()
    {
        
    }


    void IQModulator()
    {
        
        //-------------------------------------------------------------
        // Leveling Loop
        //
        //

        


        // Measure the RF power according to the power meter.
        // Need to measure the power using the built in ADC.


        // Figure out how far off we are from the ideal power and
        // adjust the attenuator level to get the power output we want.
        //
        // We want to use a PID loop to do this correctly.
        // (Alternatively, we can try using an analog loop and see if it
        // will control the power correctly.)

        
        

        
    }
}