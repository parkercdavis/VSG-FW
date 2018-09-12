//------------------------------------------------------------------------------------------
//
//
//

#ifndef MAX2871_HPP
#define MAX2871_HPP

#include "stdint.h"

#include "Macros.h"


namespace RFVSG
{
    namespace Common
    {
        
        namespace MAX2871
        {
            enum LockDetectSpeed
            {
                Slow,
                Fast
            };

            enum SigmaDeltaNoiseMode
            {
                LowNoise,
                Reserved,
                LowSpur1,
                LowSpur2
            };

            enum MuxConfiguration
            {
                TriState,
                PullUp,
                PullDown,
                RDivOutput,
                NDivOutputOverTwo,
                AnalogLockDetect,
                DigitalLockDetect,
                SyncInput,
                Reserved1,
                Reserved2,
                Reserved3,
                Reserved4,
                ReadRegSix
                // Higher order are reserved.
            };

            enum LockDetectFunction
            {
                FracNLockDetect,
                IntNLockDetect
            };

            enum LockDetectPrecision
            {
                TenNS,
                SixNS
            };

            enum PhaseDetectorPolarity
            {
                Negative,
                Positive
            };

            enum ShutdownMode
            {
                Normal,
                Shutdown
            };

            enum CounterResetMode
            {
                Normal,
                RNReset
            };

            enum ChargePumpLinearity
            {
                Disabled,
                Linearity10Percent,
                Linearity20Percent,
                Linearity30Percent
            };

            enum ChargePumpTestMode
            {
                Normal,
                LongReset,
                ForceChargePumpIntoSource,
                ForceChargePumpIntoSink
            };
        }
        


        //----------------------------------------------------------------------------------
        //
        //
        class Max2871
        {
            private:

                //--------------------------------------------------------------------------
                // Register 0
                //
                // BIT      BIT ID  NAME                    DEFINITION
                // 31       INT     Int-N or Frac-N Mode    0 = Enables the fractional-N mode 
                //                                          1 = Enables the integer-N mode 
                // * The LDF bit must also be set to the appropriate mode.
                //
                // 30:15    N[15:0]     Int Division Val    Sets integer part (N-divider) of the 
                //                                          feedback divider factor. All integer values 
                //                                          from 16 to 65,535 are allowed for integer mode. 
                //                                          Integer values from 0 to 15 are not allowed. 
                //                                          Integer values from 19 to 4091 are allowed for 
                //                                          fractional mode.
                //
                // 14:3     FRAC[11:0]  Fractional Div Val  Sets fractional value:  000000000000 = 0 
                //                                                                  000000000001 = 1 
                //                                                                  111111111110 = 4094 
                //                                                                  111111111111 = 4095
                // * See F0I bit description
                //
                // 2:0      ADDR[2:0]   Address Bits        Register address bits, 000
                //
                //
                volatile uint32_t _R0 = 0x007D0000;

                
                //--------------------------------------------------------------------------
                // Register 1
                //                
                // BIT      BIT ID      NAME                DEFINITION
                //-----------------------------------------------------------------
                // 31       Reserved    Reserved            Reserved. Program to 0.
                //
                // 30:29    CPL[1:0]    CP Linearity        Sets CP linearity mode.  
                //                                          00 = Disables the CP linearity mode (integer-N mode) 
                //                                          01 = CP linearity 10% mode (frac-N mode)
                //                                          10 = CP linearity 20% mode (frac-N mode)
                //                                          11 = CP linearity 30% mode (frac-N mode)
                //
                // 28:27    CPT[1:0]    Charge Pump Test    Sets charge-pump test modes. 
                //                                          00 = Normal mode
                //                                          01 = Long Reset mode
                //                                          10 = Force CP into source mode 
                //                                          11 = Force CP into sink mode
                //
                // 26:15    P[11:0]     Phase Value         Sets phase value. See the Phase Adjustment section. 
                //                                          000000000000 = 0
                //                                          000000000001 = 1 (recommended)
                //                                          -----
                //                                          111111111111 = 4095
                //
                // 14:3     M[11:0]     Modulus Value (M)   Fractional modulus value used to program fVCO. 
                //                                          See the Int, Frac, Mod and R Counter Relationship section. 
                //                                          Double buffered by register 0. 
                //                                          000000000000 = Not Valid
                //                                          000000000001 = Not Valid
                //                                          000000000010 = 2 
                //                                          -----
                //                                          111111111111 = 4095
                //
                // 2:0      ADDR[2:0]   Address Bits        Control Register address bits, 001
                
                volatile uint32_t _R1 = 0x2000FFF9;


