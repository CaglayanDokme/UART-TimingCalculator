/* @brief   UART statistical container and calculator class.
 * @author  Caglayan DOKME, caglayandokme@gmail.com
 * @date    November 11, 2021
 */

// Prevent circular inclusion
#pragma once

// Class Definition
class UartStats
{
public:
    /** Helper Types **/
    class StopBit_t
    {
    public:
        enum Type{STOP_BIT_1, STOP_BIT_1p5, STOP_BIT_2};

        StopBit_t(const Type type = STOP_BIT_1) : bitType(type) { }

        operator float() const
        {
            switch(bitType){
                case STOP_BIT_1:
                    return 1;
                case STOP_BIT_1p5:
                    return 1.5;
                case STOP_BIT_2:
                    return 2;
            }
        }

        Type bitType;
    };

    class Parity_t{
    public:
        enum Type{NONE, ODD, EVEN};

        Parity_t(const Type type = NONE) : bitType(type) { }

        operator float() const
        {
            switch(bitType){
                case NONE:
                    return 0;
                case ODD:
                    return 1;
                case EVEN:
                    return 1;
            }
        }

        Type bitType;
    };

    /** Constructor **/
    UartStats() { update(); }

    /** Member Methods **/
    void setBaudrate(const unsigned int newBaud)      { baudrate = newBaud;      update(); }
    void setDataBits(const unsigned int newDataBits)  { dataBits = newDataBits;  update(); }
    void setStopBit(const StopBit_t::Type newStopBit) { stopBit  = newStopBit;   update(); }
    void setParity(const Parity_t::Type newParityBit) { parity   = newParityBit; update(); }

    float           getBitPerByte() const { return bitPerByte;      }
    unsigned int    getBaudrate()   const { return baudrate;        }
    unsigned int    getDataBits()   const { return dataBits;        }
    StopBit_t::Type getStopBit()    const { return stopBit.bitType; }
    Parity_t::Type  getParity()     const { return parity.bitType;  }

    void update()           { bitPerByte = 1 + dataBits + parity + stopBit; }  // 1: Start bit
    float calculate() const { return (1 / (float(baudrate) / bitPerByte));  }

private:
    /** Members **/
    unsigned int baudrate   {1};
    unsigned int dataBits   {8};
    StopBit_t    stopBit    {StopBit_t::STOP_BIT_1};
    Parity_t     parity     {Parity_t::NONE};
    float        bitPerByte;
};
