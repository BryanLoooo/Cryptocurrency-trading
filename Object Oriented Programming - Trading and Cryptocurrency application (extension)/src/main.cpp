#include <iostream>
#include <map>
#include <vector>
#include <limits>
#include "OrderBook.h"
#include "Candlestick.h"

void printGraph(const OrderBook& orderBook) 
{
    std::map<std::string, std::vector<OrderBookEntry>> orderBookMap;

    for (const auto& entry : orderBook.getOrderBookEntries()) 
    {
        std::string timestamp = entry.getDate();
        orderBookMap[timestamp].push_back(entry);
    }

    double open = 0.0;
    std::vector<CandleStick> candleSticks;
    int scaledown = 1;

    for (const auto& entry : orderBookMap) 
    {
        double open = entry.second.front().getOpen();
        double close = entry.second.front().getClose();
        double high = entry.second.front().getHigh();
        double low = entry.second.front().getLow();

        candleSticks.emplace_back(entry.first, open, close, high, low);

        std::cout << "Timestamp: " << entry.first
                  << "\nOpen: " << candleSticks.back().getOpen() / scaledown
                  << "\nClose: " << candleSticks.back().getClose() / scaledown
                  << "\nHigh: " << candleSticks.back().getHigh() / scaledown
                  << "\nLow: " << candleSticks.back().getLow() / scaledown << std::endl;

        int slack = 10;
        

        for (int i = static_cast<int>(candleSticks.back().getHigh() + slack);
             i >= static_cast<int>(candleSticks.back().getLow() - slack); --i) 
            {
            std::cout << "   ";

            if ((candleSticks.back().getClose() / scaledown) > (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i >= static_cast<int>(candleSticks.back().getClose() / scaledown)) &&
                    (i <= static_cast<int>(candleSticks.back().getHigh() / scaledown)))
                {
                    std::cout << "*";
                }
            }
            if ((candleSticks.back().getClose() / scaledown) < (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i >= static_cast<int>(candleSticks.back().getOpen() / scaledown)) &&
                    (i <= static_cast<int>(candleSticks.back().getHigh() / scaledown)))
                {
                    std::cout << "*";
                }
            }
             if ((candleSticks.back().getClose() / scaledown) < (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i <= static_cast<int>(candleSticks.back().getOpen() / scaledown)) &&
                    (i >= static_cast<int>(candleSticks.back().getClose() / scaledown)))
                {
                    std::cout << "/";
                }
            }
            if ((candleSticks.back().getClose() / scaledown) > (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i <= static_cast<int>(candleSticks.back().getClose() / scaledown)) &&
                    (i >= static_cast<int>(candleSticks.back().getOpen() / scaledown)))
                {
                    std::cout << "/";
                }
            }
            if ((candleSticks.back().getClose() / scaledown) < (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i <= static_cast<int>(candleSticks.back().getClose() / scaledown)) &&
                    (i >= static_cast<int>(candleSticks.back().getLow() / scaledown)))
                {
                    std::cout << "&";
                }
            }
            if ((candleSticks.back().getClose() / scaledown) > (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i <= static_cast<int>(candleSticks.back().getOpen() / scaledown)) &&
                    (i >= static_cast<int>(candleSticks.back().getLow() / scaledown)))
                {
                    std::cout << "&";
                }
            }
            if (i == static_cast<int>(candleSticks.back().getOpen() / scaledown))
            {
                std::cout << "OPEN";
            } 
            else if (i == static_cast<int>(candleSticks.back().getClose() / scaledown)) 
            {
                std::cout << "CLOSE";
            } 
            else if (i == static_cast<int>(candleSticks.back().getHigh() / scaledown)) 
            {
                std::cout << "HIGH";
            } 
            else if (i == static_cast<int>(candleSticks.back().getLow() / scaledown)) 
            {
                std::cout << "LOW";
            } 
            else 
            {
                std::cout << "";
            }
            std::cout << '\n';
        }
        std::cout << "==============\n";
    }
}

int main() {
    std::string filePath = "coin_Aave.csv";
    OrderBook orderBook(filePath);

    printGraph(orderBook);

    return 0;
}
