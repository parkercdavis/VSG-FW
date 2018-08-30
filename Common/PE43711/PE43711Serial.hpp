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


        //
        // A pointer to the SPI bus that we want to use to control
        // the attenuator.
        //
        // Note, we prefer the pointer here because multiple devices can happily
        // share the same SPI bus.
        // 
        // Watch out for null pointers though...
        SPI* _SPI;


        // Internal Set Attenuation
        //
        // This is the implementation of the virtual method in the parent class.
        // Since this class is for the serial case, then we call the SPI bus
        // to transmit our data to the attenuator.
        //
        void InternalSetAttenuation(uint8_t AttenValue)
        {
            // Handle null pointers *before* we try to talk.
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