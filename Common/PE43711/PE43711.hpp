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

namespace Common
{
    class PE43711
    {
    private:

        // AttenuationByte
        //
        //
        uint8_t _AttenuationByte;


    protected:

        // Parallel/Serial Select Line
        //
        DigitalOut _PS;


        // Latch Enable
        //
        //
        DigitalOut _LE;


    public:
        
        PE43711();
        virtual ~PE43711();

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


        #pragma region Virtual Methods

        // SetAttenuation
        // 
        // Set the attenuation using either serial/parallel code. 
        // We let the inheriting class define this method.
        //
        virtual void InternalSetAttenuation(uint8_t AttenValue) = 0;

        #pragma endregion


        #pragma region Methods

        // SetAttenuation
        // 
        // Set the amount of attenuation.
        //
        void SetAttenuation(float AttenValue)
        {
            _AttenuationByte = PE43711::FloatToByte(AttenValue);

            InternalSetAttenuation(_AttenuationByte);
        }

        void SetAttenuation(uint8_t AttenValue)
        {
            InternalSetAttenuation(_AttenuationByte);
        }


        // Get Attenuation
        //
        // Return the value of the attenuation as a floating point number.
        //
        float GetAttenuation()
        {
            return PE43711::ByteToFloat(_AttenuationByte);
        }

        #pragma endregion


        #pragma region Operator Overloads

        // Assign operator
        //
        // For float values, we want to set the value of attenuation.
        //
        PE43711& operator =(float TheFloat)
        {
            SetAttenuation(PE43711::FloatToByte(TheFloat));

            return *this;
        }


        PE43711& operator =(uint8_t TheByte)
        {
            SetAttenuation(TheByte);

            return *this;
        }

        inline operator float ()
        {
            return PE43711::ByteToFloat(_AttenuationByte);
        }

        inline operator uint8_t ()
        {
            return _AttenuationByte;
        }

        #pragma endregion


    }; // end class PE43711

}

#endif