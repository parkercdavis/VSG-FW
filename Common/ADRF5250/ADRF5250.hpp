

#ifndef ADRF5250_HPP
#define ADRF5250_HPP

#include "stdint.h"

class ADRF5250
{
    private:

    uint8_t V1_Pin;
    uint8_t V2_Pin;
    uint8_t V3_Pin;

    uint8_t State = 0;

    public:

    ADRF5250(uint8_t VControl1, uint8_t VControl2, uint8_t VControl3)
    {
        V1_Pin = VControl1;
        V2_Pin = VControl2;
        V3_Pin = VControl3;

        digitalWrite(V1_Pin, LOW);
        digitalWrite(V2_Pin, LOW);
        digitalWrite(V3_Pin, LOW);
    }

    ADRF5250& operator=(const uint8_t Index)
    {
        if(Index > 5) Index = 0;

        if(Index != State)
        {
            switch(Index)
            {
                // Connect RF common to RF1.
                case 1:

                    digitalWrite(V1_Pin, HIGH);
                    digitalWrite(V2_Pin, LOW);
                    digitalWrite(V3_Pin, LOW);

                break;

                // Connect RF common to RF2.
                case 2:

                    digitalWrite(V1_Pin, LOW);
                    digitalWrite(V2_Pin, HIGH);
                    digitalWrite(V3_Pin, LOW);

                break;

                // Connect RF common to RF3.
                case 3:

                    digitalWrite(V1_Pin, HIGH);
                    digitalWrite(V2_Pin, HIGH);
                    digitalWrite(V3_Pin, LOW);
                break;

                // Connect RF common to RF4.
                case 4:
                    digitalWrite(V1_Pin, LOW);
                    digitalWrite(V2_Pin, LOW);
                    digitalWrite(V3_Pin, HIGH);
                break;

                // Connect RF common to RF5.
                case 5:
                    digitalWrite(V1_Pin, HIGH);
                    digitalWrite(V2_Pin, LOW);
                    digitalWrite(V3_Pin, HIGH);
                break;


                // Turn off all switches.
                default:
                case 0:
                    digitalWrite(V1_Pin, LOW);
                    digitalWrite(V2_Pin, LOW);
                    digitalWrite(V3_Pin, LOW);

                break;
            } // end switch statement

            State = Index;
        }

        return this;
    }


};


#endif