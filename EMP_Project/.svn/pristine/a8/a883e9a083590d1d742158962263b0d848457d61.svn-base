/*
 * TemperatureInputs.h
 *
 *  Created on: 06.03.2015
 *      Author: s.hegemann
 */

#ifndef CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_TEMPERATUREINPUTS_H_
#define CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_TEMPERATUREINPUTS_H_

//Messages
//#define NO      0
//#define ERROR   1
//#define WARNING 2
//#define STATUS  3
//#define DEBUG   4

// Oscillator
#define INTERNAL_OSC    0
#define EXTERNAL_OSC    1

// Reference Status
#define VREF_OFF    0
#define VREF_ON     1
#define VREF_AUTO   2
#define REF0        0
#define REF1        1
#define REF_INT     2
#define REF_INT_SUPPLY  3

// System Monitor
#define NORMAL_OPERATION    0
#define MEASURE_OFFSET      1
#define MEASURE_GAIN        2
#define TEMPERATURE_DIODE   3
#define MEASURE_REF01       4
#define MEASURE_REF02       5
#define MEASURE_AVDD        6
#define MEASURE_DVDD        7

// Channel
#define ANI0    0
#define ANI1    1
#define ANI2    2
#define ANI3    3
#define ANI4    4
#define ANI5    5
#define ANI6    6
#define ANI7    7
#define IEXT1   8
#define IEXT2   9
#define DISCONNTECT 12

//PGA
#define PGAx1   0
#define PGAx2   1
#define PGAx4   2
#define PGAx8   3
#define PGAx16  4
#define PGAx32  5
#define PGAx46  6
#define PGAx128 7

//Samples
#define SPS5        0
#define SPS10       1
#define SPS20       2
#define SPS40       3
#define SPS80       4
#define SPS160      5
#define SPS320      6
#define SPS640      7
#define SPS1000     8
#define SPS20000    9

// OutputCurrent
#define CURRENT0        0
#define CURRENT50       1
#define CURRENT100      2
#define CURRENT250      3
#define CURRENT500      4
#define CURRENT750      5
#define CURRENT1000     6
#define CURRENT1500     7



// ADS1248 register
#define ADS1248_MUX0_REGISTER    0x00
#define ADS1248_VBIAS_REGISTER   0x01
#define ADS1248_MUX1_REGISTER    0x02
#define ADS1248_SYS0_REGISTER    0x03
#define ADS1248_OFC0_REGISTER    0x04
#define ADS1248_OFC1_REGISTER    0x05
#define ADS1248_OFC2_REGISTER    0x06
#define ADS1248_FSC0_REGISTER    0x07
#define ADS1248_FSC1_REGISTER    0x08
#define ADS1248_FSC2_REGISTER    0x09
#define ADS1248_IDAC0_REGISTER   0x0A
#define ADS1248_IDAC1_REGISTER   0x0B
#define ADS1248_GPIOCFG_REGISTER 0x0C
#define ADS1248_GPIODIR_REGISTER 0x0D
#define ADS1248_GPIODAT_REGISTER 0x0E


//SPI Commands
//Control
#define ADS1248_CMD_WAKEUP          0x01
#define ADS1248_CMD_SLEEP           0x02
#define ADS1248_CMD_SYNC            0x04
#define ADS1248_CMD_RESET           0x06
#define ADS1248_CMD_NOP             0xFF
//Read Data
#define ADS1248_CMD_RDATA           0x12
#define ADS1248_CMD_RDATAC          0x14
#define ADS1248_CMD_SDATAC          0x16
//Read Registers
#define ADS1248_CMD_RREG            0x20
//Write Registers
#define ADS1248_CMD_WREG            0x40
//Calibration
#define ADS1248_CMD_SYSOCAL         0x60
#define ADS1248_CMD_SYSGCAL         0x61
#define ADS1248_CMD_SELFOCAL        0x62
//Restricted command should be never send to the device :)
#define ADS1248_CMD_RESTRICTED      0xF1


#define ACTIVE_LOW  0
#define ACTIVE_HIGH 0
////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <string>
#include <vector>
#include <mutex>
#include "median.h"

#include "GaGCppAPI.h"

namespace BaseTecDriver {

    class TemperatureInputs
    {
        public:
            struct tPruData
            {
                union {
                        struct {
                                uint8_t rdy             : 1;
                                uint8_t tempRdy         : 1;
                                uint8_t tempReset       : 1;
                                uint8_t __bit03         : 1;
                                uint8_t msbFirst        : 1;
                                uint8_t __bit05         : 1;
                                uint8_t __bit06         : 1;
                                uint8_t __bit07         : 1;
                        } bit;
                        uint8_t word;
                } hwInfo;

