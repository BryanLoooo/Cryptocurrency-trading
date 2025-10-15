#include "CSVReader.h"
#include <iostream>
#include <fstream>

CSVReader::CSVReader(){

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
        while(std::getline(csvFile, line))
        {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }catch(const std::exception& e)
            {
                std::cout << "CSVReader::readCSV bad data"  << std::endl;
            }
        }// end of while
    }    

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries"  << std::endl;
    return entries; 
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
   std::vector<std::string> tokens;
   signed int start, end;
   std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do{
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
    start = end + 1;
    }while(end > 0);

   return tokens; 
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    int SNo;
    double High, Low, Open, Close, Volume, Marketcap;

    if (tokens.size() < 10) {
        std::cout << "Bad line: Insufficient columns" << std::endl;
        throw std::exception{};
    }

    try {
        SNo = std::stoi(tokens[0]);
        High = std::stod(tokens[4]);
        Low = std::stod(tokens[5]);
        Open = std::stod(tokens[6]);
        Close = std::stod(tokens[7]);
        Volume = std::stod(tokens[8]);
        Marketcap = std::stod(tokens[9]);
    } catch (const std::exception& e) {
        std::cerr << "CSVReader::stringsToOBE Error converting values" << std::endl;
        throw;
    }

    OrderBookEntry obe{SNo, tokens[1], tokens[2], tokens[3], High, Low, Open, Close, Volume, Marketcap};
    return obe;
}


OrderBookEntry CSVReader::stringsToOBE(std::string SNo_String,
                                    std::string Name, 
                                    std::string Symbol,
                                    std::string Date,
                                    std::string HighString,
                                    std::string LowString,
                                    std::string OpenString,
                                    std::string CloseString,
                                    std::string VolumeString,
                                    std::string MarketCapString)
{
    int SNo;
    double High, Low, Open, Close, Volume, Marketcap;
    try {
         SNo = std::stoi(SNo_String);
         High = std::stod(HighString);
         Low = std::stod(LowString);
         Open = std::stod(OpenString);
         Close = std::stod(CloseString);
         Volume = std::stod(VolumeString);
         Marketcap = std::stod(MarketCapString);
    }catch(const std::exception& e){
        std::cout << "CSVReader::stringsToOBE Bad int! " << SNo_String<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << HighString<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << LowString<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << OpenString<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad float! " << CloseString<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad int! " << VolumeString<< std::endl; 
        std::cout << "CSVReader::stringsToOBE Bad int! " << MarketCapString<< std::endl; 

        throw;        
    }
    OrderBookEntry obe{SNo, Name, Symbol, Date, High, Low, Open, Close, Volume, Marketcap};
                
    return obe;
}
     