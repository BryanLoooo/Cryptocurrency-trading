#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>

//added these libraries
#include "Candlestick.h"
#include <unordered_set>
#include <iomanip>
#include <numeric>
#include <fstream>
#include <cmath>
#include <map>

MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while(true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}


void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue   
    std::cout << "6: Continue " << std::endl;
    // 7 print high and low values for candlestick   
    std::cout << "7: Print Market statistics for Candlesticks " << std::endl;
    // 8 print Candlestick   
    std::cout << "8: Print Candlestick " << std::endl;
    // 9 print additional candlestick 
    std::cout << "9: Print Additional Candlestick " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, 
                                                                p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;



    }
    // std::cout << "OrderBook contains :  " << orders.size() << " entries" << std::endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;
    // for (OrderBookEntry& e : orders)
    // {
    //     if (e.orderType == OrderBookType::ask)
    //     {
    //         asks ++;
    //     }
    //     if (e.orderType == OrderBookType::bid)
    //     {
    //         bids ++;
    //     }  
    // }    
    // std::cout << "OrderBook asks:  " << asks << " bids:" << bids << std::endl;

}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::ask 
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }   
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::bid 
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
        }   
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl; 
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
        
    }

    currentTime = orderBook.getNextTime(currentTime);
}
 
//This function is for part 1
void MerkelMain::printHighAndLow(OrderBook& OrderBook){
    try{
        //verify whether the function is able to get to this point
        std::cout << "Before processing" << std::endl;

        //declare a map to store all the entries
        std::map<std::string, std::vector<OrderBookEntry>> orderBookMap;

        //retrieve the user input to allow the user to have to option to choose what kind of product the user wants to view
        std::string tradingPair;
        std::cout << "Exchanges which are available:\nETH/BTC, DOGE/BTC, BTC/USDT, ETH/USDT, DOGE/USDT \nEnter the trading pair in the format (ETH/BTC) :";
        std::cin >> tradingPair;

        if(tradingPair == "ETH/BTC"){

            tradingPair == "ETH/BTC";

        }else if(tradingPair == "DOGE/BTC"){

            tradingPair == "DOGE/BTC";

        }else if(tradingPair == "BTC/USDT"){

            tradingPair == "BTC/USDT";

        }else if(tradingPair == "ETH/USDT"){

            tradingPair == "ETH/USDT";

        }else if(tradingPair == "DOGE/USDT"){

            tradingPair == "DOGE/USDT";

        }else{

            std::cerr << "Invalid product input please try again." << std::endl;
        }

        std::string orderBookTypeString;
        std::cout <<"Enter either a bid or an ask to find out more information on market statistics (ask or bid only) :";
        std::cin >> orderBookTypeString;

        OrderBookType OrderBookType;
        if(orderBookTypeString == "ask"){

            OrderBookType = OrderBookType::ask;

        }else if(orderBookTypeString == "bid"){

            OrderBookType = OrderBookType::bid;

        }else if(orderBookTypeString == "ASK"){

            OrderBookType = OrderBookType::ask;

        }else if(orderBookTypeString == "BID"){

            OrderBookType = OrderBookType::bid;

        }else{

            std::cerr << "Invalid input for bid or ask please try again." << std::endl;
        }

        //based on the user input I will use the orderbook object to retrieve those products of the particular type specified
        for(const auto& entry : OrderBook.getOrders(OrderBookType, tradingPair))
        {
            //initialise a string to store the timestamps
            std::string timestamp = entry.getTimestamp();

            orderBookMap[timestamp].push_back(entry);
        }

        //set the open value as 0
        double open = 0.0;

        std::vector<CandleStick> candleSticks;

        for(const auto& entry : orderBookMap) {

            double totalValue = 0.0;
            double totalAmount = 0.0;
            double highestPrice = std::numeric_limits<double>::lowest();
            double lowestPrice = std::numeric_limits<double>::max();

            //calculating the average price
            for(const auto& order : entry.second){

                totalValue += (order.getPrice() * order.getAmount());

                totalAmount += (order.getAmount());

                double price = order.getPrice();

                //checks to see what was the lowest and the highest price seen
                if (price > highestPrice){
                    highestPrice = price;
                }
                if(price < lowestPrice){
                    lowestPrice = price;
                }
            }

            double averagePrice = (entry.second.empty() ? 0.0 : totalValue/ totalAmount);

            //put the new calculated values into the candlestick vector
            candleSticks.emplace_back(entry.first, open, averagePrice, highestPrice, lowestPrice);

            open = averagePrice;

            std::cout << "Timestamp: " << entry.first
                      << ", Open: " << candleSticks.back().getOpen()
                      << ", Close: " << candleSticks.back().getClose()
                      << ", High: " << candleSticks.back().getHigh()
                      << ", Low: " << candleSticks.back().getLow() << std::endl;
        }
        std::cout << "After processing" << std::endl;
    } catch (const std::exception& e){
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }catch(...) {
        std::cerr << "Unknown exception caught" << std::endl;
    }
}


