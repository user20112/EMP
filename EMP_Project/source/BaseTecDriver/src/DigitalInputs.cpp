/*
 * DigitalInputs.cpp
 *
 *  Created on: 05.03.2015
 *      Author: s.hegemann
 */

#include "GaAppBaseLib.h"

#include "DigitalInputs.h"

namespace BaseTecDriver {

    DigitalInputs::DigitalInputs(volatile void* ptMemoryBase,
                                 std::string _dataBaseNode,
                                 std::string _loggerName)
            : dataBaseNode(_dataBaseNode)
    {
        mLoggerName = _loggerName;
        el::Loggers::getLogger(mLoggerName);

        ptRawData = (tDataChannel*) ptMemoryBase;
        memset((void*) ptRawData, 0, sizeof(tDataChannel));

        for (int i = 0; i < 9; i++) {
            std::string index = std::to_string(i);

            GaGCppAPI::TypedPV<uint8_t>* mode = new GaGCppAPI::TypedPV<uint8_t>((dataBaseNode + ".Input_0" + index + ".countMode").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
            countMode.push_back(mode);
            switch (mode->get()) {
            default:
                case 0:
                ptRawData->countMode[i] = eCountMode::DISABLED;
                break;

            case 1:
                ptRawData->countMode[i] = eCountMode::ON_EDGE_HIGH;
                break;

            case 2:
                ptRawData->countMode[i] = eCountMode::ON_EDGE_LOW;
                break;

            case 3:
                ptRawData->countMode[i] = eCountMode::ON_BOTH_EDGES;
                break;
            }

            GaGCppAPI::TypedPV<uint8_t>* state = new GaGCppAPI::TypedPV<uint8_t>((dataBaseNode + ".Input_0" + index + ".actState").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
            actState.push_back(state);

            GaGCppAPI::TypedPV<uint32_t>* rawCount = new GaGCppAPI::TypedPV<uint32_t>((dataBaseNode + ".Input_0" + index + ".rawCounterValue").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
            rawCounter.push_back(rawCount);
            GaGCppAPI::TypedPV<float>* count = new GaGCppAPI::TypedPV<float>((dataBaseNode + ".Input_0" + index + ".counterValue").c_str(), ga_PV_PROPERTY_ACC_NON_BLOCKING);
            float scaleFactor = atof(count->getProperty("scaleFactor").c_str());
            if (scaleFactor <= 0) {
                scaleFactor = 1;
            }
            counterScaleFactor.push_back(scaleFactor);
            edgeCounter.push_back(count);
        }
    }

    DigitalInputs::~DigitalInputs()
    {
        for (auto elm = countMode.begin(); elm != countMode.end(); elm++) {
            delete (*elm);
        }
        countMode.clear();
        for (auto elm = actState.begin(); elm != actState.end(); elm++) {
            delete (*elm);
        }
        actState.clear();
        for (auto elm = edgeCounter.begin(); elm != edgeCounter.end(); elm++) {
            delete (*elm);
        }
        edgeCounter.clear();
    }

    int32_t
    DigitalInputs::taskRun(gs_Task taskHandle,
                           const uint32_t* frameNumber) noexcept
    {
        for (int i = 0; i < 9; i++) {
            switch (countMode.at(i)->get()) {
            default:
                case 0:
                ptRawData->countMode[i] = eCountMode::DISABLED;
                break;

            case 1:
                ptRawData->countMode[i] = eCountMode::ON_EDGE_HIGH;
                break;

            case 2:
                ptRawData->countMode[i] = eCountMode::ON_EDGE_LOW;
                break;

            case 3:
                ptRawData->countMode[i] = eCountMode::ON_BOTH_EDGES;
                break;
            }

            actState.at(i)->put((uint8_t) ptRawData->activeState[i]);
            if (*frameNumber > 0) {
                rawCounter.at(i)->put((uint32_t) ptRawData->edgeCounter[i]);
                edgeCounter.at(i)->put((float) (ptRawData->edgeCounter[i] * counterScaleFactor.at(i)));
            }
            else {
                std::cout << "restore counter value for channel " << i+1 << " to " << rawCounter.at(i)->get() << std::endl;
                ptRawData->edgeCounter[i] = rawCounter.at(i)->get();
                edgeCounter.at(i)->put((float) (ptRawData->edgeCounter[i] * counterScaleFactor.at(i)));
            }

        }

        return (0);
    }

} /* namespace BaseTecDriver */
