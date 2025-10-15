#pragma once

#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader{
    public:
        CSVReader();

        static std::vector<OrderBookEntry> readCSV(std::string csvFile);
        static std::vector<std::string> tokenise(std::string csvLine, char separator);
    
        static OrderBookEntry stringsToOBE( std::string SNo, 
                                            std::string Name, 
                                            std::string Symbol, 
                                            std::string Date, 
                                            std::string High,
                                            std::string Low,
                                            std::string Open,
                                            std::string Close,
                                            std::string Volume,
                                            std::string Marketcap);

    private:
        static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};