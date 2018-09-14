//------------------------------------------------------------------------------------------
// MAX2871 
//
// Harrison Statham
//

#ifndef MAX2871_HPP
#define MAX2871_HPP

#include <functional>
#include "stdint.h"

#include "mbed.h"
#include "Macros.h"

namespace RFVSG
{

    enum eFracNSigmaDeltaNoiseMode
    {
        LowNoise,
        Reserved,
        LowSpur1,
        LowSpur2        
    };

    enum ePolarity
    {
        Negative,
        Positive
    };


    enum eLockDetectPrecision
    {
        TenNs,
        SixNs
    };


    enum eLockDetectFunction
    {
        FracNLockDetect,
        IntNLockDetect
    };

    enum eLockDetectSpeed
    {
        SlowerThan32MHz,
        FasterThan32MHz
    };

    enum eLockDetectPinFunction
    {
        Low,
        DigitalLock,
        AnalogLock,
        High
    };

    enum eChargePumpLinearityMode
    {
        Disabled,
        TenPercent,
        TwentyPercent,
        ThirtyPercent
    };

    enum eChargePumpTestMode
    {
        Normal,
        LongReset,
        ForceIntoSource,
        ForceIntoSink
    };

    enum eVCOFeedbackMode
    {
        Divided,
        Fundamental
    };


    enum eRFOutputPowerLevels
    {
        MinusFourDBm,
        MinusOneDBm,
        PlusTwoDBm,
        PlusFiveDBm
    };

    enum eRFOutputPath
    {
        VCODivided,
        Fundamental
    };

    enum eRFOutputDividerMode
    {
        Div1,
        Div2,
        Div4,
        Div8,
        Div16,
        Div32,
        Div64,
        Div128
    };

    enum eMuxConfiguration
    {
        TriStateOutput,
        DigitalVdd,
        DigitalGnd,
        RDividerOutput,
        NDividerOutputDivideBy2,
        AnalogLockDetect,
        DigitalLockDetect,
        SyncInput,
        Reserved1,
        Reserved2,
        Reserved3,
        Reserved4,
        ReadSPIRegister6
    };


    enum eADCMode
    {
        Disabled,
        TempSensor,
        Reserved1,
        Reserved2,
        TunePin
    };


    class MAX2871
    {

    private:
        
        //-----------------------------------------------------
        //
        #pragma region Registers

        //-----------------------------------------------------
        // Register 0
        // 

        union 
        {
            struct
            {
                uint32_t Address                : 3;
                uint32_t FractionalDivision     : 12;
                uint32_t IntegerDivision        : 16;
                uint32_t IsIntegerMode          : 1;

            } Bits;

            volatile uint32_t Value;

        } _R0;



        //-----------------------------------------------------
        //
        union
        {
            struct
            {
                uint32_t Address                : 3;
                uint32_t Modulus                : 12;
                uint32_t Phase                  : 12;
                uint32_t ChargePumpTest         : 2;
                uint32_t ChargePumpLinearity    : 2;
                uint32_t Reserved               : 1;

            } Bits;

            volatile uint32_t Value;

        } _R1;

        

        //-----------------------------------------------------
        // 
        union 
        {
            struct
            {
                uint32_t Address                : 3;
                uint32_t CounterReset           : 1;
                uint32_t ChargePumpHighZ        : 1;
                uint32_t Shutdown               : 1;
                uint32_t PhaseDetectorPolarity  : 1;
                uint32_t LockDetectPrecision    : 1;
                uint32_t LockDetectFunction     : 1;
                uint32_t ChargePumpCurrent      : 4;
                uint32_t DoubleBufferMode       : 1;
                uint32_t ReferenceDividerValue  : 10;
                uint32_t ReferenceDivideBy2Mode : 1;
                uint32_t ReferenceDoublerMode   : 1;
                uint32_t MuxConfiguration       : 3;
                uint32_t SigmaDeltaNoiseMode    : 2;
                uint32_t LockDetectSpeed        : 1;

            } Bits;

            uint32_t Value;

        } _R2;

        




