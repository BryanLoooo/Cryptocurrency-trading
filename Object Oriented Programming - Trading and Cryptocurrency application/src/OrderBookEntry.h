#pragma once

#include <string>

enum class OrderBookType{bid, ask, unknown, asksale, bidsale};

class OrderBookEntry
{
    public:
    

        OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType, 
                        std::string username = "dataset");

        OrderBookEntry( int _SNo,
                        std::string _Name, 
                        std::string _Symbol,
                        std::string _Date,
                        double _High,
                        double _Low,
                        double _Open,
                        double _Close,
                        double _Volume,
                        double _MarketCap);

        static OrderBookType stringToOrderBookType(std::string s);

        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.timestamp < e2.timestamp;
        }  
        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
         static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }
        std::string getTimestamp() const;

        double getPrice() const;

        double getAmount() const;

        std::string getDate() const;
        double getOpen() const;
        double getClose() const;
        double getHigh() const;
        double getLow() const;

        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;

        int SNo;
        std::string Name;
        std::string Symbol;
        std::string Date;
        double High;
        double Low;
        double Open;
        double Close;
        double Volume;
        double MarketCap;
};