//This function is for part 2
void MerkelMain::printGraph(OrderBook& orderBook) 
{
    //creates a map to store values
    std::map<std::string, std::vector<OrderBookEntry>> orderBookMap;

        //retriebes the user input for what kind of products the user wants to view
        std::string tradingPair;
        std::cout << "Exchanges which are available:\nETH/BTC, DOGE/BTC, BTC/USDT, ETH/USDT, DOGE/USDT \nEnter the trading pair in the format (ETH/BTC):";
        std::cin >> tradingPair;

        if(tradingPair == "ETH/BTC"){
            tradingPair == "ETH/BTC";

        }else if(tradingPair == "DOGE/BTC"){
            tradingPair == "DOGE/BTC";

        }else if(tradingPair == "BTC/USDT"){
            tradingPair == "BTC/USDT";

        }else if(tradingPair == "ETH/USDT"){
            tradingPair == "ETH/USDT";

        }else if(tradingPair == "DOGE/USDT"){
            tradingPair == "DOGE/USDT";

        }else{
            std::cerr << "Invalid product input please try again." << std::endl;
        }

        std::string orderBookTypeString;
        std::cout <<"Enter either a bid or an ask to find out more information on market statistics (ask or bid only) :";
        std::cin >> orderBookTypeString;

        OrderBookType OrderBookType;
        if(orderBookTypeString == "ask"){
            OrderBookType = OrderBookType::ask;
        }else if(orderBookTypeString == "bid"){
            OrderBookType = OrderBookType::bid;
        }else if(orderBookTypeString == "ASK"){
            OrderBookType = OrderBookType::ask;
        }else if(orderBookTypeString == "BID"){
            OrderBookType = OrderBookType::bid;
        }else{
            std::cerr << "Invalid input for bid or ask please try again." << std::endl;
        }

    //uses and orderbook object to search for the particular product and the type of trade specified by the user
    for (const auto& entry : orderBook.getOrders(OrderBookType, tradingPair)) 
    {
        std::string timestamp = entry.getTimestamp();
        orderBookMap[timestamp].push_back(entry);
    }

    double open = 0.0;
    int linesPrinted = 0;
    const int scaleFactor = 5;
    bool differencePrinted = false;

    std::vector<CandleStick> candleSticks;
    
    for (const auto& entry : orderBookMap) 
    {
        double totalPrice = 0.0;
        double totalAmount = 0.0;
        double highestPrice = std::numeric_limits<double>::lowest();
        double lowestPrice = std::numeric_limits<double>::max();

        //boolean is being declared to check if the difference between the open and close values have already been calculated
        bool differencePrinted = false;

        for (const auto& order : entry.second) 
        {
            totalPrice += (order.getPrice() * order.getAmount());

            totalAmount += (order.getAmount());

            double price = order.getPrice();
            if (price > highestPrice) {
                highestPrice = price;
            }
            if (price < lowestPrice) {
                lowestPrice = price;
            }
        }

        double averagePrice = (entry.second.empty() ? 0.0 : totalPrice / totalAmount);

        //the candlestick vector will then store all the new values being calculated
        candleSticks.emplace_back(entry.first, open, averagePrice, highestPrice, lowestPrice);

        open = averagePrice;

        std::cout << "Timestamp: " << entry.first
                  << "\nOpen: " << candleSticks.back().getOpen() * scaleFactor
                  << "\nClose: " << candleSticks.back().getClose() * scaleFactor
                  << "\nHigh: " << candleSticks.back().getHigh() * scaleFactor
                  << "\nLow: " << candleSticks.back().getLow() * scaleFactor << std::endl;

        //the buffer is created to make spacing between each candlesticks objects being created onto the terminal
        const int buffer = 10;

        //the difference is being calculated by subtracting the open value and the close value of each candlesticks
        double difference = std::abs(candleSticks.back().getOpen() - candleSticks.back().getClose());

        //since the differences are so small I want to be able to see the difference between the open and close so I round off the to nearest 5 decimal places
        double DiffResult = std::ceil(difference * 100000) / 100000;

    //printing the candlestick object
    //this for loop looks for everytime that is a high or low value and add in the buffer
    for (int i = static_cast<int>(candleSticks.back().getHigh() * scaleFactor) + buffer;
         i >= static_cast<int>(candleSticks.back().getLow() * scaleFactor) - buffer; --i) {

        std::cout << "   ";

        //sets the open values
        if (i == static_cast<int>(candleSticks.back().getOpen() * scaleFactor)) {

            //checks if the difference has already been printed
            if (!differencePrinted) {

            //if the close is more then the open value then I will print + if not I will print -
            std::string colorOpen = (candleSticks.back().getClose() > candleSticks.back().getOpen()) ? "   \n +++++++\n" : "   \n -------\n";
            std::cout << " " << colorOpen << " ";

            //checks if the difference has already been printed
            if (!differencePrinted) {

                //as long as the difference is more then 0 and is less than 1 then I will print 1 bar if not I will find out how many more bars to print
                if (difference > 0.0 && difference <= 1.0) {
                    std::cout << "|     |" << "  difference : " << std::fixed << std::setprecision(5) << DiffResult << std::endl;
                } 
                else if (difference > 1.0) 
                {
                    std::cout << "Difference is more than 1: " << std::fixed << std::setprecision(5) << DiffResult << std::endl;
                    std::cout << "|     |" << std::endl;

                    int diffScale = static_cast<int>(difference * scaleFactor);
                    for (int j = 1; j < diffScale; ++j) {
                        std::cout << "|     |\n";
                    }
                }

                differencePrinted = true;
            }

            //this is to print the close with the symbol + or -
            std::string colorOpenEnd = (candleSticks.back().getClose() > candleSticks.back().getOpen()) ? "   \n +++++++\n" : "   \n -------\n";
            std::cout << " " << colorOpenEnd << " ";
        }
        //returns that the difference has already been printed
        differencePrinted = true;

        } else if (i == static_cast<int>(candleSticks.back().getClose() * scaleFactor)) 
        {

            if (!differencePrinted) 
            {

            double closeToLowDifference = std::abs(candleSticks.back().getClose() - candleSticks.back().getLow());

            int diffScale = static_cast<int>(closeToLowDifference * scaleFactor);

            std::string colorClose = (candleSticks.back().getClose() > candleSticks.back().getOpen()) ? "   \n +++++++\n" : "   \n -------\n";
            std::cout << " " << colorClose << " ";

            if (!differencePrinted) {

                if (difference > 0.0 && difference <= 1.0) 
                {
                    std::cout << "|     |" << "  difference : " << std::fixed << std::setprecision(5) << DiffResult << std::endl;

                } else if (difference > 1.0) {
                    std::cout << "Difference is more than 1: " << std::fixed << std::setprecision(5) << DiffResult << std::endl;
                    std::cout << "|     |" << std::endl;

                    for (int j = 1; j < diffScale; ++j) {
                        std::cout << "|     |\n";
                    }
                }
                differencePrinted = true; // Set the flag to true
            }
            std::string colorCloseEnd = (candleSticks.back().getClose() > candleSticks.back().getOpen()) ? "   \n +++++++\n" : "   \n -------\n";
            std::cout << " " << colorCloseEnd << " ";
        }

        differencePrinted = true;
        }

        else if (i == static_cast<int>(candleSticks.back().getClose() * scaleFactor)) 
        {
            std::string colorClose = (candleSticks.back().getClose() > candleSticks.back().getOpen()) ? "   \n +++++++\n" : "   \n -------\n";
            std::cout << " " << colorClose << " ";

            if (!differencePrinted) 
            {
                double closeToLowDifference = std::abs(candleSticks.back().getClose() - candleSticks.back().getLow());

                double closedDiffResult = std::ceil(difference * 100000) / 100000;
                std::cout << "Difference between Close and Low: " << std::fixed << std::setprecision(5) << closedDiffResult << std::endl;
                std::cout << "   |   " << std::endl;

                int diffScale = static_cast<int>(closeToLowDifference * scaleFactor);
                for (int j = 1; j < diffScale; ++j) 
                {
                    std::cout << "   |   \n";
                }

                differencePrinted = true;
            }
        } else {
            std::cout << "|";
        }
        std::cout << '\n';
    }

    std::cout << "==============\n";

    linesPrinted++;

    //prints only the first 10 lines of data
    if (linesPrinted >= 10) 
    {
        candleSticks.clear();
        linesPrinted = 0; 
        break;
    }
  }
}


