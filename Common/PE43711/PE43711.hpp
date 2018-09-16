//--------------------------------------------------------------------------
//
//
//
//
//

#ifndef PE43711_HPP
#define PE43711_HPP

#include "mbed.h"
#include <math.h>
#include <functional>

namespace Common
{
    class PE43711
    {
    private:

        // AttenuationByte
        //
        //
        uint8_t AttenuationByte;


    private:

        // Parallel/Serial Select Line
        // 
        //
        DigitalOut& PS;


        // Latch Enable
        //
        // Equivalent to the CS pin.
        //
        DigitalOut& LE;


        // Digital Pins
        // 
        DigitalOut& D0;
        DigitalOut& D1; 
        DigitalOut& D2; 
        DigitalOut& D3; 
        DigitalOut& D4; 
        DigitalOut& D5; 
        DigitalOut& D6; 
        DigitalOut& D7;


        // Write Function
        //
        // An anonymous function that allows the programmer
        // to abstract away the SPI interface from the PE43711 firmware.
        // 
        std::function<void()> WriteFunction;


    public:
        
        #pragma region Static Methods

        // Byte To Float
        //
        // Convert a byte to a floating point number.
        //
        static float ByteToFloat(uint8_t TheByte)
        {
            float TheValue = 0.0;

            TheValue += (TheByte >> 0 & 1) ? 0.25 : 0.0;
            TheValue += (TheByte >> 1 & 1) ? 0.5 : 0.0;
            TheValue += (TheByte >> 2 & 1) ? 1.0 : 0.0;
            TheValue += (TheByte >> 3 & 1) ? 2.0 : 0.0;
            TheValue += (TheByte >> 4 & 1) ? 4.0 : 0.0;
            TheValue += (TheByte >> 5 & 1) ? 8.0 : 0.0;
            TheValue += (TheByte >> 6 & 1) ? 16.0 : 0.0;

            return TheValue;
        }


        // Float to Byte
        // 
        // Convert a float to a byte.
        // 
        // TODO: Test this code thoroughly! Crazy, sleep deprived, Harrison came up with
        // this algorithm.
        //
        static uint8_t FloatToByte(float TheFloat)
        {
            float Values[7] = {0.25, 0.5, 1.0, 2.0, 4.0, 8.0, 16.0};
            
            uint8_t TheValue = 0;
                    
            for(int i = 6; i >= 0; i--)
            {
                
                if(TheFloat < Values[i])
                {
                    // If the value is less than the test value, the modulus will return TheFloat.
                    // We bypass this case since our resolution is 0.25.
                    continue;
                }
                else if((fmod(TheFloat, Values[i]) > 0.0) || TheFloat == Values[i])
                {
                    // If the value == TheFloat (the mod = 0) but we need to handle this case since it should
                    // set the current bit.

                    // If the modulus is greater than 0, then we can "fit" the number in "Values[i]" into TheFloat.
                    
                    // Set the bit in TheValue corresponding to the current index i.
                    TheValue |= (1 << i);

                    // Subtract off the number "Values[i]" and continue the routine.
                    TheFloat -= Values[i];
                }
            }
            
            return TheValue;
        }

        #pragma endregion


        #pragma region Constructors

        PE43711(DigitalOut& PSPin, DigitalOut& LEPin, std::function<void()> WriteFn)
        {
            PS = PSPin;
            LE = LEPin;
            WriteFunction = WriteFn;
        }

        PE43711(DigitalOut& PSPin, 
                DigitalOut& LEPin, 
                DigitalOut& D0Pin, 
                DigitalOut& D1Pin, 
                DigitalOut& D2Pin, 
                DigitalOut& D3Pin, 
                DigitalOut& D4Pin, 
                DigitalOut& D5Pin, 
                DigitalOut& D6Pin, 
                DigitalOut& D7Pin), : 
                PS(PSPin), LE(LEPin), 
                D0(D0Pin), D1(D1Pin), 
                D2(D2Pin), D3(D3Pin), 
                D4(D4Pin), D5(D5Pin), 
                D6(D6Pin), D7(D7Pin)
        {

        }
        
        #pragma endregion
        


    }; // end class PE43711

}

#endif