                uint8_t commandState;
                uint8_t writeByteCnt;
                uint8_t readByteCnt;
                uint8_t _unused[12];
                uint8_t writeBuffer[32];
                uint8_t readBuffer[32];
            };
            ///////////////////////////////ADS1248 structs////////////////////////////////////////////////////////////
            volatile union {
              struct {
                unsigned char MUX_SN0   :1;
                unsigned char MUX_SN1   :1;
                unsigned char MUX_SN2   :1;
                unsigned char MUX_SP0   :1;
                unsigned char MUX_SP1   :1;
                unsigned char MUX_SP2   :1;
                unsigned char BCS0      :1;
                unsigned char BCS1      :1;
              };
              struct {
                unsigned char MUX_SN    :3;
                unsigned char MUX_SP    :3;
                unsigned char BCS       :2;
              };
              unsigned char all;
            } MUX0_Reg;
            volatile union {
              struct {
                unsigned char VBIAS0   :1;
                unsigned char VBIAS1   :1;
                unsigned char VBIAS2   :1;
                unsigned char VBIAS3   :1;
                unsigned char VBIAS4   :1;
                unsigned char VBIAS5   :1;
                unsigned char VBIAS6   :1;
                unsigned char VBIAS7   :1;
              };
              unsigned char all;
            } VBIAS_Reg;
            volatile union {
              struct {
                unsigned char MUXCAL0   :1;
                unsigned char MUXCAL1   :1;
                unsigned char MUXCAL2   :1;
                unsigned char REFSELT0 :1;
                unsigned char REFSELT1 :1;
                unsigned char VREFCON0 :1;
                unsigned char VREFCON1 :1;
                unsigned char CLKSTAT   :1;
              };
              struct {
                unsigned char MUXCAL    :3;
                unsigned char REFSELT   :2;
                unsigned char VREFCON   :2;
                unsigned char           :1;
              };
              unsigned char all;
            } MUX1_Reg;
            volatile union {
              struct {
                unsigned char DR0       :1;
                unsigned char DR1       :1;
                unsigned char DR2       :1;
                unsigned char DR3       :1;
                unsigned char PGA0     :1;
                unsigned char PGA1     :1;
                unsigned char PGA2     :1;
                unsigned char           :1;
              };
              struct {
                unsigned char DR        :4;
                unsigned char PGA       :3;
                unsigned char           :1;
              };
              unsigned char all;
            } SYS_Reg;
            volatile union {
              struct {
                unsigned char OFC0     :1;
                unsigned char OFC1     :1;
                unsigned char OFC2     :1;
                unsigned char OFC3     :1;
                unsigned char OFC4     :1;
                unsigned char OFC5     :1;
                unsigned char OFC6     :1;
                unsigned char OFC7     :1;
              };
              unsigned char all;
            } OFC0_Reg;
            volatile union {
              struct {
                unsigned char OFC8      :1;
                unsigned char OFC9      :1;
                unsigned char OFC10    :1;
                unsigned char OFC11    :1;
                unsigned char OFC12    :1;
                unsigned char OFC13    :1;
                unsigned char OFC14    :1;
                unsigned char OFC15    :1;
              };
              unsigned char all;
            } OFC1_Reg;
            volatile union {
              struct {
                unsigned char OFC16    :1;
                unsigned char OFC17    :1;
                unsigned char OFC18    :1;
                unsigned char OFC19    :1;
                unsigned char OFC20    :1;
                unsigned char OFC21    :1;
                unsigned char OFC22    :1;
                unsigned char OFC23    :1;
              };
              unsigned char all;
            } OFC2_Reg;
            volatile union {
              struct {
                unsigned char FSC0     :1;
                unsigned char FSC1     :1;
                unsigned char FSC2     :1;
                unsigned char FSC3     :1;
                unsigned char FSC4     :1;
                unsigned char FSC5     :1;
                unsigned char FSC6     :1;
                unsigned char FSC7     :1;
              };
              unsigned char all;
            } FSC0_Reg;
            volatile union {
              struct {
                unsigned char FSC8      :1;
                unsigned char FSC9      :1;
                unsigned char FSC10    :1;
                unsigned char FSC11    :1;
                unsigned char FSC12    :1;
                unsigned char FSC13    :1;
                unsigned char FSC14    :1;
                unsigned char FSC15    :1;
              };
              unsigned char all;
            } FSC1_Reg;
            volatile union {
              struct {
                unsigned char FSC16    :1;
                unsigned char FSC17    :1;
                unsigned char FSC18    :1;
                unsigned char FSC19    :1;
                unsigned char FSC20    :1;
                unsigned char FSC21    :1;
                unsigned char FSC22    :1;
                unsigned char FSC23    :1;
              };
              unsigned char all;
            } FSC2_Reg;
            volatile union {
              struct {
                unsigned char IMAG0 :1;
                unsigned char IMAG1 :1;
                unsigned char IMAG2 :1;
                unsigned char DRDY_MODE:1;
                unsigned char ID0       :1;
                unsigned char ID1       :1;
                unsigned char ID2       :1;
                unsigned char ID3       :1;
              };
              struct {
                unsigned char IMAG      :3;
                unsigned char       :1;
                unsigned char ID        :4;
              };
              unsigned char all;
            } IDAC0_Reg;
            volatile union {
              struct {
                unsigned char I2DIR0   :1;
                unsigned char I2DIR1   :1;
                unsigned char I2DIR2   :1;
                unsigned char I2DIR3   :1;
                unsigned char I1DIR0   :1;
                unsigned char I1DIR1   :1;
                unsigned char I1DIR2   :1;
                unsigned char I1DIR3   :1;
              };
              struct {
                unsigned char I2DIR    :4;
                unsigned char I1DIR    :4;
              };
              unsigned char all;
            } IDAC1_Reg;
            volatile union {
              struct {
                unsigned char IOCFG0   :1;
                unsigned char IOCFG1   :1;
                unsigned char IOCFG2   :1;
                unsigned char IOCFG3   :1;
                unsigned char IOCFG4   :1;
                unsigned char IOCFG5   :1;
                unsigned char IOCFG6   :1;
                unsigned char IOCFG7   :1;
              };
              unsigned char all;
            } GPIOCFG_Reg;
            volatile union {
              struct {
                unsigned char IODIR0   :1;
                unsigned char IODIR1   :1;
                unsigned char IODIR2   :1;
                unsigned char IODIR3   :1;
                unsigned char IODIR4   :1;
                unsigned char IODIR5   :1;
                unsigned char IODIR6   :1;
                unsigned char IODIR7   :1;
              };
              unsigned char all;
            } GPIODIR_Reg;
            volatile union {
              struct {
                unsigned char IODAT0   :1;
                unsigned char IODAT1   :1;
                unsigned char IODAT2   :1;
                unsigned char IODAT3   :1;
                unsigned char IODAT4   :1;
                unsigned char IODAT5   :1;
                unsigned char IODAT6   :1;
                unsigned char IODAT7   :1;
              };
              unsigned char all;
            } GPIODAT_Reg;

