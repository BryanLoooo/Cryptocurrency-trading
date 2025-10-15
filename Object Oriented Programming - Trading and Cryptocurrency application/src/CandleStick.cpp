//importing libraries
#include "CandleStick.h"
#include <iostream>
#include <string>
#include <vector>

CandleStick::CandleStick(const std::string& timestamp,
                        double open,
                        double close, 
                        double high, 
                        double low)
:   timestamp_(timestamp),
    open_(open),
    close_(close),
    high_(high),
    low_(low)
{

}

std::string CandleStick::getTimestamp() const{
    return timestamp_;
}

double CandleStick::getOpen() const{
    return open_;
}

double CandleStick::getClose() const{
    return close_;
}

double CandleStick::getHigh() const{
    return high_;
}

double CandleStick::getLow() const{
    return low_;
}