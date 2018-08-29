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

        SPI* _SPI;


        void InternalSetAttenuation(uint8_t AttenValue)
        {
            if(_SPI == (SPI*)0)
            {
                return;
            }

            // Ensure that LE is low.
            _LE = 0;

            // Lock up the SPI bus so we can use it exclusively.
            _SPI->lock();

            // format(number of bits per spi frame, spi mode)
            _SPI->format(8, 0);

            // Set the frequency of the bus to 1MHz.
            _SPI->frequency(1000000);

            // Write the byte out to the device.
            _SPI->write(AttenValue);

            // Wait for some specified time and then pulse the LE pin.
            // Read the datasheet for the minimum time needed.
            // 10 ns for LE setup. (We wait 20ns just because).
            wait(10e-9);
            _LE = 1;
            wait(20e-9);
            _LE = 0;
            
            // Unlock the bus to allow someone else to use it.
            _SPI->unlock();
        }


    public:

        PE43711Serial(PinName ParallelSerialPin, PinName LE, SPI* TheSPI)
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