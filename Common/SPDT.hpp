//--------------------------------------------------------------------------
//
//
//
//
//

#include "mbed.h"

#include "Switch.hpp"


namespace Common
{

    class SPDT : public Switch
    {
    private:
        DigitalOut _RF1;
        DigitalOut _RF2;
        DigitalOut _Enable;

    public:

        ///
        // SPDT
        //
        //
        SPDT(PinName RF1, PinName RF2, bool RF1IsDefault, PinName Enable, bool IsEnabledByDefault) : _RF1(RF1), _RF2(RF2), _Enable(Enable)
        {
            if(IsEnabledByDefault)
            {
                _Enable = 1;
            }
            else
            {
                _Enable = 0;
            }

            if(RF1IsDefault)
            {
                _RF1 = 1;
                _RF2 = 0;
            }
            else
            {
                _RF1 = 0;
                _RF2 = 1;
            }
        }

        ///
        // Enable
        //

        void Enable()
        {
            _Enable = 1;
        }

        ///
        // Disable
        //
        void Disable()
        {
            _Enable = 0;
        }

        // Read
        //
        //
        SPnTSwitchState Read()
        {
            return (_RF1) ? RF1 : RF2;
        }

        ///
        // Toggle
        //

        void Toggle()
        {
            _RF1 = !_RF1;
            _RF2 = !_RF1;
        }
    };
}