//this is for part 3
void MerkelMain::readCandlestickData()
{
    //opening the file
    std::ifstream file("coin_Aave.csv");

    //if the file is not able to open
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    std::map<std::string, std::vector<OrderBookEntry>> orderBookMap;

    std::string line;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);

        std::string SNo_String,
            Name,
            Symbol,
            Date,
            HighString,
            LowString,
            OpenString,
            CloseString,
            VolumeString,
            MarketCapString;

        std::getline(iss, SNo_String, ',');
        std::getline(iss, Name, ',');
        std::getline(iss, Symbol, ',');
        std::getline(iss, Date, ',');
        std::getline(iss, HighString, ',');
        std::getline(iss, LowString, ',');
        std::getline(iss, OpenString, ',');
        std::getline(iss, CloseString, ',');
        std::getline(iss, VolumeString, ',');
        std::getline(iss, MarketCapString, ',');

        try {
            OrderBookEntry entry(std::stoi(SNo_String),
                Name,
                Symbol,
                Date,
                std::stod(HighString),
                std::stod(LowString),
                std::stod(OpenString),
                std::stod(CloseString),
                std::stod(VolumeString),
                std::stod(MarketCapString));

            std::string timestamp = entry.getDate();
             orderBookMap[timestamp].push_back(entry);
        }
        catch (const std::exception& e) 
        {
            std::cerr << "Error processing line: " << e.what() << std::endl;
        }
    }

    //close the file after reading it
    file.close();

    double open = 0.0;
    std::vector<CandleStick> candleSticks;

    //this scaledown is to adjust the values that are being printed out onto the console
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

        //slack is to add some distance between each candlestick that is being printed
        int slack = 10;
        
        //everytime the for loop finds that there is a high or a low value it prints it with the slack
        for (int i = static_cast<int>(candleSticks.back().getHigh() + slack);
             i >= static_cast<int>(candleSticks.back().getLow() - slack); --i) 
            {
            std::cout << "   ";

            //if close is more than open then it will take the distance between the high and the close and prints |
            if ((candleSticks.back().getClose() / scaledown) > (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i > static_cast<int>(candleSticks.back().getClose() / scaledown)) &&
                    (i < static_cast<int>(candleSticks.back().getHigh() / scaledown)))
                {
                    std::cout << "   |   ";
                }
            }

            //if the close is less than the open then the distance between the open and the high will then print |
            if ((candleSticks.back().getClose() / scaledown) < (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i > static_cast<int>(candleSticks.back().getOpen() / scaledown)) &&
                    (i < static_cast<int>(candleSticks.back().getHigh() / scaledown)))
                {
                    std::cout << "   |   ";
                }
            }

            //if the close is less then the open the it will print the bar
             if ((candleSticks.back().getClose() / scaledown) < (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i < static_cast<int>(candleSticks.back().getOpen() / scaledown)) &&
                    (i > static_cast<int>(candleSticks.back().getClose() / scaledown)))
                {
                    std::cout << "|     |";
                }
            }

            //if close is more than the open the it will print the bar
            if ((candleSticks.back().getClose() / scaledown) > (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i < static_cast<int>(candleSticks.back().getClose() / scaledown)) &&
                    (i > static_cast<int>(candleSticks.back().getOpen() / scaledown)))
                {
                    std::cout << "|     |";
                }
            }

            //if the close is less than the open the the distance between the close and low is printed as |
            if ((candleSticks.back().getClose() / scaledown) < (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i < static_cast<int>(candleSticks.back().getClose() / scaledown)) &&
                    (i > static_cast<int>(candleSticks.back().getLow() / scaledown)))
                {
                    std::cout << "   |   ";
                }
            }

            //if the close is more than the open then the distance between the open and the low is printed as |
            if ((candleSticks.back().getClose() / scaledown) > (candleSticks.back().getOpen() / scaledown)) 
            {
                if ((i < static_cast<int>(candleSticks.back().getOpen() / scaledown)) &&
                    (i > static_cast<int>(candleSticks.back().getLow() / scaledown)))
                {
                    std::cout << "   |   ";
                }
            }
            if (i == static_cast<int>(candleSticks.back().getOpen() / scaledown))
            {
                std::string colorOpen = (candleSticks.back().getClose() > candleSticks.back().getOpen()) ? "     \n   +++++++\n" : "     \n   -------\n";
                std::cout << " " << colorOpen << " ";
            } 
            else if (i == static_cast<int>(candleSticks.back().getClose() / scaledown)) 
            {
                std::string colorClose = (candleSticks.back().getClose() > candleSticks.back().getOpen()) ? "     \n   +++++++\n" : "     \n   -------\n";
                std::cout << " " << colorClose << " ";
            } 

            //the high value is being print as _
            else if (i == static_cast<int>(candleSticks.back().getHigh() / scaledown)) 
            {
                std::cout << "\n    _____ \n";
            } 

            //the low value is being printed as _
            else if (i == static_cast<int>(candleSticks.back().getLow() / scaledown)) 
            {
                std::cout << "\n    _____ \n";
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

int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-9" << std::endl;
    std::getline(std::cin, line);
    try{
        userOption = std::stoi(line);
    }catch(const std::exception& e)
    {
        // 
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-9" << std::endl;
    }
    if (userOption == 1) 
    {
        printHelp();
    }
    if (userOption == 2) 
    {
        printMarketStats();
    }
    if (userOption == 3) 
    {
        enterAsk();
    }
    if (userOption == 4) 
    {
        enterBid();
    }
    if (userOption == 5) 
    {
        printWallet();
    }
    if (userOption == 6) 
    {
        gotoNextTimeframe();
    }   
    if (userOption == 7) 
    {
        printHighAndLow(orderBook);
    }  
    if (userOption == 8) 
    {
        printGraph(orderBook);
    }  
    if (userOption == 9) 
    {
        readCandlestickData();
    }      
}
