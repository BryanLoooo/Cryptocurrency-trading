#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>
#include <map>

class OrderBook{
    public:
        OrderBook(std::string filename);
        const std::vector<OrderBookEntry>& getOrderBookEntries() const;

    private:
        std::vector<OrderBookEntry> orderBookEntries;
};
