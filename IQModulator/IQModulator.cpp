//--------------------------------------------------------------------------
//
//
//
//
//

#include "IQModulator.hpp"

namespace IQModulator
{
    void IQModulator()
    {
        PinName LE = p20;
        PinName PS = p21;
        PinName MOSI = p22;
        PinName SCLK = p23;

        SPI TheSPI(MOSI, NC,  SCLK, NC);

        Common::PE43711Serial IQAtten(PS, LE, &TheSPI);

        // The cast is necessary for the compiler to determine which SetAttenuation method
        // we wish to call.... :/
        IQAtten.SetAttenuation((float) 22.25);
    }
}