                //--------------------------------------------------------------------------
                // Register 2
                //
                // BIT      BIT ID      NAME                DEFINITION
                //-----------------------------------------------------------------
                // 31       LDS         Lock-Detect Speed   Lock-detect speed adjustment. 
                //                                          0 = fPFD ≤ 32MHz
                //                                          1 = fPFD > 32MHz
                //

                

                void SetLockDetectSpeed(enum MAX2871::LockDetectSpeed Speed)
                {
                    if(Speed == MAX2871::LockDetectSpeed::Slow)
                    {
                        CLEAR_BIT(_R2, 31)
                    }
                    else
                    {
                        SET_BIT(_R2, 31)
                    }
                }

                enum MAX2871::LockDetectSpeed GetLockDetectSpeed()
                {
                    return (MAX2871::LockDetectSpeed ((_R2 >> 31) & 0x1)); // Can this cast be done???
                }

                // 30:29    SDN[1:0]    Frac-N Sigma Delta  Sets noise mode (see the Low-Spur Mode section.) 
                //                      Noise Mode          00 = Low-noise mode
                //                                          01 = Reserved
                //                                          10 = Low-spur mode 1
                //                                          11 = Low-spur mode 2
                //

                
                void SetSigmaDeltaNoiseMode(enum MAX2871::SigmaDeltaNoiseMode NoiseMode)
                {
                    switch(NoiseMode)
                    {
                        case MAX2871::SigmaDeltaNoiseMode::LowNoise:

                            CLEAR_BITS(_R2, 29, 30)

                        break;

                        case MAX2871::SigmaDeltaNoiseMode::Reserved:

                        break;

                        case MAX2871::SigmaDeltaNoiseMode::LowSpur1:

                            SET_BIT(_R2, 30)
                            CLEAR_BIT(_R2, 29)

                        break;

                        case MAX2871::SigmaDeltaNoiseMode::LowSpur2:

                            SET_BITS(_R1, 29, 30)

                        break;
                    }
                }

                enum MAX2871::SigmaDeltaNoiseMode GetSigmaDeltaNoiseMode()
                {
                    enum MAX2871::SigmaDeltaNoiseMode Mode;

                    uint32_t TestModeBits = (_R1 >> 27) & 0x11;
                    
                    switch(TestModeBits)
                    {
                        case 0: Mode = MAX2871::SigmaDeltaNoiseMode::Normal;
                        break;

                        case 1: Mode = MAX2871::SigmaDeltaNoiseMode::LongReset;
                        break;

                        case 2: Mode = MAX2871::SigmaDeltaNoiseMode::ForceChargePumpIntoSource;
                        break;

                        case 3: Mode = MAX2871::SigmaDeltaNoiseMode::ForceChargePumpIntoSink;
                        break;
                    }

                    return TestMode;
                }


                // 28:26    MUX[2:0]    MUX Configuration   Sets MUX pin con guration (MSB bit located register 05). 
                //                                          0000 = Three-state output
                //                                          0001 = D_VDD
                //                                          0010 = D_GND
                //                                          0011 = R-divider output 
                //                                          0100 = N-divider output/2 
                //                                          0101 = Analog lock detect 
                //                                          0110 = Digital lock detect 
                //                                          0111 = Sync Input
                //                                          1000 : 1011 = Reserved
                //                                          1100 = Read SPI registers 06 
                //                                          1101 : 1111= Reserved
                

                void SetMuxConfiguration(enum MAX2871::MuxConfiguration Config)
                {

                }

                enum MAX2871::MuxConfiguration GetMuxConfiguration()
                {

                }

                // 25       DBR         Reference Doubler   Sets reference doubler mode. 
                //                                          0 = Disable reference doubler 
                //                                          1 = Enable reference doubler
                
                void SetReferenceDoubler(bool State)
                {

                }

                bool GetReferenceDoublerState()
                {

                }

                // 24       RDIV2       Reference Div2      Sets reference divide-by-2 mode. 
                //                                          0 = Disable reference divide-by-2 
                //                                          1 = Enable reference divide-by-2
                
                void SetReferenceDivider2(bool State)
                {

                }

                // 23:14    R[9:0]      Reference Divider   Sets reference divide value (R). 
                //                                          Double buffered by register 0. 
                //                                          0000000000 = 0 (unused)
                //                                          0000000001 = 1
                //                                          -----
                //                                          1111111111 = 1023
                
                void SetReferenceDividerValue(uint16_t Value)
                {

                }

                uint16_t GetReferenceDividerValue()
                {

                }

                // 13       REG4DB      Double Buffer       Sets double buffer mode. 0 = Disabled 1 = Enabled
                
                void SetDoubleBufferState(bool State)
                {

                }

