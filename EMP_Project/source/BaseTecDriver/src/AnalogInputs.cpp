/*
 * AnalogInputs.cpp
 *
 *  Created on: 05.03.2015
 *      Author: s.hegemann
 */

#include <iomanip>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <math.h>

#include "AnalogInputs.h"
#include "GaAppBaseLib.h"

namespace BaseTecDriver {

    const uint32_t AnalogInputs::dataBufferSize;

    AnalogInputs::AnalogInputs(volatile void* ptMemoryBase,
                               std::string _dataBaseNode,
                               std::string _loggerName,
                               uint32_t _taskCycleTime)
            : dataBaseNode(_dataBaseNode)
    {
        mLoggerName = _loggerName;
        el::Loggers::getLogger(mLoggerName);

        taskCycleTime = _taskCycleTime;

        ptRawData = (tAnalogData*) ptMemoryBase;
        memset((void*) ptRawData, 0, (unsigned int)sizeof(tAnalogData));
/*
        ptRawData->sampleAverage = 3;
        ptRawData->openDelay = 100;
        ptRawData->sampleDelay = 100;
*/
        ptRawData->sampleAverage = 2;
        ptRawData->openDelay = 10;
        ptRawData->sampleDelay = 5;

        lastReadPos = 0;
        lastWritePos = 0;
        lastChannelId = 7;

        for (int i = 0; i < 7; i++) {
            std::string index = std::to_string(i);
            GaGCppAPI::TypedPV<uint16_t>* rawVal = new GaGCppAPI::TypedPV<uint16_t>((dataBaseNode + ".Analog_0" + index + ".rawValue").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
            this->rawVal.push_back(rawVal);

            GaGCppAPI::TypedPV<float>* normVal = new GaGCppAPI::TypedPV<float>((dataBaseNode + ".Analog_0" + index + ".normValue").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
            this->normVal.push_back(normVal);

            GaGCppAPI::TypedPV<float>* val = new GaGCppAPI::TypedPV<float>((dataBaseNode + ".Analog_0" + index + ".value").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
            this->Val.push_back(val);
        }
    }

    AnalogInputs::~AnalogInputs()
    {
        for (auto elm = rawVal.begin(); elm != rawVal.end(); elm++) {
            delete (*elm);
        }
        rawVal.clear();
    }

    int32_t
    AnalogInputs::taskRun() noexcept
    {
        bool readPosCorrected = false;
        uint32_t channel;
        uint32_t value;

        uint16_t dumpDiagCnt = ptRawData->diagCnt;
        uint16_t dumpWritePos = ptRawData->writePos;
        uint16_t dumpReadPos = ptRawData->readPos;
        ptRawData->diagCnt = 0;

        if (lastReadPos != dumpReadPos) {
            CLOG(WARNING, mLoggerName.c_str()) << "analog inputs: read position is modified! " << std::dec << dumpReadPos << " should be: " << lastReadPos;
        }

        if ((dumpReadPos < 0) || (dumpReadPos >= dataBufferSize)) {
            CLOG(WARNING, mLoggerName.c_str()) << "analog inputs: invalid read position" << std::dec << dumpReadPos;
            dumpReadPos = 0;
            readPosCorrected = true;
        }

        if (dumpDiagCnt > dataBufferSize-1) {
            CLOG(WARNING, mLoggerName.c_str()) << "analog inputs: buffer overflow detected; " << (int)dumpDiagCnt - (int)dataBufferSize << " values lost (" << dumpDiagCnt << " values written since last read out; buffer size: " << dataBufferSize << " values) ";
            dumpReadPos += (int)dumpDiagCnt - (int)dataBufferSize;
            dumpReadPos %= dataBufferSize;
            readPosCorrected = true;
        }

        for (int i = 0; i < 7; i++) {
            chn[i].sampleCount = 0;
            chn[i].sumValues = 0;
        }

        while (ptRawData->dataBuffer[dumpReadPos] & 0x8000)
        {
            if (!(ptRawData->dataBuffer[dumpReadPos] & 0x8000)) {
                CLOG(WARNING, mLoggerName.c_str()) << "invalid buffer entry 0x" << std::hex << std::setw(4) << std::setfill('0') << ptRawData->dataBuffer[dumpReadPos];
            }
            else {
                channel = ptRawData->dataBuffer[dumpReadPos] & 0x7000;
                value = ptRawData->dataBuffer[dumpReadPos] & 0x0fff;
                ptRawData->dataBuffer[dumpReadPos] &= ~0x8000;

                channel >>= 12;

                if (channel > 7) {
                    CLOG(WARNING, mLoggerName.c_str()) << "analog inputs: invalid channel ID " << channel;
                    break;
                }

                lastChannelId++;
                if (lastChannelId >= 7)
                    lastChannelId = 0;
                if (channel != lastChannelId) {
                    if (!readPosCorrected) {
                        CLOG(WARNING, mLoggerName.c_str()) << "missing data for channel " << lastChannelId << " (current index: " << channel << ").";
                    }
                    lastChannelId = channel;
                }

                readPosCorrected = false;

                chn[channel].sumValues += (value / 4096.0) * 10.2;
                chn[channel].sampleCount++;
            }

            dumpReadPos++;
            if ((dumpReadPos < 0) || (dumpReadPos >= dataBufferSize))
                dumpReadPos = 0;

            dumpDiagCnt--;
            if (dumpDiagCnt == 0) {
                break;
            }

        } // while (ptRawData->dataBuffer[dumpReadPos] & 0x8000)


        for (int i = 0; i < 7; i++) {
            if (chn[i].sampleCount > 0) {
                chn[i].lastValue = chn[i].sumValues  / chn[i].sampleCount;
                chn[i].sampleRate = chn[i].sampleCount / (float)(taskCycleTime / 1000.0 / 1000.0);
            }
            // rawVal.at(i)->put((float) chn[i].lastValue);
            // normVal.at(i)->put((float) chn[i].lastValue / 4096.0);
            Val.at(i)->put((float) chn[i].lastValue);
        }

        lastWritePos = dumpWritePos;
        lastReadPos = dumpReadPos;
        ptRawData->readPos = dumpReadPos;
        return (0);
    }

    void
    AnalogInputs::printRegisterInfo()
    {
        int32_t fp;
        fp = open("/dev/mem", O_RDWR | O_SYNC);
        uint8_t* reg = (uint8_t*) mmap(0, 0xff, PROT_READ | PROT_WRITE, MAP_SHARED, fp, 0x44E0D000);
        if (*reg != 0) {
            std::cout << "\n Analog Input Register:"
                    << "\n========================"
                    /*
                     << "\n  REVISION               0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x0  ))
                     << "\n  SYSCONFIG              0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x10 ))
                     << "\n  IRQSTATUS_RAW          0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x24 ))
                     << "\n  IRQSTATUS              0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x28 ))
                     << "\n  IRQENABLE_SET          0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x2C ))
                     << "\n  IRQENABLE_CLR          0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x30 ))
                     << "\n  IRQWAKEUP              0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x34 ))
                     << "\n  DMAENABLE_SET          0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x38 ))
                     << "\n  DMAENABLE_CLR          0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x3C ))
                     << "\n  CTRL                   0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x40 ))
                     << "\n  ADCSTAT                0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x44 ))
                     << "\n  ADCRANGE               0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x48 ))
                     << "\n  ADC_CLKDIV             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x4C ))
                     << "\n  ADC_MISC               0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x50 ))
                     << "\n  STEPENABLE             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x54 ))
                     << "\n  IDLECONFIG             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x58 ))
                     << "\n  TS_CHARGE_STEPCONFIG   0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x5C ))
                     << "\n  TS_CHARGE_DELAY        0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x60 ))
                     << "\n  STEPCONFIG1            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x64 ))
                     << "\n  STEPDELAY1             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x68 ))
                     << "\n  STEPCONFIG2            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x6C ))
                     << "\n  STEPDELAY2             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x70 ))
                     << "\n  STEPCONFIG3            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x74 ))
                     << "\n  STEPDELAY3             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x78 ))
                     << "\n  STEPCONFIG4            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x7C ))
                     << "\n  STEPDELAY4             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x80 ))
                     << "\n  STEPCONFIG5            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x84 ))
                     << "\n  STEPDELAY5             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x88 ))
                     << "\n  STEPCONFIG6            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x8C ))
                     << "\n  STEPDELAY6             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x90 ))
                     << "\n  STEPCONFIG7            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x94 ))
                     << "\n  STEPDELAY7             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x98 ))
                     << "\n  STEPCONFIG8            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0x9C ))
                     << "\n  STEPDELAY8             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xA0 ))
                     << "\n  STEPCONFIG9            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xA4 ))
                     << "\n  STEPDELAY9             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xA8 ))
                     << "\n  STEPCONFIG10           0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xAC ))
                     << "\n  STEPDELAY10            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xB0 ))
                     << "\n  STEPCONFIG11           0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xB4 ))
                     << "\n  STEPDELAY11            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xB8 ))
                     << "\n  STEPCONFIG12           0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xBC ))
                     << "\n  STEPDELAY12            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xC0 ))
                     << "\n  STEPCONFIG13           0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xC4 ))
                     << "\n  STEPDELAY13            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xC8 ))
                     << "\n  STEPCONFIG14           0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xCC ))
                     << "\n  STEPDELAY14            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xD0 ))
                     << "\n  STEPCONFIG15           0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xD4 ))
                     << "\n  STEPDELAY15            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xD8 ))
                     << "\n  STEPCONFIG16           0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xDC ))
                     << "\n  STEPDELAY16            0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xE0 ))
                     << "\n  FIFO0COUNT             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xE4 ))
                     << "\n  FIFO0THRESHOLD         0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xE8 ))
                     << "\n  DMA0REQ                0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xEC ))
                     << "\n  FIFO1COUNT             0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xF0 ))
                     << "\n  FIFO1THRESHOLD         0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xF4 ))
                     << "\n  DMA1REQ                0x" << std::hex << std::setw(8) << std::setfill('0') << (*(uint32_t*)(reg + 0xF8 ))
                     */
                    << "\n"
                    << "\n   PRU code status:        0x" << std::hex << std::setw(8) << std::setfill('0') << ptRawData->inputState
                    << "\n   PRU diag counter:       0x" << std::dec << std::setw(8) << std::setfill(' ') << ptRawData->diagCnt
                    << "\n   PRU readPos:            0x" << std::dec << std::setw(8) << std::setfill(' ') << ptRawData->readPos
                    << "\n   PRU writePos:           0x" << std::dec << std::setw(8) << std::setfill(' ') << ptRawData->writePos
                    << "\n"
                    << "\n" << std::endl;
/*
            for (uint32_t i = 0; i < dataBufferSize; i += 16) {
                std::cout << " "  << std::dec << std::setw(4)  << i + 1 << ": " << std::hex << std::setw(4) << ptRawData->dataBuffer[i+0] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+1] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+2] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+3] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+4] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+5] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+6] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+7] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+8] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+9] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+10] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+11] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+12] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+13] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+14] << "  "
                                                                                                   << std::setw(4) << ptRawData->dataBuffer[i+15] << "  "
                                                                                                   << std::endl;
            }
*/
        }
        else {
            std::cout << "\n Analog Input Register:"
                    << "\n========================"
                    << "\n  REVISION               0x" << std::hex << std::setw(8) << std::setfill('0') << *(reg + 0x0)
                    << "\n" << std::endl;
        }
        close(fp);

        for (int i = 0; i < 7; i++) {
            std::cout << " Channel " << std::dec << i + 1 << ": Value " << std::setw(6) << std::setfill(' ') << std::setprecision(3) << chn[i].lastValue << "V   (samples: " << std::setw(4) << chn[i].sampleCount << ")" << std::endl;
        }

    }

} /* namespace BaseTecDriver */
