//--------------------------------------------------------------------------
// RF Synth
//
// This file defines the API that python will interface with.
// Python should know nothing of the internal hardware only the commands
// that it has access to.
//
// Harrison Statham
//

#ifndef RFSYNTH_HPP
#define RFSYNTH_HPP

#include "mbed.h"
#include "stdint.h"

namespace RFVSG
{
    namespace RFSynth
    {
        // Master Commands
        //
        // A list of all the commands that the master can send to the slave.
        // If the command is not one of these then we should ignore the command.
        //
        enum eMasterCommands
        {
            SetFrequency,
            SetPower,
            SetVSGMode,
            MuteRF,
        };

        int RFSynth();
    }
}


#endif