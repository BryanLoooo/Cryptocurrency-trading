#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <unordered_set>

OrderBook::OrderBook(std::string filename) {
    orderBookEntries = CSVReader::readCSV(filename);
}

const std::vector<OrderBookEntry>& OrderBook::getOrderBookEntries() const {
    return orderBookEntries;
}