#include "CandleStick.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

CandleStick::CandleStick(const std::string& _timestamp, 
                         double _open, 
                         double _close, 
                         double _high, 
                         double _low)

: timestamp(_timestamp), 
  open(_open), 
  close(_close), 
  high(_high), 
  low(_low) 
{

}

std::string CandleStick::getTimestamp() const {
    return timestamp;
}

double CandleStick::getOpen() const {
    return open;
}

double CandleStick::getClose() const {
    return close;
}

double CandleStick::getHigh() const {
    return high;
}

double CandleStick::getLow() const {
    return low;
}