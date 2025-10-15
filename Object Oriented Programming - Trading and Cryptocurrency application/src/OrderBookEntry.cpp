#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType, 
                        std::string _username)
: price(_price), 
  amount(_amount), 
  timestamp(_timestamp),
  product(_product), 
  orderType(_orderType), 
  username(_username)
{
  
    
}

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
OrderBookType OrderBookEntry::stringToOrderBookType(std::string s)
{
  if (s == "ask")
  {
    return OrderBookType::ask;
  }
  if (s == "bid")
  {
    return OrderBookType::bid;
  }
  return OrderBookType::unknown;
}

std::string OrderBookEntry::getTimestamp() const {
    return timestamp;
}

double OrderBookEntry::getPrice() const {
    return price;
}

double OrderBookEntry::getAmount() const {
    return amount;
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