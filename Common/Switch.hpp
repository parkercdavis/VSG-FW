//--------------------------------------------------------------------------
// Switch
//
// An abstract class representing a generic RF switch.
//
// Harrison Statham
//

namespace Common
{
    class Switch
    {

    public:

        Switch();

        // Enable
        //  
        // *Most* RF switches have an enable pin to turn the device on/off.
        // 
        virtual void Enable();


        // Disable
        // 
        // Turn off the device.
        //
        virtual void Disable();

        // Toggle
        //
        // Toggle the state of the switch.
        //
        virtual void Toggle();

    }; // end class Switch

} // end namespace Common