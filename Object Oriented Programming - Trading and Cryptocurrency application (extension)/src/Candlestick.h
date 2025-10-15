#ifndef CANDLESTICK_H
#define CANDLESTICK_H

#include <string>
#include <vector>

class CandleStick {
    public:
        CandleStick(const std::string& timestamp = "", 
                    double open = 0.0, 
                    double close = 0.0, 
                    double high = 0.0, 
                    double low = 0.0);

        std::string getTimestamp() const;

        double getOpen() const;
        double getClose() const;
        double getHigh() const;
        double getLow() const;

        void plotTextGraph(const std::vector<CandleStick>& candleSticks);

    private:
        std::string timestamp;
        double open;
        double close;
        double high;
        double low;
};

#endif