        //-----------------------------------------------------
        //
        union
        {
            struct
            {
                uint32_t Address            : 3;
                uint32_t ClockDividerValue  : 12;
                uint32_t ClockDividerMode   : 2;
                uint32_t MuteDelayMode      : 1;
                uint32_t CycleSlipMode      : 1;
                uint32_t Reserved           : 5;
                uint32_t VASTemp            : 1;
                uint32_t VASShutdown        : 1;
                uint32_t VCO                : 6;

            } Bits;

            uint32_t Value;

        } _R3;

        

        //-----------------------------------------------------
        //
        union
        {
            struct
            {
                uint32_t Address                : 3;
                uint32_t RFOutputAPower         : 2;
                uint32_t RFAEnable              : 1;
                uint32_t RFOutputBPower         : 2;
                uint32_t RFBEnable              : 1;
                uint32_t RFBOutputPath          : 1;
                uint32_t MuteUntilLockDetect    : 1;
                uint32_t VCOShutdown            : 1;
                uint32_t BandSelect             : 8;
                uint32_t RFOutputDividerMode    : 3;
                uint32_t VCOFeedbackMode        : 1;
                uint32_t BandSelectMSB          : 2;
                uint32_t ShutdownReferenceInput : 1;
                uint32_t ShutdownVCODivider     : 1;
                uint32_t ShutdownVCOLDO         : 1;
                uint32_t Reserved               : 3;

            } Bits;
            
            uint32_t Value;

        } _R4;

        

        //-----------------------------------------------------
        //
        union
        {
            struct
            {
                uint32_t Address                : 3;
                uint32_t ADCMode                : 3;
                uint32_t ADCStart               : 1;
                uint32_t Reserved1              : 11;
                uint32_t MuxMSB                 : 1;
                uint32_t Reserved2              : 3;
                uint32_t LockDetectPinFunction  : 2;
                uint32_t F01                    : 1;
                uint32_t ShutdownPLL            : 1;
                uint32_t Reserved3              : 3;
                uint32_t VCOAutoselectDelay     : 2;
                uint32_t Reserved4              : 1;
            } Bits;

            uint32_t Value;

        } _R5;

        
        

        //-----------------------------------------------------
        //
        union
        {
            struct
            {
                uint32_t Address        : 3;
                uint32_t CurrentVCO     : 6;
                uint32_t VASActive      : 1;
                uint32_t Reserved1      : 5;
                uint32_t ADCValid       : 1;
                uint32_t ADCCode        : 7;
                uint32_t PowerOnReset   : 1;
                uint32_t Reserved2      : 4;
                uint32_t DieID          : 4;

            } Bits;
            
            uint32_t Value;

        } _R6;

        #pragma endregion
        

        //-----------------------------------------------------
        //
        std::function<void(int)>& ReadFunction;
        
        std::function<void(int)>& WriteFunction;

        DigitalOut ChipEnable;

        DigitalIn LockDetect;

        DigitalOut RFOutputEnable;

        DigitalOut Mux;

        float RSet;

    
    public:

        #pragma region Constructors

        MAX2871(std::function<void(int)> ReadFn, std::function<void(int)> WriteFn, PinName ChipEnablePin, PinName LockDetectPin, PinName RFOutputEnablePin, PinName MuxPin, float RSetResistor)
        : ChipEnable(ChipEnablePin), LockDetect(LockDetectPin), RFOutputEnable(RFOutputEnablePin), Mux(MuxPin), RSet(RSetResistor)
        {

            // Set the registers to their default values.
            _R0.Value = 0x007D0000;
            _R1.Value = 0x2000FFF9;
            _R2.Value = 0x00004042;
            _R3.Value = 0x0000000B;
            _R4.Value = 0x6180B23C;
            _R5.Value = 0x00400005;

            // Note: Apart from setting the register value, we arent allowed to write to
            // this register. However, the read_function *can* write to this register.
            _R6.Value = 0x00000006;

            ReadFunction = ReadFn;
            WriteFunction = WriteFn;
        }

        #pragma endregion

        
        //-----------------------------------------------------
        //
        #pragma region PLL Methods


        bool IsFractionalNMode()
        {
            return !_R0.Bits.IsIntegerMode;
        }


        // Enable Fractional-N Mode
        // 
        void EnableFractionalNMode()
        {
            // Note: The LDF bit must be set accordingly!
            // TODO: Check this out properly.
           _R0.Bits.IsIntegerMode = 0; 
        }


