//--------------------------------------------------------------------------
// Switch
//
// An abstract class representing a generic RF switch.
//
// Harrison Statham
//

namespace Common
{

    // SPnT Switch State
    //
    // An enum representing the state that the switch is in.
    //

    enum SPnTSwitchState
    {
        BadState,
        RF1,
        RF2,
        RF3,
        RF4,
        RF5,
        RF6,
        RF7,
        RF8
    };

    enum OtherSwitchState
    {

    };

    struct SwitchState
    {
        enum SPnTSwitchState SPNTState;    
        enum OtherSwitchState OtherState;
    };


    class Switch
    {

    public:

        Switch() {}
        ~Switch() {}

        // Enable
        //  
        // *Most* RF switches have an enable pin to turn the device on/off.
        // 
        virtual void Enable() = 0;

        // Disable
        // 
        // Turn off the device.
        //
        virtual void Disable() = 0;


        // Read
        // 
        // Return the state of the system.
        // 
        virtual int Read() = 0;

        // Toggle
        //
        // Toggle the state of the switch.
        //
        virtual void Toggle() = 0;

    }; // end class Switch

} // end namespace Common