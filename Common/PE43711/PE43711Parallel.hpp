//--------------------------------------------------------------------------
//
//
//
//
//

#ifndef PE43711Parallel_HPP
#define PE43711Parallel_HPP

#include "PE43711.hpp"

namespace Common
{

    class PE43711Parallel : public PE43711
    {
    private:

        DigitalOut _D0;
        DigitalOut _D1;
        DigitalOut _D2;
        DigitalOut _D3;
        DigitalOut _D4;
        DigitalOut _D5;
        DigitalOut _D6;
        DigitalOut _D7;
    
        //
        //
        void InternalSetAttenuation(uint8_t AttenValue)
        {

        }

        

    public:

        

    }; // end class PE43711Parallel

} // end namespace Common

#endif