        // Set Fractional-N Division Value
        // 
        // Set the frac-N value from 0 to 4095.
        // See F01 bit.
        // 
        void SetFractionalDivisionValue(uint16_t Value)
        {
            // The top four bits should ALWAYS be zero.
            Value &= 0x0FFF;

            _R0.Bits.FractionalDivision = Value; // Can I do this without shifting Value???
        }


        // Set F01
        //
        // Sets integer mode for F = 0.
        // 
        void SetF01(bool State)
        {

        }


        void SetModulus(uint16_t Value)
        {
            // Value must always be greater than 1 and less than 4096.
            Value &= 0xFFE;

            _R1.Bits.Modulus = Value;
        }


        void SetSigmaDeltaNoiseMode(eFracNSigmaDeltaNoiseMode NoiseMode)
        {
            if(NoiseMode != eFracNSigmaDeltaNoiseMode::Reserved)
            {
                _R2.Bits.SigmaDeltaNoiseMode = NoiseMode;
            }
        }

        
        void SetIntegerDivisionValue(uint16_t Value)
        {
            if(IsFractionalNMode())
            {
                // Integer-N value must be betweeen 19 and 4091 inclusive while
                // in fractional-n mode.
                if(Value >= 19 && Value <= 4091)
                {
                    _R0.Bits.IntegerDivision = Value;
                }
            }
            else
            {
                // Integer-N value must be greater than 15 in integer-n mode.
                if(Value > 15)
                {
                    _R0.Bits.IntegerDivision = Value;
                }
            }
        }


        // Enable Fractional-N Mode
        // 
        void EnableIntegerNMode()
        {
            // Note: The LDF bit must be set accordingly!
            // TODO: Check this out properly.
           _R0.Bits.IsIntegerMode = 1; 
        }


        // Is Integer N Mode
        // 
        bool IsIntegerNMode()
        {
            return _R0.Bits.IsIntegerMode;
        }

        
        // Reset R/N Counter
        // 
        // Reset the R & N counters in the device.
        //
        void ResetRNCounter()
        {
            _R2.Bits.CounterReset = 1;
        }


        // Set Phase Detector Polarity
        //
        void SetPhaseDetectorPolarity(ePolarity Polarity)
        {
            _R2.Bits.PhaseDetectorPolarity = Polarity;
        }

        
        // Set Lock Detect Precision
        void SetLockDetectPrecision(eLockDetectPrecision Precision)
        {
            _R2.Bits.LockDetectPrecision = Precision;
        }

        
        // Set Lock Detect Function
        //
        void SetLockDetectFunction(eLockDetectFunction Func)
        {
            _R2.Bits.LockDetectFunction = Func;
        }


        // Set Lock Detect Speed
        //
        void SetLockDetectSpeed(eLockDetectSpeed Speed)
        {
            _R2.Bits.LockDetectSpeed = Speed;
        }


        // Set Lock Detect Pin Function
        //
        void SetLockDetectPinFunction(eLockDetectPinFunction PinFunction)
        {
            _R5.Bits.LockDetectPinFunction = PinFunction;
        }


        // Enable Slip Cycle Reduction
        void EnableSlipCycleReduction()
        {
            _R3.Bits.CycleSlipMode = 1;
        }


        // Disable Slip Cycle Reduction
        //
        void DisableSlipCycleReduction()
        {
            _R3.Bits.CycleSlipMode = 0;
        }


        // 
        void EnablePLL()
        {
            _R5.Bits.ShutdownPLL = 0;
        }

        void ShutdownPLL()
        {
            _R5.Bits.ShutdownPLL = 1;
        }

        #pragma endregion


        //-----------------------------------------------------
        //
        #pragma region Charge Pump


        // Set Charge Pump Test Mode
        // 
        void SetChargePumpTestMode(eChargePumpTestMode TestMode)
        {
            _R1.Bits.ChargePumpTest = TestMode;
        }


        // Set Charge Pump Linearity
        // 
        void SetChargePumpLinearity(eChargePumpLinearityMode LinearityMode)
        {
            _R1.Bits.ChargePumpLinearity = LinearityMode;
        }


        // Enable Charge Pump High Impedance
        // 
        void EnableChargePumpHighZ()
        {
            _R2.Bits.ChargePumpHighZ = 1;
        }