                bool GetDoubleBufferState()
                {

                }

                // 12:9     CP[3:0]     Charge-Pump Current Sets charge-pump current in mA (RSET = 5.1kΩ). 
                //                                          Double buffered by register 0. 
                //                                          ICP = 1.63/RSET × (1+CP[3:0])
                
                void SetChargePumpCurrent(uint8_t Value)
                {
                    // MUST know what RSet is!
                }

                uint8_t GetChargePumpCurrentBinary()
                {

                }

                double GetChargePumpCurrentDouble()
                {

                }

                // 8        LDF         Lock-Detect Fn      Sets lock-detect function. 
                //                                          0 = Frac-N lock detect
                //                                          1 = Int-N lock detect
                
                


                void SetLockDetectFunction(enum MAX2871::LockDetectFunction Fn)
                {

                }

                enum MAX2871::LockDetectFunction GetLockDetectFunction()
                {

                }

                // 7        LDP         Lock-Detect Prec.   Sets lock-detect precision. 0 = 10ns 1 = 6ns
                
                

                void SetLockDetectFunction(enum MAX2871::LockDetectPrecision Precision)
                {

                }

                enum MAX2871::LockDetectPrecision GetLockDetectPrecision()
                {

                }

                // 6        PDP         Phase Detector Pol. Sets phase detector polarity. 
                //                                          0 = Negative 
                //                                          1 = Positive (default)

                void SetPhaseDetectorPolarity(enum MAX2871::PhaseDetectorPolarity Polarity)
                {

                }

                enum MAX2871::PhaseDetectorPolarity GetPhaseDetectorPolarity()
                {

                }


                // 5        SHDN        Shutdown Mode       Sets power-down mode. 0 = Normal mode 1 = Device shutdown

                void SetShutdownMode(enum MAX2871::ShutdownMode Shutdown)
                {

                }

                enum MAX2871::ShutdownMode GetShutdownMode()
                {

                }
                

                // 4        TRI         Charge Pump Output  Sets charge-pump output high-impedance mode. 
                //                      High Impedance      0 = Disabled
                //                                          1 = Enabled
                
                void SetChargePumpOutputHighZ(bool State)
                {

                }

                bool GetChargePumpOutputHighZ()
                {

                }

                // 3        RST         Counter Reset       Sets counter reset mode. 
                //                                          0 = Normal operation
                //                                          1 = R and N counters reset

                void SetCounterReset(enum MAX2871::CounterResetMode CounterReset)
                {

                }

                enum MAX2871::CounterResetMode GetCounterResetMode()
                {
                    
                }
                

                // 2:0      ADDR[2:0]   Address Bits        Control Register address bits, 010
                
                volatile uint32_t _R2 = 0x00004042;


                //--------------------------------------------------------------------------
                // Register 3
                //
                volatile uint32_t _R3 = 0x0000000B;


                //--------------------------------------------------------------------------
                // Register 4
                //
                volatile uint32_t _R4 = 0x6180B23C;


                //--------------------------------------------------------------------------
                // Register 5
                //
                volatile uint32_t _R5 = 0x00400005;


                //--------------------------------------------------------------------------
                // Register 6 (Read Only)
                //
                volatile uint32_t _R6 = 0x00000000;


            public:

                #pragma region Constructors

                Max2871()
                {
                    // Setup SPI (if needed)
                    // Try talking to the device.
                    // Try setting the basic registers to their default values.
                    // Must write twice to ensure proper setup.
                    // Initialize anything else.
                }

                #pragma endregion


                //--------------------------------------------------------------------------
                // Fractional-N or Integer-N Mode
                //
                // All the code herein is related to setting the parameters of fractional-N
                // or integer-N mode.
                //

                #pragma region FracN/IntN Mode

                void SetFracNMode(bool FracNMode)
                {
                    if(FracNMode)
                    {
                        // Set the fracN bit
                        CLEAR_BIT(_R0, 31)
                    }
                    else
                    {
                        // Clear the bit designating integer-N mode.
                        SET_BIT(_R0, 31)
                    }

                    // Make sure LDF bit is set to appropriate mode.
                    // If LDF is not correctly set, then pick a value to force the device into
                    // compliance...
                }

                bool IsFracNMode()
                {
                    return GET_BIT(_R0, 31);
                }

                bool IsIntNMode()
                {
                    return !IsFracNMode();
                }

                void SetIntegerNDivisionValue(uint16_t IntegerNDivValue)
                {
                    if(IntegerNDivValue > 15)
                    {
                        if(IsFracNMode())
                        {
                            if(IntegerNDivValue >= 19 && IntegerNDivValue <= 4091)
                            {
                                _R0 |= (IntegerNDivValue << 15);
                            }
                        }
                        else
                        {
                            _R0 |= (IntegerNDivValue << 15);
                        }
                    }
                }

