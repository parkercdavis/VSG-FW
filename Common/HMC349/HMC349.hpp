//--------------------------------------------------------------------------
//
//
//
//
//

#include "mbed.h"
#include "SPDT.hpp"

namespace Common
{
    class HMC349 : public SPDT 
    {
    public:
        // Common::HMC349 ISwitch(ISW_RF1, ISW_RF2, true, ISW_EN, true);
        HMC349(PinName RF1, PinName RF2, bool IsRF1Default, PinName En, bool IsEnabled) 
        : SPDT(RF1, RF2, IsRF1Default, En, IsEnabled){}
    };
}