        void DisableChargePumpHighZ()
        {
            _R2.Bits.ChargePumpHighZ = 0;
        }


        void SetChargePumpCurrent(uint8_t Current)
        {
            // Only the lower four bits can be set.
            Current &= 0x0F;

            _R2.Bits.ChargePumpCurrent = Current;
        }


        //
        float CalculateChargePumpCurrent()
        {
            uint8_t CPCurrent = _R2.Bits.ChargePumpCurrent;

            return (1.63/RSet)*(1 + CPCurrent);
        }

        #pragma endregion


        //-----------------------------------------------------
        //
        #pragma region Reference Input


        // Set Reference Divider Value (R)
        void SetReferenceDividerValue(uint16_t Value)
        {
            // Only the top 10 bits can be set.
            Value &= 0x3FF;

            _R2.Bits.ReferenceDividerValue = Value;
        }


        void EnableReferenceDivideBy2()
        {
            _R2.Bits.ReferenceDivideBy2Mode = 1;
        }


        void DisableReferenceDivideBy2()
        {
            _R2.Bits.ReferenceDivideBy2Mode = 0;
        }


        void EnableReferenceDoubler()
        {
            _R2.Bits.ReferenceDoublerMode = 1;
        }


        void DisableReferenceDoubler()
        {
            _R2.Bits.ReferenceDoublerMode = 0;
        }

        void EnableReferenceInput()
        {
            _R4.Bits.ShutdownReferenceInput = 0;
        }

        void DisableReferenceInput()
        {
            _R4.Bits.ShutdownReferenceInput = 1;
        }


        #pragma endregion


        //-----------------------------------------------------
        //
        #pragma region VCO

        void SetVCO(uint8_t VCO)
        {
            // Check to see if VAS is disabled first.
            if(!IsVCOAutoSelectEnabled())
            {
                VCO &= 0x3F;

                _R3.Bits.VCO = VCO;
            }
        }

        void EnableVCO()
        {
            _R4.Bits.VCOShutdown = 0;
        }

        void DisableVCO()
        {
            _R4.Bits.VCOShutdown = 1;
        }

        void SetVCOFeedbackMode(eVCOFeedbackMode FeedbackMode)
        {
            _R4.Bits.VCOFeedbackMode = FeedbackMode;
        }

        
        void EnableVCODivider()
        {
            _R4.Bits.ShutdownVCODivider = 0;
        }

        void DisableVCODivider()
        {
            _R4.Bits.ShutdownVCODivider = 1;
        }


        void EnableVCOLDO()
        {
            _R4.Bits.ShutdownVCOLDO = 0;
        }

        void DisableVCOLDO()
        {
            _R4.Bits.ShutdownVCOLDO = 0;
        }


        void EnableVCOAutoSelect()
        {
            _R3.Bits.VASShutdown = 0;
        }


        void DisableVCOAutoSelect()
        {
            _R3.Bits.VASShutdown = 1;
        }


        bool IsVCOAutoSelectEnabled()
        {
            return !_R3.Bits.VASShutdown;
        }


        void EnableVCOAutoSelectTempCompensation()
        {
            _R3.Bits.VASTemp = 1;
        }

        void DisableVCOAutoSelectTempCompensation()
        {
            _R3.Bits.VASTemp = 0;
        }

        bool IsVCOAutoSelectTempCompensationEnabled()
        {
            return _R3.Bits.VASTemp;
        }

        void SetVCOAutoselectDelay()
        {
            if(IsVCOAutoSelectTempCompensationEnabled())
            {
                _R5.Bits.VCOAutoselectDelay = 0b11;
            }
            else
            {
                _R5.Bits.VCOAutoselectDelay = 0b00;
            }
        }

        uint8_t GetCurrentVCO()
        {
            return _R6.Bits.CurrentVCO;
        }

        
        bool IsVCOAutoSelectSearching()
        {
            return !_R6.Bits.VASActive;
        }

        #pragma endregion

        //-----------------------------------------------------
        //
        #pragma region RF Outputs


        void SetPhase(uint16_t Value)
        {
            // We only use the top 12 bits.
            Value &= 0x0FFF;

            _R1.Bits.Phase = Value;
        }


