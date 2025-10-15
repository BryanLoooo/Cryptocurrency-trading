#ifndef ORDER_BOOK_ENTRY_H
#define ORDER_BOOK_ENTRY_H
#include <string>
#include <unordered_set>

class OrderBookEntry{
    public:
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

        std::string getDate() const;
        double getOpen() const;
        double getClose() const;
        double getHigh() const;
        double getLow() const;

};

#endif // ORDER_BOOK_ENTRY_H