#ifndef CANDLESTICK_H
#define CANDLESTICK_H

#include <string>
#include <vector>

class CandleStick{
    public:

        //declare Candlestick constructor
        CandleStick(const std::string& timestamp = "",
        double open = 0.0, 
        double close = 0.0,
        double high = 0.0, 
        double low = 0.0);

        //declare functions
        std::string getTimestamp() const;

        double getOpen() const;
        double getClose() const;
        double getHigh() const;
        double getLow() const;

    private:

        //declaring variables
        std::string timestamp_;
        double open_;
        double close_;
        double high_;
        double low_;
};

#endif //end of the candlestick header file