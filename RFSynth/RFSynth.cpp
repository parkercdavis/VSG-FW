//--------------------------------------------------------------------------
//
//
//

#include "RFSynth.hpp"

namespace RFVSG
{
    namespace RFSynth
    {
                
        //-------------------------------------------
        // Define the pin out of the device

        // CW RF Amplifier
        DigitalOut CWAmpEnable();
        DigitalOut CWAmpSenseEnable();
        AnalogIn   CWAmpISense();
        
        // CW Attenuator
        DigitalOut CWAttenLatchEnable();
        DigitalOut CWAttenPS();

        // CW SP5T
        DigitalOut CWSP5TV1();
        DigitalOut CWSP5TV2();
        DigitalOut CWSP5TV3();
        

        // LO_P Attenuator
        DigitalOut LOPAttenLatchEnable();
        DigitalOut LOPAttenPS();

        // LO_N Attenuator
        DigitalOut LONAttenLatchEnable();
        DigitalOut LONAttenPS();


        // LO Differential Amplifier
        DigitalOut LODiffAmpEnable();
        DigitalOut LODiffAmpSenseEnable();
        AnalogIn   LODiffAmpISense();

        
        // Synth
        DigitalOut SynthLatchEnable();
        DigitalOut SynthChipEnable();
        DigitalOut SynthRFOutEnable();
        DigitalIn  SynthMux();
        DigitalIn  SynthLockDetect();


        // Interrupts
        InterruptIn MasterInterrupt();
        DigitalOut  SlaveInterrupt();

        I2CSlave i2c();

        // SPI
        // SPI(mosi, miso, sclk);
        SPI spi();

        
        // State variables
        //

        // Command from the master.
        uint32_t MasterCommand = 0;

        // The current going to the diff amp.
        uint32_t DiffAmpISense = 0;

        // The current going to the rf amplifier for the CW.
        uint32_t RFAmpISense = 0;

        // Is VSG Mode (i.e. CW disabled)
        bool IsVSGMode = false;


        int RFSynth()
        {
            // Setup SPI if needed.
            spi.frequency(1000000);
            
            // Setup the mbed as a I2C slave.
            i2c.address();


            // Setup the devices
            //
            // We assume that we are in VSG mode to start
            // and then we will let the master tell us otherwise.

            CWAmpEnable = 0;
            CWAmpSenseEnable = 0;
            CWAttenPS = 0;          // Check datasheet.
            CWSP5TV1 = 0;
            CWSP5TV2 = 0;
            CWSP5TV3 = 0;

            LOPAttenPS = 0;
            LONAttenPS = 0;
            LODiffAmpEnable = 1;
            LODiffAmpSenseEnable = 1;

            SynthChipEnable = 1;
            SynthRFOutEnable = 1;
            
            
            // Read the LUT to see what the attenuation setting should be.
            // Write to the attenuators.
            
            // Read from the LUT to see what the power setting should be
            // for the MAX2871.
            // Write the power and frequency settings to the Max2871.



            // Set up the interrupt from the master micro.
            //
            MasterInterrupt.rise(&MasterCommunicating);


            // Tell the master that we are present and ready to receive commands.
            // At this point, the master should see the interrupt on its side,
            // and respond with a basic I2C command telling the device that the
            // master is ready to go.
            //
            // We leave this pin high unless something bad happens telling the
            // master that something is wrong. The master can then choose what
            // to do such as issue a reset to the device.
            SlaveInterrupt = 1;


            while(true)
            {
                // Do something forever.

                if(IsVSGMode)
                {
                    // Read from the Diff amp current sense.
                }
                else
                {
                    // Read from the RF amp current sense.
                }

                wait(0.01);

            } // end while(true)


            // If we somehow make it here, then we let the master device know
            // and it can decide what to do.

            SlaveInterrupt = 0;


            return 0;

        } // end RFSynth()


        // Listen For Command From Master
        //
        // This function is called when the master signals an interrupt
        // on the correct pin.
        //
        void MasterCommunicating()
        {
            
            int CommandType = i2c.receive();

            switch(CommandType)
            {
                // The master is writing to all slave devices.
                // We can use this for general commands like shutdown etc...
                // Commands that ALL slave devices will share.
                case I2CSlave::WriteGeneral:

                    // Do something general here...

                break;

                // The master is expecting us to write something back to it!
                case I2CSlave::ReadAddressed:

                    // Tell the master who are, the firmware installed, the serial number,
                    // the ADC current sense values, and any other relevant information.

                break;

                
                // The master is writing to us!
                case I2CSlave::WriteAddressed:

                    // Read from the master and figure out what we need to do.
                    uint32_t Command = i2c.read();

                    switch(Command)
                    {
                        case eMasterCommands::SetVSGMode:

                        break;

                        case eMasterCommands::SetFrequency:

                        break;

                        case eMasterCommands::SetPower:

                        break;

                        case eMasterCommands::MuteRF:
                        
                        break;
                    }

                break;
            }
            
        } // end MasterCommunicating


        void ChangeMode()
        {
            if(IsVSGMode)
            {
                LOPAttenPS = 0;
                LONAttenPS = 0;
                LODiffAmpEnable = 1;
                LODiffAmpSenseEnable = 1;
            }
            else
            {
                CWAmpEnable = 1;
                CWAmpSenseEnable = 1;
                CWAttenPS = 0; // Check datasheet.
                CWSP5TV1 = 0;
                CWSP5TV2 = 0;
                CWSP5TV3 = 0;
            }

            SynthChipEnable = 1;
            SynthRFOutEnable = 1;
        }

    } // end namespace RFSynth

} // end namespace RFVSG