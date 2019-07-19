/*
 * Filter.h
 *
 *  Created on: 24.06.2014
 *      Author: c.zeuke
 */

#ifndef MEDIAN_FILTER_H_
#define MEDIAN_FILTER_H_
///////////////////////////////////////////////////////////////////////////////
//includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <CircularBuffer.h>

///////////////////////////////////////////////////////////////////////////////
//defines
#define WINDOW 9

///////////////////////////////////////////////////////////////////////////////
namespace BaseTecDriver {
    class Filter
    {
    public:
        double Values[WINDOW];
        double SortList[WINDOW];
        int cnt = 0;
        int pos = 0;
        double mcalc(double newValue);

        Filter();

        virtual ~Filter();


    };
}
#endif /* FILTER_H_ */
