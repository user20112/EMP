/*
 * Filter.h
 *
 *  Created on: 24.06.2014
 *      Author: c.zeuke
 */

#ifndef FILTER_H_
#define FILTER_H_
///////////////////////////////////////////////////////////////////////////////
//includes
#include "median.h"
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//class
namespace BaseTecDriver
{
  Filter::Filter()
  {
    int i = 0;
    cnt = 0;
    pos = 0;
    for(i=0; i<WINDOW; i++)
    {
      Values[i] = 0.0;
    }
  }
  Filter::~Filter()
  {}

  double Filter::mcalc(double newValue)
  {
    double retVal = 0;
    int i = 0;
    //int j = 0;
    //int k = 0;

    Values[pos++]= newValue;
    if(pos > WINDOW) pos = 0;

    for(i=0; i<WINDOW; i++)
    {
      SortList[i] = Values[i];
    }

    for (int j = 0; j < WINDOW; ++j)
    {
      //   Find position of minimum element
      int min = j;
      for (int k = j + 1; k < WINDOW; ++k)
        if (SortList[k] < SortList[min])
          min = k;
      //   Put found minimum element in its place
      double temp = SortList[j];
      SortList[j] = SortList[min];
      SortList[min] = temp;
    }
    retVal = (SortList[1]+SortList[2]+SortList[3])/3.0;

    return (retVal);
  }
}
#endif /* FILTER_H_ */
