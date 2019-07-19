/*
 * TemperatureInputs.cpp
 *
 *  Created on: 06.03.2015
 *      Author: s.hegemann
 */

#include <iomanip>

#include "DigitalOutputs.h"
#include "TemperatureInputs.h"

#include "GaAppBaseLib.h"
#include "HardwareCtrl.h"
#include <bitset>

namespace BaseTecDriver
{
  std::mutex t; //temperature read/write mutex

  TemperatureInputs::TemperatureInputs(volatile void* ptMemoryBase,
      std::string _dataBaseNode,
      std::string _loggerName)
  : dataBaseNode(_dataBaseNode),
    mLoggerName(_loggerName)
  {
    ptRawData = (tPruData*) ptMemoryBase;
    memset((void*) ptRawData, (int)0, (unsigned long int)sizeof(tPruData));

    rawValue = new GaGCppAPI::TypedPV<uint32_t>((dataBaseNode + ".Temperature_00"+".rawValue").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
    normValue = new GaGCppAPI::TypedPV<float>((dataBaseNode + ".Temperature_00" + ".normValue").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);

    for (int i = 0; i < 1; i++) {

      std::string index = std::to_string(i);
      //        GaGCppAPI::TypedPV<uint8_t>* errorLevel = new GaGCppAPI::TypedPV<uint8_t>((dataBaseNode + ".Temperature_0" + index + ".errorLevel").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
      //        errorLevel->put(0);
      GaGCppAPI::TypedPV<float>* normValue = new GaGCppAPI::TypedPV<float>((dataBaseNode + ".Temperature_0" + index + ".normValue").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
      normValue->put(0);
      //        GaGCppAPI::SharedPV* normMode = new GaGCppAPI::SharedPV((dataBaseNode + ".Temperature_0" + index + ".normMode").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
      // normMode->put("std");
      //        GaGCppAPI::TypedPV<uint32_t>* rawValue = new GaGCppAPI::TypedPV<uint32_t>((dataBaseNode + ".Temperature_0" + index + ".rawValue").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
      //        rawValue->put(0);
      //        GaGCppAPI::TypedPV<float>* value = new GaGCppAPI::TypedPV<float>((dataBaseNode + ".Temperature_0" + index + ".value").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
      //        value->put(0);

    }

  }


  TemperatureInputs::~TemperatureInputs()
  {

    delete rawValue;
    delete normValue;

  }

  int32_t
  TemperatureInputs::taskRun(gs_Task taskHandle,
      const uint32_t* frameNumber) noexcept
      {
    //        std::cout << "current input gpio bank 3: 0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ptRawData->_unused[0]
    //                                                     << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ptRawData->_unused[1]
    //                                                     << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ptRawData->_unused[2]
    //                                                     << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)ptRawData->_unused[3] << std::endl;

    float tmpTemp = 0;

    if(!firstRunDone)
    {
      //Wait 0,6ms after reset
      usleep(600);

      ads_init();
      ptRawData->commandState = 0;
      firstRunDone = true;
      //
      //            //Debug
      //            ads_selectChannel(0);
      //            //Debug
      return(0);
    }

    switch (ptRawData->commandState)
    {
      case 0:
        //Select Channel 1 for measurement
        //ads_selectChannel(0);
        ptRawData->commandState = 1;
        break;

      case 1://Wait for result from channel 1
        if(ptRawData->hwInfo.bit.tempRdy)
        {
          ads_rec_temperature(&tmpTemp);
          ads_set_temperature(1,tmpTemp);
          normValue->put(tmpTemp);
          ptRawData->commandState = 0;
        }
        else
        {
          ptRawData->commandState = 1;
        }
        break;

      default:
        //CLOG(ERROR, mLoggerName.c_str()) << "temperature inputs: invalid command state " << (uint16_t)ptRawData->commandState;
        ptRawData->commandState = 0;
        break;

    } // switch (ptRawData->commandState)

    return (0);
      }


  void
  TemperatureInputs::printInfo()
  {
    std::cout << "\n Temperature Input Register:"
        << "\n=============================="
        << "\n"
        << "\n   PRU code status:        0x" << std::hex << std::setw(2) << std::setfill('0') << (uint16_t)ptRawData->hwInfo.word
        << "\n   PRU diag counter:       " << std::dec << std::setw(4) << std::setfill(' ') << (uint16_t)ptRawData->commandState
        << "\n   PRU Bytes to Write:     " << std::dec << std::setw(4) << std::setfill(' ') << (uint16_t)ptRawData->writeByteCnt
        << "\n   PRU read Bytes:         " << std::dec << std::setw(4) << std::setfill(' ') << (uint16_t)ptRawData->readByteCnt
        << "\n"
        << "\n" << std::endl;
  }

  void TemperatureInputs::reg_write(uint8_t reg, uint8_t data, uint8_t numberOfRegs)
  {
    while(ptRawData->hwInfo.bit.rdy);                           //Wait for last send is done
    ptRawData->readByteCnt = 0;                                 //No Bytes to read
    ptRawData->writeBuffer[2] = (reg&0x0F)|ADS1248_CMD_WREG;    //mask upper 4bytes and replace them with 0100
    ptRawData->writeBuffer[1] = 0x00;                           //Number of registers to be written (= number of bytes -1)
    ptRawData->writeBuffer[0] = data;                           //Databyte
    ptRawData->writeByteCnt = numberOfRegs+2;                   //number of bytes to send
    ptRawData->hwInfo.bit.rdy = 1;                              //Let's go!
  }

  uint8_t TemperatureInputs::reg_read(uint8_t startReg, uint8_t numberOfRegs)
  {
    while(ptRawData->hwInfo.bit.rdy);                                   //Wait for last send is done
    ptRawData->writeBuffer[1] = (startReg&0x0F)|ADS1248_CMD_RREG ;      //mask upper 4bytes and replace them with 0010
    ptRawData->writeBuffer[0] = (numberOfRegs-1)&0x0F;                  //Number of registers to read (= number of bytes -1)
    ptRawData->readByteCnt = numberOfRegs;                              //Number of registers to read, Max 4
    ptRawData->writeByteCnt = 2;                                        //number of bytes to send
    ptRawData->hwInfo.bit.rdy = 1;                                      //Let's go!
    while(ptRawData->hwInfo.bit.rdy);
    return (ptRawData->readBuffer[0]);
    //Send same number of nop as registers to read
  }

  void TemperatureInputs::ads_singleCmd(uint8_t data)
  {
    while(ptRawData->hwInfo.bit.rdy);           //Wait for last send is done
    ptRawData->readByteCnt = 0;                                 //No Bytes to read
    ptRawData->writeBuffer[0] = data;           //NOP
    ptRawData->writeByteCnt = 1;
    ptRawData->hwInfo.bit.rdy = 1;              //Let's go!
  }

  void TemperatureInputs::ads_nop(void)
  {
    while(ptRawData->hwInfo.bit.rdy);           //Wait for last send is done
    ptRawData->readByteCnt = 0;                                 //No Bytes to read
    ptRawData->writeBuffer[0] = 0xFF;           //NOP
    ptRawData->writeByteCnt = 1;
    ptRawData->hwInfo.bit.rdy = 1;              //Let's go!
  }

  void TemperatureInputs::ads_reset(void)
  {
    while(ptRawData->hwInfo.bit.rdy);               //Wait for last send is done
    ptRawData->writeBuffer[0] = ADS1248_CMD_RESET;  //Reset
    ptRawData->writeByteCnt = 1;
    ptRawData->readByteCnt = 0;
    ptRawData->hwInfo.bit.tempRdy;              //Temperature ready to receive
    ptRawData->hwInfo.bit.rdy = 1;                  //Let's go!
    usleep(20*1000);                                // 16 ms according to data sheet
  }

  void TemperatureInputs::ads_selfCal()
  {
    ads_send (ADS1248_CMD_SELFOCAL);
    usleep(100*1000);
  }

  //Get all ADS1248 registers
  void TemperatureInputs::ads_getAllRegister()
  {
    //        uint8_t id = reg_read(0x0A);
    //        std::bitset<8> d(id);
    //
    //        std::cout<<"ADS1248 ID: " << d << std::endl;
    //        for(int i = 0; i<32 ;i++)
    //        {
    //                    std::bitset<8> x(ptRawData->readBuffer[i]);
    //                    std::cout << "readBuffer[" << i << "] = " << x << std::endl;
    //        }
    //        while(1);

    MUX0_Reg.all     = reg_read(ADS1248_MUX0_REGISTER);
    VBIAS_Reg.all    = reg_read(ADS1248_VBIAS_REGISTER);
    MUX1_Reg.all     = reg_read(ADS1248_MUX1_REGISTER);
    SYS_Reg.all      = reg_read(ADS1248_SYS0_REGISTER);
    OFC0_Reg.all     = reg_read(ADS1248_OFC0_REGISTER);
    OFC1_Reg.all     = reg_read(ADS1248_OFC1_REGISTER);
    OFC2_Reg.all     = reg_read(ADS1248_OFC2_REGISTER);
    FSC0_Reg.all     = reg_read(ADS1248_FSC0_REGISTER);
    FSC1_Reg.all     = reg_read(ADS1248_FSC1_REGISTER);
    FSC2_Reg.all     = reg_read(ADS1248_FSC2_REGISTER);
    IDAC0_Reg.all    = reg_read(ADS1248_IDAC0_REGISTER);
    IDAC1_Reg.all    = reg_read(ADS1248_IDAC1_REGISTER);
    GPIOCFG_Reg.all  = reg_read(ADS1248_GPIOCFG_REGISTER);
    GPIODIR_Reg.all  = reg_read(ADS1248_GPIODIR_REGISTER);
    GPIODAT_Reg.all  = reg_read(ADS1248_GPIODAT_REGISTER);

    //                std::bitset<8> a(MUX0_Reg.all);
    //                std::cout << a << std::endl;
    //                std::bitset<8> b(VBIAS_Reg.all);
    //                std::cout << b << std::endl;
    //                std::bitset<8> c(MUX1_Reg.all);
    //                std::cout << c << std::endl;
    //                std::bitset<8> d(SYS_Reg.all);
    //                std::cout << d << std::endl;
    //                std::bitset<8> e(OFC0_Reg.all);
    //                std::cout << e << std::endl;
    //                std::bitset<8> f(OFC1_Reg.all);
    //                std::cout << f << std::endl;
    //                std::bitset<8> g(FSC0_Reg.all);
    //                std::cout << g << std::endl;
    //                std::bitset<8> h(FSC1_Reg.all);
    //                std::cout << h << std::endl;
    //                std::bitset<8> i(FSC2_Reg.all);
    //                std::cout << i << std::endl;
    //                std::bitset<8> j(IDAC0_Reg.all);
    //                std::cout << j << std::endl;
    //                std::bitset<8> k(IDAC1_Reg.all);
    //                std::cout << k << std::endl;
    //                std::bitset<8> l(GPIOCFG_Reg.all);
    //                std::cout << l << std::endl;
    //                std::bitset<8> m(GPIODIR_Reg.all);
    //                std::cout << m << std::endl;
    //                std::bitset<8> n(GPIODAT_Reg.all);
    //                std::cout << n << std::endl;
    //                while(1);

  }

  //Set all ADS1248 registers
  void TemperatureInputs::ads_setAllRegister()
  {
    reg_write(ADS1248_MUX0_REGISTER,MUX0_Reg.all);
    reg_write(ADS1248_VBIAS_REGISTER,VBIAS_Reg.all);
    reg_write(ADS1248_MUX1_REGISTER,MUX1_Reg.all);
    reg_write(ADS1248_SYS0_REGISTER,SYS_Reg.all);
    reg_write(ADS1248_OFC0_REGISTER,OFC0_Reg.all);
    reg_write(ADS1248_OFC1_REGISTER,OFC1_Reg.all);
    reg_write(ADS1248_OFC2_REGISTER,OFC2_Reg.all);
    reg_write(ADS1248_FSC0_REGISTER,FSC0_Reg.all);
    reg_write(ADS1248_FSC1_REGISTER,FSC1_Reg.all);
    reg_write(ADS1248_FSC2_REGISTER,FSC2_Reg.all);
    reg_write(ADS1248_IDAC0_REGISTER,IDAC0_Reg.all);
    reg_write(ADS1248_IDAC1_REGISTER,IDAC1_Reg.all);
    reg_write(ADS1248_GPIOCFG_REGISTER,GPIOCFG_Reg.all);
    reg_write(ADS1248_GPIODIR_REGISTER,GPIODIR_Reg.all);
    reg_write(ADS1248_GPIODAT_REGISTER,GPIODAT_Reg.all);
  }



  void TemperatureInputs::ads_rec_temperature(float *temperature)
  {
    //ADC started and finished conversion
    //Debug
    //
    while(ptRawData->hwInfo.bit.rdy);               //Wait for last send is done
    //usleep(100000);
    ptRawData->writeBuffer[0] = ADS1248_CMD_RDATA;  //Read data once
    ptRawData->writeByteCnt = 1;
    ptRawData->readByteCnt = 3;
    ptRawData->hwInfo.bit.rdy = 1;                  //Let's go!
    while(ptRawData->hwInfo.bit.rdy);               //Wait for send
    ptRawData->hwInfo.bit.tempRdy;                  //Clear "Temperature Ready"


    long valTmp = 0;
    float u = 0;
    float res = 0;

    valTmp = valTmp | (ptRawData->readBuffer[2] << 16);
    valTmp = valTmp | (ptRawData->readBuffer[1] << 8);
    valTmp = valTmp | (ptRawData->readBuffer[0] );


    u = valTmp/32768.0;     //2048/ffffff/PGA - mV
    res = u*1;              //1mA
    //        *temperature = 3367.821- sqrt(11342221.257-(res-100)/5.802*100000);
    float tempRaw = 3367.821- sqrt(11342221.257-(res-100)/5.802*100000);

    *temperature = (float)md.mcalc((double)tempRaw);

    //printf("U: %3.3f\tR: %3.3f\tTemperatur: %3.3f \n",u,res,*temperature);

    return;
  }

  void TemperatureInputs::ads_send(uint8_t data)
  {
    ptRawData->writeBuffer[0] = data;
    ptRawData->readByteCnt = 0;                                 //No Bytes to read
    ptRawData->writeByteCnt = 1;
    ptRawData->hwInfo.bit.rdy = 1;              //Let's go!
  }

  void TemperatureInputs::ads_init(uint8_t mode)
  {
    switch (mode)
    {
      case 1:

        break;

        // Setup for normal PT100 Mode
      default:
        ptRawData->hwInfo.word = 0;
        ads_getAllRegister();
        MUX0_Reg.MUX_SN         = ANI2;
        MUX0_Reg.MUX_SP         = ANI1;
        MUX1_Reg.VREFCON        = VREF_ON;
        MUX1_Reg.REFSELT        = REF_INT;
        MUX1_Reg.MUXCAL         = NORMAL_OPERATION;
        SYS_Reg.PGA             = PGAx8;
        SYS_Reg.DR              = SPS640;//SPS160;
        IDAC0_Reg.DRDY_MODE     = 0;        // DO nur als MISO!!!
        IDAC0_Reg.IMAG          = CURRENT1000;   // IDAC 100uA
        IDAC1_Reg.I1DIR         = ANI0;
        IDAC1_Reg.I2DIR         = DISCONNTECT;
        ads_setAllRegister();

        //selfCalibration();
        break;
        ads_nop();
    }
  }

  ///////////////////////////// selectChannel ////////////////////////////////
  void TemperatureInputs::ads_selectChannel(int channel)
  {
    //Todo: wieder löschen!!!!!!!!!!
    //channel = 0;
    switch(channel)
    {
      case 0:
      {
        IDAC1_Reg.I1DIR =ANI0;
        MUX0_Reg.MUX_SP = ANI1;
        MUX0_Reg.MUX_SN = ANI2;
        break;
      }
      case 1:
      {
        IDAC1_Reg.I1DIR =ANI3;
        MUX0_Reg.MUX_SP = ANI4;
        MUX0_Reg.MUX_SN = ANI5;
        break;
      }
      case 2:
      {
        IDAC1_Reg.I1DIR =IEXT1;
        MUX0_Reg.MUX_SP = ANI6;
        MUX0_Reg.MUX_SN = ANI7;
        break;
      }
      default:
        break;
    }
    reg_write(ADS1248_MUX0_REGISTER,MUX0_Reg.all);
    reg_write(ADS1248_IDAC1_REGISTER,IDAC1_Reg.all);
    ads_nop();
  }

  bool TemperatureInputs::ads_get_reset_state()
  {
    return (adsReset);
  }

  float TemperatureInputs::ads_get_temperature(int channel)
  {
    float tmp = 0;
    switch (channel)
    {
      case 1:
        t.lock();
        tmp = temperature_ch1;
        std::cout << "ads_get_temperature: " << tmp << std::endl;
        t.unlock();
        return(tmp);
      case 2:
        t.lock();
        tmp = temperature_ch2;
        t.unlock();
        return(tmp);
      case 3:
        t.lock();
        tmp = temperature_ch3;
        t.unlock();
        return(tmp);
      default:
        return(999.999);

    }

  }

  void TemperatureInputs::ads_set_temperature(int channel, float newTemperature)
  {
    switch (channel)
    {
      case 1:
        t.lock();
        temperature_ch1 = newTemperature;
        t.unlock();
        break;
      case 2:
        t.lock();
        temperature_ch2 = newTemperature;
        t.unlock();
        break;
      case 3:
        t.lock();
        temperature_ch3 = newTemperature;
        t.unlock();
        break;
      default:
        return;
    }
    return;
  }



} /* namespace BaseTecDriver */