            //////////////////////////////////////////////////////////////////////////////

        public:
            TemperatureInputs(volatile void* ptMemoryBase,
                              std::string _dataBaseNode,
                              std::string _loggerName);

            virtual ~TemperatureInputs();

            int32_t
            taskRun(gs_Task taskHandle,
                    const uint32_t* frameNumber) noexcept;

            void printInfo();
            void reg_write(uint8_t reg, uint8_t data,uint8_t numberOfRegs = 1);
            uint8_t reg_read(uint8_t startReg, uint8_t numberOfRegs = 1);
            void ads_rec_temperature(float *temperature);
            void ads_send(uint8_t data);
            void ads_singleCmd(uint8_t);
            void ads_nop(void);
            void ads_reset(void);                   //Resets the ADS1248 to initvalues
            void ads_init(uint8_t mode= 0);        //Initialises the ADS1248 for the selected sensortypes
            void ads_getAllRegister();              //Reads all register in the sturcture
            void ads_setAllRegister();              //Writes all registers from the sturcture to the ADS1248
            void ads_selfCal();                     //Caribrates the ADS1248
            void ads_selectChannel(int channel);    //Select ADS1248 meausurement chanel

            bool ads_get_reset_state();
            float ads_get_temperature(int channel);
            void ads_set_temperature(int channel, float temperature);


            bool firstRunDone = false;
            int ende = 0;
            int returnState = 0;
            float tempFlt = 0;
            int32_t tempRaw = 0;
            Filter md;



        private:
            GaGCppAPI::TypedPV<uint32_t>* rawValue;
            GaGCppAPI::TypedPV<float>* normValue;

            std::string dataBaseNode;
            std::string mLoggerName;
            volatile tPruData*  ptRawData;
            bool adsReset = false;
            float temperature_ch1 = 0;
            float temperature_ch2 = 0;
            float temperature_ch3 = 0;

    };


} /* namespace BaseTecDriver */

#endif /* CHUCKCOOLING_SOURCE_BASETECDRIVER_INCLUDE_TEMPERATUREINPUTS_H_ */