                void SetFracNDivisionValue(uint16_t FracNDivValue)
                {
                    // Clear the top four bits to ensure we dont override other values.
                    _R0 |= (FracNDivValue & 0b0000111111111111) << 3;
                }


                #pragma endregion



                //--------------------------------------------------------------------------
                // Charge Pump and Loop Filter
                //

                #pragma region Charge Pump and Loop Filter

                

                #pragma end region


                void SetPhaseValueAdjustment(uint16_t Value)
                {
                    if(Value > 4095) Value = 4095;

                    _R1 |= ((uint32_t)Value) << 15;
                }

                uint16_t GetPhaseValueAdjustment()
                {
                    return (uint16_t)((_R1 >> 15) & 0b00000000000000000000111111111111); // Need to verify...
                }


                void SetChargePumpTestMode(enum MAX2871::ChargePumpTestMode TestMode)
                {
                    switch(TestMode)
                    {
                        case MAX2871::ChargePumpTestMode::Normal:

                            CLEAR_BITS(_R1, 27, 28)

                        break;

                        case MAX2871::ChargePumpTestMode::LongReset:

                            SET_BIT(_R1, 27)
                            CLEAR_BIT(_R1, 28)

                        break;

                        case MAX2871::ChargePumpTestMode::ForceChargePumpIntoSource:

                            SET_BIT(_R1, 28)
                            CLEAR_BIT(_R1, 27)

                        break;

                        case MAX2871::ChargePumpTestMode::ForceChargePumpIntoSink:

                            SET_BITS(_R1, 27, 28)

                        break;
                    }
                }

                enum MAX2871::ChargePumpTestMode GetChargePumpTestMode()
                {
                    enum MAX2871::ChargePumpTestMode TestMode;

                    uint32_t TestModeBits = (_R1 >> 27) & 0x11;
                    
                    switch(TestModeBits)
                    {
                        case 0: TestMode = MAX2871::ChargePumpTestMode::Normal;
                        break;

                        case 1: TestMode = MAX2871::ChargePumpTestMode::LongReset;
                        break;

                        case 2: TestMode = MAX2871::ChargePumpTestMode::ForceChargePumpIntoSource;
                        break;

                        case 3: TestMode = MAX2871::ChargePumpTestMode::ForceChargePumpIntoSink;
                        break;
                    }

                    return TestMode;
                }


                void SetChargePumpLinearity(enum MAX2871::ChargePumpLinearity Linearity)
                {
                    switch(Linearity)
                    {
                        case MAX2871::ChargePumpLinearity::Disabled:

                            CLEAR_BITS(_R1, 29, 30)

                        break;

                        case MAX2871::ChargePumpLinearity::Linearity10Percent:

                            SET_BIT(_R1, 29)
                            CLEAR_BIT(_R1, 30)

                        break;

                        case MAX2871::ChargePumpLinearity::Linearity20Percent:

                            SET_BIT(_R1, 30)
                            CLEAR_BIT(_R1, 29)

                        break;

                        case MAX2871::ChargePumpLinearity::Linearity30Percent:

                            SET_BIT(_R1, 29)
                            SET_BIT(_R1, 30)

                        break;
                    }
                }

                enum MAX2871::ChargePumpLinearity GetChargePumpLinearity()
                {
                    enum MAX2871::ChargePumpLinearity Linearity;

                    uint32_t LinearityBits = (_R1 >> 29) & 0x11;
                    
                    switch(LinearityBits)
                    {
                        case 0: Linearity = MAX2871::ChargePumpLinearity::Disabled;
                        break;

                        case 1: Linearity = MAX2871::ChargePumpLinearity::Linearity10Percent;
                        break;

                        case 2: Linearity = MAX2871::ChargePumpLinearity::Linearity20Percent;
                        break;

                        case 3: Linearity = MAX2871::ChargePumpLinearity::Linearity30Percent;
                        break;
                    }

                    return Linearity;
                }



                void SetFracNModulusValue(uint16_t Value)
                {
                    // Cap the value at 4095 (2^12 - 1)
                    if(Value > 4095) Value = 4095;

                    _R1 |= ((uint32_t)Value) << 3;
                }

                uint16_t GetFracNModulusValue()
                {
                    return (uint16_t)((_R1 >> 3) & 0b00000000000000000000111111111111); // Need to verify...
                }

                //--------------------------------------------------------------------------
                // Write
                //
                // Write the current software statet to the devices registers.
                //

                void Write()
                {

                }

        }; // end class Max2871

    }
}


#endif