#include "OrderBookEntry.h"
#include <unordered_set>

OrderBookEntry::OrderBookEntry(int _SNo,
                        std::string _Name, 
                        std::string _Symbol,
                        std::string _Date,
                        double _High,
                        double _Low,
                        double _Open,
                        double _Close,
                        double _Volume,
                        double _MarketCap)
:  SNo(_SNo),
    Name(_Name), 
    Symbol(_Symbol), 
    Date(_Date),
    High(_High),
    Low(_Low),
    Open(_Open),
    Close(_Close),
    Volume(_Volume),
    MarketCap(_MarketCap)

{
  
}

std::string OrderBookEntry::getDate() const {
    return Date;
}

double OrderBookEntry::getOpen() const {
    return Open;
}

double OrderBookEntry::getClose() const {
    return Close;
}

double OrderBookEntry::getHigh() const {
    return High;
}

double OrderBookEntry::getLow() const {
    return Low;
}
