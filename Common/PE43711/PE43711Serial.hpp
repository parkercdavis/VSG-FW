//--------------------------------------------------------------------------
//
//
//
//
//

#ifndef PE43711Serial_HPP
#define PE43711Serial_HPP

#include "PE43711.hpp"

namespace Common
{

    class PE43711Serial : public PE43711
    {
    private:

        //DigitalOut _CLK;
        //DigitalOut _SI;
        
        // 
        SPI _SPI;


        void InternalSetAttenuation(uint8_t AttenValue)
        {

        }


    public:

        PE43711Serial(PinName ParallelSerialPin, PinName LE, SPI& TheSPI)
        {
            _PS = DigitalOut(ParallelSerialPin);
            _LE = DigitalOut(LE);

            // We explicitly defined this device as serial thus
            // the _PS line is always high.
            _PS = 1;

            // Hold on to a reference to the SPI object.
            _SPI = TheSPI;
        }

        ~PE43711Serial()
        {
            
        }



        

    }; // end class PE43711Serial

} // end namespace Common

#endif