        // Set RF Output A Power
        //
        void SetRFOutputAPower(eRFOutputPowerLevels PowerLevel)
        {
            _R4.Bits.RFOutputAPower = PowerLevel;
        }


        void EnableRFOutputA()
        {
            _R4.Bits.RFAEnable = 1;
        }


        void DisableRFOutputA()
        {
            _R4.Bits.RFAEnable = 0;
        }


        // 
        //
        void SetRFOutputBPower(eRFOutputPowerLevels PowerLevel)
        {
            _R4.Bits.RFOutputBPower = PowerLevel;
        }


        void EnableRFOutputB()
        {
            _R4.Bits.RFBEnable = 1;
        }


        void DisableRFOutputB()
        {
            _R4.Bits.RFBEnable = 0;
        }


        void SetRFOutputBPath(eRFOutputPath Path)
        {
            _R4.Bits.RFBOutputPath = Path;
        }


        void EnableMuteUntilLockDetect()
        {   
            _R4.Bits.MuteUntilLockDetect = 1;
        }


        void DisableMuteUntilLockDetect()
        {
            _R4.Bits.MuteUntilLockDetect = 0;
        }


        /*
        000 = Divide by 1, if 3000MHz ≤ fRFOUTA ≤ 6000MHz
        001 = Divide by 2, if 1500MHz ≤ fRFOUTA< 3000MHz
        010 = Divide by 4, if 750MHz ≤ fRFOUTA < 1500MHz
        011 = Divide by 8, if 375MHz ≤ fRFOUTA < 750MHz
        100 = Divide by 16, if 187.5MHz ≤ fRFOUTA < 375MHz 
        101 = Divide by 32, if 93.75MHz ≤ fRFOUTA < 187.5MHz 
        110 = Divide by 64, if 46.875MHz ≤ fRFOUTA < 93.75MHz 
        111 = Divide by 128, if 23.5MHz ≤ fRFOUTA< 46.875MHz
        */
        void SetRFOutputDividerMode(eRFOutputDividerMode DividerMode)
        {
            _R4.Bits.RFOutputDividerMode = DividerMode;
        }

        #pragma endregion


        //-----------------------------------------------------
        //
        #pragma region Digital Inputs/Outputs
        
        void SWShutdown()
        {
            _R2.Bits.Shutdown = 1;
        }


        void SWPowerOn()
        {
            _R2.Bits.Shutdown = 0;
        }


        void SetMuxConfiguration(eMuxConfiguration MuxConfig)
        {
            _R2.Bits.MuxConfiguration = MuxConfig;
        }


        // 
        // 
        void SetMuxMSB()
        {
            // Verify!
            _R5.Bits.MuxMSB = 1;
        }


        bool IsPowerOnReset()
        {
            return _R6.Bits.PowerOnReset;
        }

        uint8_t GetDieID()
        {
            if(_R6.Bits.DieID == 0b0110)
            {
                return 2870;
            }
            else
            {
                return 2871;
            }
        }

        #pragma endregion


        //-----------------------------------------------------
        //
        #pragma region ADC


        void SetADCMode(eADCMode ADCMode)
        {
            if(ADCMode != 0b010 && ADCMode != 0b011)
            {
                _R5.Bits.ADCMode = ADCMode;
            }
        }

        void EnableADCNormalOperation()
        {
            _R5.Bits.ADCStart = 0;
        }

        void StartADCConversion()
        {
            _R5.Bits.ADCStart = 1;
        }


        bool IsADCValid()
        {  
            return _R6.Bits.ADCValid;
        }


        uint8_t GetADCCode()
        {
            return _R6.Bits.ADCCode;
        }

        #pragma endregion



        //-----------------------------------------------------
        //
        #pragma region Misc Methods


        void SetDoubleBufferMode(bool State)
        {

        }

        void SetClockDividerValue(uint16_t Value)
        {

        }

        void SetClockDividerMode(uint8_t Mode)
        {

        }

        void SetMuteDelayState(bool State)
        {

        }

        

        


        void SetBandSelect(uint8_t Band)
        {

        }

        void SetBandSelectMSB()
        {

        }

        

        

        #pragma endregion

    }; // end class MAX2871

} // end namespace RFVSG 

#endif