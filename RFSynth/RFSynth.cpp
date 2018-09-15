//--------------------------------------------------------------------------
//
//
//

#include "RFSynth.hpp"

namespace RFVSG
{
    namespace RFSynth
    {
        int RFSynth()
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

            // CW SP5T
            DigitalOut CWSP5TV1();
            DigitalOut CWSP5TV2();
            DigitalOut CWSP5TV3();

            // Synth
            DigitalOut SynthLatchEnable();
            DigitalOut SynthChipEnable();
            DigitalOut SynthRFOutEnable();
            DigitalIn  SynthMux();
            DigitalIn  SynthLockDetect();


            // SPI
            SPI mspi();


            //-------------------------------------------
            // Setup the devices


            while(true)
            {
                // Do something forever.
            }

            return 0;
        } // end RFSynth()

    } // end namespace RFSynth

} // end namespace RFVSG