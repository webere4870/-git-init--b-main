/*
* Authors:    
*               Elijah Weber
* Date:         November 9th, 2020
* Program:      Text-Based Pirate Adventure Game
* Description:  This game is a pirate adventure game where you set off to find a lost treasure.
*               Explore four randomly named islands in search for wealth and adventure.
*/
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>
#include <cmath>
#include <fstream>
using namespace std;

// Function Prototypes
void introduction(string playerName);
void rules();
void inventory(string item, int location);
bool startingIsland(int randomNumber, int& money, string* countryPointer, int& userPirates);
bool island2(int randomNumber, int& money, string* countryPointer, int& userPirates);
bool island3(int randomNumber, int& money, string* countryPointer, int& userPirates);
bool island4(int randomNumber, int& money, string* countryPointer, int& userPirates);
bool userInput(int numberOfDecisions, string input, int& number);
void islandEntry(int& money, int& number);
void randomCountryName(int* numberPointer, string* namePointer);
void reroute(int& money, int& userPirates);

/**
 Fight class does the following:
  1. Allows user to fight or concede a battle with pirate opponents
*/
class Fight
{
    // Information public to the main function
public:
    void displayPirates(int& initialMoney, int& userPirates);
    void fightPirates(int numPirates, int numEnemies);

    //Information accessible only in this class
private:
    int numberOfPirates = 0;
    int myPirates = 0;
    int randomMoneyGenerator = 0;
    int randomPirateGenerator = 0;
    int userMoney = 0;
    int whoWon = 0;
    bool userWin = false;
};

/**
 displayPirates function does the following:
  1. Randomly generates both the amount of enemy pirates and enemy loot
  2. Displays the amount of shipmates/money that was won/lost
 @param initialMoney - The amount of money the user currently has
 @param userPirates - The amount of shipmates the user currently has
 @return N/A
 */
void Fight::displayPirates(int& initialMoney, int& userPirates)
{
    cout << endl << "Oh no! A crewmate has spotted a group of enemy pirates out in the abyss!" << endl << endl;
    randomMoneyGenerator = rand() % initialMoney + (initialMoney / 2);
    randomPirateGenerator = rand() % userPirates + (userPirates - (userPirates / 2));
    cout << "Overwatch counts the following number of enemy pirates: " << randomPirateGenerator << endl;
    cout << "Intel says that they have this many coins: " << randomMoneyGenerator << endl;
    cout << endl << "You have the following number of pirates: " << userPirates << endl;
    cout << "You have the following amount of coins: " << initialMoney << endl;
    string input = "";
    int numberOfChoice = 0;
    bool isValid = false;
    int numberOfDecisions = 2;
    cout << endl << "You have the following options: " << endl;
    cout << "1. Fight until the death (Losing = lose half of your money and several crewmates...Winning = steal all their money!)" << endl;
    cout << "2. Give in to their demands and forfeit half of the money and several crewmates on board your ship." << endl;
    cout << "Type 1 to fight, 2 to surrender: ";
    cin >> input;
    isValid = userInput(numberOfDecisions, input, numberOfChoice);
    while (isValid == false)
    {
        cout << "Type 1 to fight, 2 to surrender: ";
        cin >> input;
        isValid = userInput(numberOfDecisions, input, numberOfChoice);
    }
    cout << endl;
    switch (numberOfChoice)
    {
    case 1: fightPirates(userPirates, randomPirateGenerator);
        if (userWin == true)
        {
            cout << "Congratulations, matey! You reign victorious!" << endl;
            cout << "You have stolen this many coins: " << randomMoneyGenerator << endl;
            initialMoney = initialMoney + randomMoneyGenerator;
        }
        else
        {
            if (userPirates == 1)
            {
                userPirates = userPirates - 1;
                initialMoney = initialMoney / 2;
                cout << "Oh no, matey! You have lost!" << endl;
                cout << "You have been robbed of " << initialMoney << " coins and lost " << userPirates + 1 << " crewmate! " << endl;
                userPirates = 0;
            }
            else
            {
                initialMoney = initialMoney / 2;
                cout << "Oh no, matey! You have lost!" << endl;
                cout << "You have been robbed of " << initialMoney << " coins and lost " << userPirates / 2 << " crewmates! " << endl;
                userPirates = userPirates - (userPirates / 2);
            }
        }
        break;
    case 2:
        if (userPirates == 1)
        {
            initialMoney = initialMoney / 2;
            userPirates = userPirates - 1;
            cout << "You have forfeited " << initialMoney << " coins and 1 of your men." << endl;
        }
        else
        {
            initialMoney = initialMoney / 2;
            userPirates = userPirates - (userPirates / 2);
            cout << "You have forfeited " << initialMoney << " coins and " << userPirates << " of your men." << endl;
        }

        break;
    }
    cout << "You have this many soldiers pirates remaining: " << userPirates << endl;
    cout << "You have this many coins remaining: " << initialMoney << endl << endl;
}

/**
 fightPirates function does the following:
  1. Determines the outcome of the skirmish
 @param numPirates - The number of shipmates
 @param numEnemies - The number of enemy pirates
 @return N/A
 */
void Fight::fightPirates(int numPirates, int numEnemies)
{
    if (numPirates < numEnemies)
    {
        whoWon = rand() % 3 + 1;
        if (whoWon == 1)
        {
            userWin = true;
        }
        else
        {
            userWin = false;
        }
    }
    else if (numPirates > numEnemies)
    {
        whoWon = rand() % 3 + 1;
        if (whoWon == 1 || whoWon == 2)
        {
            userWin = true;
        }
        else
        {
            userWin = false;
        }
    }
    else
    {
        whoWon = rand() % 2 + 1;
        if (whoWon == 1)
        {
            userWin = true;
        }
        else
        {
            userWin = false;
        }
    }
}


/**
 Roulette class does the following:
  1. Lets people choose a game type
  2. Allows them to play until they want to quit or they lose all their money
 */
class Roulette
{

    // Information public to the main function
public:
    Roulette();
    Roulette(int& money);
    void displayGameInformation();
    void playGame();
    void redOrBlack();
    void oddOrEven();
    void highOrLow();
    void dozenBet();
    int earnings(int newFactorial);   // Returns earnings or losses
    void getBet();
    void winnerOrLoser();
    void getRandomNumbers();
    void clearVectors();
    int returnMoney();

    //Information accessible only in this class
private:
    int moneyAmount = 0;
    int numberOfRandomNumbers = 0;
    int numberRange = 0;
    int userInput = 0;
    int wager = 0;
    int CPUnumber = 0;
    int gameType = 0;
    int factorial = 0;
    int winnings = 0;

    string validator = "";
    string redBlack = "";
    string oddEven = "";

    bool quitGame = false;
    char validationChar = ' ';
    bool isValidEntry = false;
    bool isWinner = false;
    bool isValidRandom = false;

    vector<int> randomNumbersVector;   // Random number storage
    vector<int> userInputVector;    // User input storage
};


/**
 Roulette function does the following:
  1. Default constructor
 @param N/A
 @return N/A
 */
Roulette::Roulette()
{
}

/**
 Roulette function does the following:
  1. Initializes money account
 @param money
 @return N/A
 */
Roulette::Roulette(int& money)
{
    moneyAmount = money;
}

/**
 Roulette function does the following:
  1. Initializes money account
 @param money
 @return N/A
 */
int Roulette::returnMoney()
{
    return moneyAmount;
}

/**
 displayGameInformation function does the following:
  1. Displays game info
 @param N/A
 @return N/A
 */
void Roulette::displayGameInformation()
{
    cout << "Welcome to the Roulette table! " << endl <<
        "Winning a round will cause a factorial of your betting amount. " << endl <<
        "Losing a round will result in the loss of your wager!" << endl << endl;
    playGame();
}


/**
 playGame function does the following:
  1. This is the main function for the user playing at the Roulette table
 @param N/A
 @return N/A
 */
void Roulette::playGame()
{
    // Plays the game until money = 0 or the user wants to quit
    while (quitGame == false && moneyAmount > 0)
    {

        // Read in what game they want to play
        cout << "Game types: " << endl << "1 = Red or Black" << endl <<
            "2 = Even or Odd" << endl <<
            "3 = High or Low" << endl <<
            "4 = By the Dozen" << endl << "Enter valid game type: ";

        // Read in input and validate
        cin >> validator;
        isValidEntry = true;


        // Validates entry
        for (int counter = 0; counter < validator.length(); counter++)
        {
            validationChar = validator[counter];
            if (!isalnum(validationChar))
            {
                isValidEntry = false;
            }
        }

        // Try catch taken from http://www.cplusplus.com/forum/beginner/253696/
        try
        {
            if (isValidEntry == true)
            {
                gameType = stoi(validator);
            }
        }
        catch (...)
        {
            cout << "Whoops!";
        }

        // Executes until valid value is entered
        while (isValidEntry == false || gameType > 4 || gameType < 1 || validator.length() > 1)
        {

            // Repeat code
            cout << endl << "Invalid entry." << endl << endl;
            cout << "Game types: " << endl << "1 = Red or Black" << endl <<
                "2 = Even or Odd" << endl <<
                "3 = High or Low" << endl <<
                "4 = By the Dozen" << endl << "Enter valid game type: ";
            cin >> validator;

            isValidEntry = true;

            for (int counter = 0; counter < validator.length(); counter++)
            {
                validationChar = validator[counter];
                if (!isalnum(validationChar))
                {
                    isValidEntry = false;
                }
            }

            // Repeat validation
            try
            {
                if (isValidEntry == true)
                {
                    gameType = stoi(validator);
                }
            }
            catch (...)
            {
                cout << "Whoops!";
            }

        }

        // Determines which game to be played
        switch (gameType)
        {
        case 1:redOrBlack();
            break;
        case 2:oddOrEven();
            break;
        case 3:highOrLow();
            break;
        case 4:dozenBet();
            break;
        };

        // Play again
        if (moneyAmount > 0)
        {
            cout << "Would you like to keep playing? " << endl <<
                "Type Y for yes, and any other button to pay your entry to the island: ";
            cin >> validationChar;
        }


        if (validationChar == 'Y' || validationChar == 'y')
        {
            quitGame = false;
        }
        else
        {
            quitGame = true;
        }
        cout << endl;
    }
}


/**
redOrBlack function does the following:
  1. Reads in user input
  2. Gets a random number and determines if the player won
 @param N/A
 @return N/A
 */
void Roulette::redOrBlack()
{
    // Reset information
    numberOfRandomNumbers = 1;
    numberRange = 2;
    isWinner = false;
    int counter = 0;
    int temporary = 0;

    // Get wager
    getBet();
    factorial = wager;

    // Executes until number of necessary inputs are received
    while (counter < numberOfRandomNumbers)
    {
        // User input
        cout << "Type 1 for Red, 2 for Black: ";
        cin >> validator;
        isValidEntry = true;

        // Validation
        for (int counter = 0; counter < validator.length(); counter++)
        {
            validationChar = validator[counter];
            if (!isalnum(validationChar))
            {
                isValidEntry = false;
            }
        }

        // Repeat validation
        try
        {
            if (isValidEntry == true)
            {
                userInput = stoi(validator);
            }
        }
        catch (...)
        {
            cout << "Whoops!";
        }


        // More validation
        while (isValidEntry == false || userInput > 2 || userInput < 1)
        {

            cout << endl << "Invalid entry." << endl << endl;
            cout << "Type 1 for Red, 2 for Black: ";
            cin >> validator;

            isValidEntry = true;

            // Validation
            for (int counter = 0; counter < validator.length(); counter++)
            {
                validationChar = validator[counter];
                if (!isalnum(validationChar))
                {
                    isValidEntry = false;
                }
            }

            // Try catch method
            try
            {
                if (isValidEntry == true)
                {
                    userInput = stoi(validator);
                }
            }
            catch (...)
            {
                cout << "Whoops!";
            }
        }

        // Add user input to the vector
        userInputVector.push_back(userInput);
        counter++;
    }

    // Gets random numbers
    cout << endl << "The house rolls the following: " << endl;
    for (int counter = 0; counter < numberOfRandomNumbers; counter++)
    {
        getRandomNumbers();
        randomNumbersVector.push_back(CPUnumber);
    }

    // Determines win or loss
    winnerOrLoser();
    if (isWinner == true)
    {
        cout << "You have won! The house spun the following: ";
        switch (randomNumbersVector[0])
        {
        case 1: redBlack = "Red";
            break;
        case 2: redBlack = "Black";
        }

        // Winner
        cout << redBlack << endl << endl;
        winnings = earnings(wager);
        cout << "Number of coins won: " << winnings << endl;
        moneyAmount = moneyAmount + winnings;

    }

    // Loser
    else
    {
        cout << "Oops! You have lost! The house spun the following: ";
        switch (randomNumbersVector[0])
        {
        case 1: redBlack = "Red";
            break;
        case 2: redBlack = "Black";
        }

        cout << redBlack << endl << endl;
        moneyAmount = moneyAmount - (wager);
        cout << "Your losses: " << (wager) << endl;

    }

    cout << "Coins remaining: ";
    cout << moneyAmount << endl << endl;

    clearVectors();
}


/**
 oddOrEven function does the following:
  1. Reads in user input
  2. Gets a random number and determines if the player won
 @param N/A
 @return N/A
 */
void Roulette::oddOrEven()
{

    // Reset information
    numberOfRandomNumbers = 1;
    numberRange = 2;
    isWinner = false;
    int counter = 0;

    // Get wager
    getBet();
    factorial = wager;

    // Until number of random numbers are reached
    while (counter < numberOfRandomNumbers)
    {

        cout << "Type 1 for Odd, 2 for Even: ";
        cin >> validator;
        isValidEntry = true;

        // Validation similar to previous function
        for (int counter = 0; counter < validator.length(); counter++)
        {
            validationChar = validator[counter];
            if (!isalnum(validationChar))
            {
                isValidEntry = false;
            }
        }


        // More validation
        try
        {
            if (isValidEntry == true)
            {
                userInput = stoi(validator);
            }
        }
        catch (...)
        {
            cout << "Whoops!";
        }


        // Validation
        while (isValidEntry == false || userInput > 2 || userInput < 1)
        {


            cout << endl << "Invalid entry." << endl << endl;
            cout << "Type 1 for Odd, 2 for Even: ";
            cin >> validator;
            isValidEntry = true;

            for (int counter = 0; counter < validator.length(); counter++)
            {
                validationChar = validator[counter];
                if (!isalnum(validationChar))
                {
                    isValidEntry = false;
                }
            }


            try
            {
                if (isValidEntry == true)
                {
                    userInput = stoi(validator);
                }
            }
            catch (...)
            {
                cout << "Whoops!";
            }
        }


        // Add input to vector
        userInputVector.push_back(userInput);
        counter++;

    }

    // Shown in other functions
    for (int counter = 0; counter < numberOfRandomNumbers; counter++)
    {
        getRandomNumbers();
        randomNumbersVector.push_back(CPUnumber);
    }


    // Shown in other functions
    winnerOrLoser();
    if (isWinner == true)
    {
        cout << "You have won! The house spun the following: ";
        switch (randomNumbersVector[0])
        {
        case 1: redBlack = "Odd";
            break;
        case 2: redBlack = "Even";
        }

        // Shown in other functions
        cout << redBlack << endl << endl;
        winnings = earnings(factorial);
        cout << "Number of coins won: " << winnings << endl;
        moneyAmount = moneyAmount + winnings;

    }
    else
    {
        cout << "Oops! You have lost! The house spun the following: ";
        switch (randomNumbersVector[0])
        {
        case 1: redBlack = "Odd";
            break;
        case 2: redBlack = "Even";
        }

        // Shown in other functions
        cout << redBlack << endl << endl;
        moneyAmount = moneyAmount - (wager);
        cout << "Your losses: " << (wager) << endl;
    }

    // Shown in other functions
    cout << "Money remaining: ";
    cout << moneyAmount << endl << endl;
    clearVectors();
}


/**
 highOrLow function does the following:
  1. Reads in user input
  2. Gets a random number and determines if the player won
 @param N/A
 @return N/A
 */
void Roulette::highOrLow()
{

    // Shown in other functions
    numberOfRandomNumbers = 1;
    numberRange = 36;
    isWinner = false;
    int highToLowNumber = 0;
    int counter = 0;
    getBet();
    factorial = wager;

    // Shown in other functions
    while (counter < numberOfRandomNumbers)
    {

        // Gets a value for high or low
        cout << "Type 1 for Low (1-18), 2 for High (19-36): ";
        cin >> validator;
        isValidEntry = true;


        // Shown in other functions
        for (int counter = 0; counter < validator.length(); counter++)
        {
            validationChar = validator[counter];
            if (!isalnum(validationChar))
            {
                isValidEntry = false;
            }
        }


        // Shown in other functions
        try
        {
            if (isValidEntry == true)
            {
                userInput = stoi(validator);
            }
        }
        catch (...)
        {
            cout << "Whoops!";
        }


        // Shown in other functions
        while (isValidEntry == false || userInput > 2 || userInput < 1)
        {

            cout << endl << "Invalid entry." << endl << endl;
            cout << "Type 1 for Low (1-18), 2 for High (19-36): ";
            cin >> validator;
            isValidEntry = true;

            // Shown in other functions
            for (int counter = 0; counter < validator.length(); counter++)
            {
                validationChar = validator[counter];
                if (!isalnum(validationChar))
                {
                    isValidEntry = false;
                }
            }


            // Shown in other functions
            try
            {
                if (isValidEntry == true)
                {
                    userInput = stoi(validator);
                }
            }
            catch (...)
            {
                cout << "Whoops!";
            }
        }

        // Determines if the random number is high or low
        userInputVector.push_back(userInput);
        if (userInputVector[counter] <= 18)
        {
            highToLowNumber = 1;
        }
        else
        {
            highToLowNumber = 2;
        }
        counter++;
    }


    // Determines what has been rolled
    cout << endl << "The house rolled the following: ";
    for (int counter = 0; counter < numberOfRandomNumbers; counter++)
    {
        getRandomNumbers();
        randomNumbersVector.push_back(CPUnumber);
        cout << randomNumbersVector[counter];
    }


    cout << endl;

    // Determines winner
    if (userInput == highToLowNumber)
    {
        isWinner = false;
    }
    else
    {
        isWinner = true;
    }

    // Shown in other functions
    if (isWinner == true)
    {
        cout << "You have won!";
        winnings = earnings(factorial);
        cout << "Your winnings: " << winnings << endl;
        moneyAmount = moneyAmount + winnings;
    }
    else
    {
        cout << "Oops! You have lost! The house spun the following: ";
        moneyAmount = moneyAmount - (wager);
        cout << "Your losses: " << (wager) << endl;
    }

    // Shown in other functions
    cout << "Coins remaining: ";
    cout << moneyAmount << endl << endl;
    clearVectors();
}


/**
 dozenBet function does the following:
  1. Reads in 12 user inputs
  2. Gets 12 random numbers and determines if the player won
 @param N/A
 @return N/A
 */
void Roulette::dozenBet()
{
    // Shown in other functions
    numberOfRandomNumbers = 12;
    numberRange = 36;
    isWinner = false;
    int counter = 0;

    // Request 12 numbers
    getBet();
    factorial = wager;
    cout << "You must now enter a dozen numbers." << endl;

    // Executes while counter is less than 12
    while (counter < numberOfRandomNumbers)
    {
        cout << "Enter number " << counter + 1 << ": ";
        cin >> validator;
        isValidEntry = true;


        // Validates each digit
        for (int counter = 0; counter < validator.length(); counter++)
        {
            validationChar = validator[counter];
            if (!isalnum(validationChar))
            {
                isValidEntry = false;
            }
        }

        // Shown in other functions
        try
        {
            if (isValidEntry == true)
            {
                userInput = stoi(validator);
                for (int counter = 0; counter < userInputVector.size(); counter++)
                {
                    if (userInput == userInputVector[counter])
                    {
                        isValidEntry = false;
                    }
                }
            }
        }
        catch (...)
        {
            cout << "Whoops!";
        }


        // Shown in other functions
        while (isValidEntry == false || userInput > 36 || userInput < 1)
        {

            cout << endl << "Invalid entry." << endl << endl;
            cout << "Enter number " << counter + 1 << ": ";
            cin >> validator;
            isValidEntry = true;

            // Shown in other functions
            for (int counter = 0; counter < validator.length(); counter++)
            {
                validationChar = validator[counter];
                if (!isalnum(validationChar))
                {
                    isValidEntry = false;
                }
            }

            // Shown in other functions
            try
            {
                if (isValidEntry == true)
                {
                    userInput = stoi(validator);
                    for (int counter = 0; counter < userInputVector.size(); counter++)
                    {
                        if (userInput == userInputVector[counter])
                        {
                            isValidEntry = false;
                        }
                    }
                }
            }
            catch (...)
            {
                cout << "Whoops!";
            }
        }

        // Add user input to vector
        userInputVector.push_back(userInput);
        counter++;
    }

    // Display random numbers rolled
    cout << endl << "The house rolled the following: ";
    for (int counter = 0; counter < numberOfRandomNumbers; counter++)
    {
        // Assume false
        isValidRandom = false;

        // Get random numbers until its valid
        while (isValidRandom == false)
        {

            // Random number
            CPUnumber = rand() % numberRange + 1;
            isValidRandom = true;

            // Determine if false
            for (int counter = 0; counter < randomNumbersVector.size(); counter++)
            {
                if (randomNumbersVector[counter] == CPUnumber)
                {
                    isValidRandom = false;
                }
            }
        }

        // Add random number to vector
        randomNumbersVector.push_back(CPUnumber);
        cout << randomNumbersVector[counter] << " ";

        // Check for a match
        for (int internalCounter = 0; internalCounter < randomNumbersVector.size(); internalCounter++)
        {
            if (userInputVector[internalCounter] == randomNumbersVector[counter])
            {
                isWinner = true;
            }
        }
    }


    cout << endl;
    // Shown in other functions
    if (isWinner == true)
    {
        cout << "You have won!";
        winnings = earnings(factorial);
        cout << "Your winnings: " << winnings << endl;
        moneyAmount = moneyAmount + winnings;
    }
    else
    {
        cout << "Oops! You have lost! The house spun the following: ";
        moneyAmount = moneyAmount - (wager);
        cout << "Your losses: " << (wager) << endl;
    }


    cout << "Money remaining: ";
    cout << moneyAmount << endl << endl;


    clearVectors();
}


/**
 earnings function does the following:
  1. Reads in the betting amount
  2. Factorials that number using recursion
 @param newFactorial (wager amount)
 @return N/A
 */
int Roulette::earnings(int newFactorial)
{
    if (newFactorial > 1)
    {
        return newFactorial * earnings(newFactorial - 1);
    }
    else
    {
        return 1;
    }
}


/**
 getBet function does the following:
  1. Reads in user inputm for the bet amount
  2. Determines if that value can be factorialed
 @param N/A
 @return N/A
 */
void Roulette::getBet()
{

    // Get wager
    int temporary = 0;
    cout << "How much money would you like to bet? (All bets must be $6 and under due to factorialization): ";
    cin >> validator;
    isValidEntry = true;


    // Shown in other functions
    for (int counter = 0; counter < validator.length(); counter++)
    {
        validationChar = validator[counter];
        if (!isalnum(validationChar))
        {
            isValidEntry = false;
        }
    }


    // Shown in other functions
    try
    {
        if (isValidEntry == true)
        {
            wager = stoi(validator);
            temporary = wager;
        }
    }
    catch (...)
    {
        cout << "Whoops!";
    }


    // Shown in other functions
    while (isValidEntry == false || wager > moneyAmount || wager < 0 || wager > 6)
    {

        // Number cannot be factorialed with given amount of money
        cout << endl << "Invalid entry." << endl << endl;
        cout << "How much money would you like to bet? ";
        cin >> validator;
        isValidEntry = true;

        // Shown in other functions
        for (int counter = 0; counter < validator.length(); counter++)
        {
            validationChar = validator[counter];
            if (!isalnum(validationChar))
            {
                isValidEntry = false;
            }
        }

        // Shown in other functions
        try
        {
            if (isValidEntry == true)
            {
                wager = stoi(validator);
                temporary = wager;
            }
        }
        catch (...)
        {
            cout << "Whoops!";
        }
    }
}

/**
 winnerOrLoser function does the following:
  1. Enters a nested for loop to determine if the user has won or not
 @param N/A
 @return N/A
 */
void Roulette::winnerOrLoser()
{
    for (int outside = 0; outside < numberOfRandomNumbers; outside++)
    {
        for (int inside = 0; inside < numberOfRandomNumbers; inside++)
        {
            if (userInputVector[outside] == randomNumbersVector[inside])
            {
                isWinner = true;
            }
        }
    }
}


/**
 getRandomNumbers function does the following:
  1. Gets the necessary number of random numbers for the given game
 @param N/A
 @return N/A
 */
void Roulette::getRandomNumbers()
{

    // Number outside of range
    CPUnumber = -1;
    isValidRandom = false;

    // Gets random numbers that haven't been pulled before
    while (isValidRandom == false)
    {

        // Random
        CPUnumber = rand() % numberRange + 1;
        isValidRandom = true;

        // Random
        for (int counter = 0; counter < randomNumbersVector.size(); counter++)
        {
            if (randomNumbersVector[counter] == CPUnumber)
            {
                isValidRandom = false;
            }
        }
    }

}


/**
 clearVectors function does the following:
  1. Resets the vectors in case the user wants to play again
 @param N/A
 @return N/A
 */
void Roulette::clearVectors()
{
    for (int counter = 0; counter < numberOfRandomNumbers; counter++)
    {
        randomNumbersVector.pop_back();
        userInputVector.pop_back();
    }
}


int main()
{
    srand(time(0));
    string playAgain = "";

    do
    {
        // Initial Variables: 
        string playerName;
        string input = "";
        int island = 0;
        int userMoney = 1000;
        int userPirates = 0;
        bool isTreasureFound = false;
        string item;
        bool isValid = false;
        int islandTreasureLocation = rand() % 4 + 1;
        int randomCountryPointer[4];
        string randomNamePointer[4];

        cout << "Enter pirate name: ";
        getline(cin, playerName);
        introduction(playerName);
        rules();
        cout << "You are starting this journey with the following number of gold coins: " << userMoney << endl;
        while (isValid == false || userPirates >= 20 || userPirates < 1)
        {
            cout << "How many pirates would you like on your crew (50 coins per pirate): ";
            cin >> input;
            isValid = userInput(20, input, userPirates);
        }
        userMoney = userMoney - (userPirates * 50);
        cout << "Money remaining: " << userMoney << endl;
        cout << "Number of crewmates: " << userPirates << endl << endl;

        while (userMoney > 0 && userPirates > 0 && isTreasureFound == false)
        {
            string validation = "";
            int userNumber = 0;
            bool validInput = false;
            int numberOfDecisions = 0;
            while (validInput == false)
            {
                numberOfDecisions = 4;
                cout << "Where would you like to move? 1 = North, 2 South, 3 = East, 4 = West ";
                cin >> validation;
                validInput = userInput(numberOfDecisions, validation, userNumber);
            }
            Fight newFight;
            newFight.displayPirates(userMoney, userPirates);
            if (userMoney == 0 || userPirates == 0)
            {
                break;
            }
            randomCountryName(randomCountryPointer, randomNamePointer);                                                     // gives the island a random name from a list of countries
            switch (userNumber)                                                                                             // calls the function for the island that they want to go to
            {
            case 1: isTreasureFound = startingIsland(islandTreasureLocation, userMoney, randomNamePointer, userPirates);
                break;
            case 2: isTreasureFound = island2(islandTreasureLocation, userMoney, randomNamePointer, userPirates);
                break;
            case 3: isTreasureFound = island3(islandTreasureLocation, userMoney, randomNamePointer, userPirates);
                break;
            case 4: isTreasureFound = island4(islandTreasureLocation, userMoney, randomNamePointer, userPirates);
                break;
            }
        }

        if (userPirates == 0)
        {
            cout << "Looks like all your men have been killed!" << endl;
        }

        if (userMoney == 0)
        {
            cout << "Looks like you have lost all your money!" << endl;
        }

        if (isTreasureFound == false)
        {
            cout << "Better luck next time!" << endl << endl;
        }
        cout << "Type Y to play again, any other button to quit: ";
        cin >> playAgain;
    } while (playAgain == "Y" || playAgain == "y");

}

struct EnemyInformation
{
    int numberOfSoldiers = 0;
    int pirateMoney = 0;
};

/**
 introduction function does the following:
  1. Introduces the user to the game
  2. Displays the overall goal
 @param playerName - user- inputted name
 @return N/A
 */
void introduction(string playerName)
{
    cout << "ARRRRRGG, welcome to pirate island. The Pirate Adventure Game!!" << endl;
    cout << "In this advetnure you will set off to find treasure with your mighty pirate crew." << endl;
    cout << "Mangage your crew and money as you explore each island trying to find the lost treasure of Davy Jones." << endl;
    cout << "Each island will bring with it challenegs, riches, and unexpected friends that can help you along the way" << endl;
    cout << "but remember if you lose all your money or if all your crew members get lost at sea you will lose the game and any hope of finding Davy Jone's treasure." << endl;
    cout << "Best of luck " << playerName << ", may the luck of the sea be in your favor" << endl;
    cout << "AAARRRRRRGGGGG!" << endl << endl;
}

/**
 rules function does the following:
  1. Displays rules of the game
  2. Displays the overall goal
 @param N/A
 @return N/A
 */
void rules()
{
    cout << "If you are going to survive the stormy seas you will need to know the rules." << endl;
    cout << "Rule 1: Beside each question or line of text enter a valid response." << endl;
    cout << "Rule 2: You will have several options at each island of which you are free to choose any option given." << endl;
    cout << "Rule 3: There will be several ways to gain crewmates and money but also ways to lose them." << endl;
    cout << "Rule 4: If you lose all your money, or all your crew members you lose the game." << endl;
    cout << "Rule 5: If you find Davy Jone's treasure you win!" << endl << endl;
}

/**
 islandEntry function does the following:
  1. Creates a higher price than the player has to enter the island (forces user to use roulette)
  2. Allows user to leave the island or head to the roulette table
 @param money - The amount of money the user currently has
 @param number - Island location
 @return N/A
 */
void islandEntry(int& money, int& number)
{
    int cost = money + money / 5;
    int numberOfDecisions = 2;
    string input = "";
    bool isValid = false;
    do
    {
        cout << "Wish to enter the island aye? It's gonna cost you." << endl;
        cout << "Number of coins required for entry: " << cost << endl;
        cout << "Your current number of coins: " << money << endl << endl;
        cout << "Looks like you need some cash. Type 1 to enter the roulette table, 2 to sail elsewhere: ";
        cin >> input;
        isValid = userInput(numberOfDecisions, input, number);
        while (isValid == false)
        {
            cout << "Looks like you still need some cash. Type 1 to enter the roulette table, 2 to sail elsewhere: ";
            cin >> input;
            userInput(numberOfDecisions, input, number);
        }
        if (number == 1)
        {
            Roulette newGame(money);
            newGame.displayGameInformation();
            newGame.playGame();
            money = newGame.returnMoney();
        }
        else
        {
            break;
        }
    } while (cost > money && money > 0);
    if (number == 1 && money > 0)
    {
        money = money - cost;
    }
    if (money > 0)
    {
        cout << "Coins remaining: " << money << endl;
    }
    return;
}

/**
 inventory function does the following:
  1. Stores items found by the user into an array
 @param item - unique items found by the user
 @param location - user location where item was found
 @return N/A
 */
void inventory(string item, int location)
{
    string backpack[7];
    backpack[location] = item;
    cout << endl << "inventory" << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << i + 1 << "." << backpack[i] << endl;
    }
}

/**
 userInput function does the following:
  1. Validates user input throughout the game
 @param numberOfDecisions - The amount of paths the user has to choose from
 @param input - user's input (in regard to what choice they want to choose)
 @param number -
 @return isValidEntry - either true or false (if true the input is valid, if false the input is not valid)
 */
bool userInput(int numberOfDecisions, string input, int& number)
{
    int temporary = 0;
    char validationChar = ' ';
    bool isValidEntry = true;

    // Shown in other functions
    for (int counter = 0; counter < input.length(); counter++)
    {
        validationChar = input[counter];
        if (!isalnum(validationChar))
        {
            isValidEntry = false;
        }
    }


    // Shown in other functions
    try
    {
        if (isValidEntry == true)
        {
            number = stoi(input);
        }
    }
    catch (...)
    {
        cout << "Whoops!";
        isValidEntry = false;
    }

    try
    {
        if (isValidEntry == false || number > numberOfDecisions || number < 1)
        {
            isValidEntry = false;
            // Number cannot be factorialed with given amount of money
            cout << endl << "Invalid entry." << endl << endl;
        }
        else
        {
        }
    }
    catch (...)
    {
        cout << "Whoops! Invalid Entry" << endl;
        isValidEntry = false;
    }
    // Shown in other functions
    return isValidEntry;
}

/**
 startingIsland function does the following:
  1. Requires user to spend 75% of their current money or leave the island
  2. Checks if the user has won the game
 @param randomNumber -
 @param money - user's current money amount
 @param countryPointer - randomly selected island name
 @param userPirates - user's current pirate amount
 @return isFound - either true or false (if true, the treasure is found, if false the treasure has not been found)
 */
bool startingIsland(int randomNumber, int& money, string* countryPointer, int& userPirates)
{
    string shipName;
    bool isFound = false;
    bool isValid = false;
    int number = 0;
    cout << "Captain, look ahead! We see an island off in the distance! Lets dock there and check it out!" << endl << endl;
    islandEntry(money, number);
    string input = "";
    if (money == 0 || number == 2)
    {
        return isFound;
    }


    cout << "Welcome to " << countryPointer[1] << "!" << endl;
    cout << "you seemed to have arived at a small coastal town on the edge of a little jungle" << endl;
    cout << endl << "You have received word from the locals that there could be treasure somewhere on the island." << endl;
    cout << "You have the following options: " << endl;
    cout << "1. Continue to search the island, requiring you to spend 75% of your money on more supplies" << endl;
    cout << "2. Leave the island and sail elsewhere" << endl;


    while (isValid == false)
    {
        cout << "Type 1 to stay, 2 to leave: " << endl;
        cin >> input;
        isValid = userInput(2, input, number);
    }
    if (number == 1)
    {
        money = money / 4;
        if (randomNumber == 1)
        {
            isFound = true;
            cout << "You have found the hidden treasure! You have won the game!" << endl;
        }
        else
        {
            cout << "Oops, you found no treasure on this island!" << endl;
            cout << "Coins remaining: " << money << endl;
        }
    }
    return isFound;
}

/**
 island2 function does the following:
  1. Requires user to spend 75% of their current money or leave the island
  2. Checks if the user has won the game
 @param randomNumber -
 @param money - user's current money amount
 @param countryPointer - randomly selected island name
 @param userPirates - user's current pirate amount
 @return isFound - either true or false (if true, the treasure is found, if false the treasure has not been found)
 */
bool island2(int randomNumber, int& money, string* countryPointer, int& userPirates)
{
    string shipName;
    bool isFound = false;
    bool isValid = false;
    int number = 0;
    cout << "Captain, look ahead! We see an island off in the distance! Lets dock there and check it out!" << endl << endl;
    islandEntry(money, number);
    string input = "";
    if (money == 0 || number == 2)
    {
        return isFound;
    }


    cout << "Welcome to " << countryPointer[2] << "!" << endl;

    cout << endl << "You arrive on a small sandy island with one massive palm tree in the center." << endl;
    cout << "You have the following options: " << endl;
    cout << "1. Search the island, requiring you to spend 75% of your money on more supplies" << endl;
    cout << "2. Leave the island and sail elsewhere" << endl;


    while (isValid == false)
    {
        cout << "Type 1 to stay, 2 to leave: " << endl;
        cin >> input;
        isValid = userInput(2, input, number);
    }
    if (number == 1)
    {
        money = money / 4;
        if (randomNumber == 2)
        {
            isFound = true;
            cout << "You have found the hidden treasure! You have won the game!" << endl;
        }
        else
        {
            cout << "Oops, you found no treasure on this island!" << endl;
            cout << "Coins remaining: " << money << endl;
        }
    }
    return isFound;
}
/**
 island3 function does the following:
  1. Has the user decide to enter the forest or continue on
  2. Entering the forest can lead to the user losing half of their shipmates or doubling their money
  3. Requires user to spend 75% of their current money or leave the island
  4. Checks if the has won the game
 @param randomNumber -
 @param money - user's current money amount
 @param countryPointer - randomly selected island name
 @param userPirates - user's current pirate amount
 @return isFound - either true or false (if true, the treasure is found, if false the treasure has not been found)
 */
bool island3(int randomNumber, int& money, string* countryPointer, int& userPirates)
{
    string shipName;
    bool isFound = false;
    bool isValid = false;
    int number = 0;
    cout << "Captain, look ahead! We see an island off in the distance! Lets dock there and check it out!" << endl << endl;
    islandEntry(money, number);
    string input = "";
    if (money == 0 || number == 2)
    {
        return isFound;
    }


    cout << "Welcome to " << countryPointer[3] << "!" << endl;

    cout << "As you beach on the island of " << countryPointer[3] << ", you see an oldly placed neon sign entitled 'Bob's Place' in front of a small forest." << endl;
    while (isValid == false)
    {
        cout << "Do you wish to enter the forest or leave the island? (1 to enter, 2 to keep moving through the island): ";
        cin >> input;
        bool userInput(int numberOfDecisions, string input, int& number);
        isValid = false;
        isValid = userInput(2, input, number);
    }

    if (number == 1)
    {
        cout << "In the middle of the forest you come upon a man who you assume to be Bob, who is peacefully" << endl << " sleeping under a massive skeleton structure." << endl << "Beside him lays a pile of shiny coins!" << endl << "Do you choose to leave Bob alone or go for the coins? (1 to leave alone, any other button to scavenge): ";
        cin >> input;
        if (input == "1")
        {

        }
        else
        {
            cout << "Smart choice! A true pirate always wants more plunder! As you sneak up you see more coins on 'Bob's' right side than his left." << endl << "Do you want to go to Bob's right side or left side for the coins? (1 left, any other button for right): ";
            cin >> input;
            if (input == "1") {
                cout << "You are not a true pirate! Bob miraculously turns into a craken and the island suddenly sinks and the craken devours half of your men!";
                userPirates = userPirates / 2;
                cout << endl << "Crewmates remaining: " << userPirates << endl << endl;
            }
            else
            {
                cout << "You are the truest of pirates! You doubled your coin stash!";
                money = money * 2;
                cout << endl << "Coins remaining: " << money << endl << endl;
            }
        }
    }

    if (money > 0 && userPirates > 0)
    {
        cout << endl << "After going through the forest you have heard from the locals that there could be treasure somewhere on the island." << endl;
        cout << "You have the following options: " << endl;
        cout << "1. Continue to search the island, requiring you to spend 75% of your money on more supplies" << endl;
        cout << "2. Leave the island and sail elsewhere" << endl;

        isValid = false;
        while (isValid == false)
        {
            cout << "Type 1 to stay, 2 to leave: " << endl;
            cin >> input;
            isValid = userInput(2, input, number);
        }
        if (number == 1)
        {
            money = money / 4;
            if (randomNumber == 3)
            {
                isFound = true;
                cout << "You have found the hidden treasure! You have won the game!" << endl;
            }
            else
            {
                cout << "Oops, you found no treasure on this island!" << endl;
                cout << "Coins remaining: " << money << endl;
            }
        }
    }

    return isFound;
}

/**
 island4 function does the following:
  1. Requires user to spend 75% of their current money or leave the island
  2. Checks if the has won the game
 @param randomNumber -
 @param money - user's current money amount
 @param countryPointer - randomly selected island name
 @param userPirates - user's current pirate amount
 @return isFound - either true or false (if true, the treasure is found, if false the treasure has not been found)
 */
bool island4(int randomNumber, int& money, string* countryPointer, int& userPirates)
{
    string shipName;
    bool isFound = false;
    bool isValid = false;
    int number = 0;
    cout << "Captain, look ahead! We see an island off in the distance! Lets dock there and check it out!" << endl << endl;
    islandEntry(money, number);
    string input = "";
    if (money == 0 || number == 2)
    {
        return isFound;
    }


    cout << "Welcome to " << countryPointer[3] << "!" << endl;

    reroute(money, userPirates);

    cout << endl << "You have received word from the bartender that there could be treasure somewhere on the floating bar." << endl;
    cout << "You have the following options: " << endl;
    cout << "1. Continue to search the bar, requiring you to spend 75% of your money on more supplies" << endl;
    cout << "2. Leave the bar and sail elsewhere" << endl;


    while (isValid == false)
    {
        cout << "Type 1 to stay, 2 to leave: " << endl;
        cin >> input;
        isValid = userInput(2, input, number);
    }
    if (number == 1)
    {
        money = money / 4;
        if (randomNumber == 4)
        {
            isFound = true;
            cout << "You have found the hidden treasure! You have won the game!" << endl;
        }
        else
        {
            cout << "Oops, you found no treasure on the bar!" << endl;
            cout << "Coins remaining: " << money << endl;
        }
    }
    return isFound;
}

/**
 randomCountryName function does the following:
  1. Randomly selects a country from a list off of an imported file
  2. Stores country name and location into main funtion arrays
 @param namePointer - array that is used to store island name
 @param numberPointer - array that is used to store island location
 @return N/A
 */
void randomCountryName(int* numberPointer, string* namePointer)
{
    int randomNumber = 0;
    for (int counter = 0; counter < 4; counter++)
    {
        bool isValid = true;
        do
        {
            randomNumber = rand() % 196 + 1;
            randomNumber = randomNumber - 1;
            for (int newCounter = 0; newCounter < counter; newCounter++)
            {
                if (randomNumber == numberPointer[newCounter])
                {
                    isValid = false;
                }
            }

        } while (isValid == false);
        numberPointer[counter] = randomNumber;
    }

    ifstream inFile;
    string temporary = "";
    vector<string> countriesList;
    inFile.open("Countries.txt");
    while (!inFile.fail())
    {
        getline(inFile, temporary);
        countriesList.push_back(temporary);
    }
    inFile.close();

    for (int counter = 0; counter < 4; counter++)
    {
        for (int newCounter = 0; newCounter < countriesList.size(); newCounter++)
        {
            if (numberPointer[counter] == newCounter)
            {
                namePointer[counter] = countriesList[newCounter];
            }
        }
    }

}

/**
 reroute function does the following:
  1. Brings user to the scurvy dog bar
  2. Allows user to interact at the bar
 @param money - this is the amount of money that the player has
 @param userPirates - this is the amount of pirates that they have
 */
void reroute(int& money, int& userPirates) {
    string response = "";
    cout << "After your park and begin to get of your ship the man aproaches you and you can see that he is missing an arm, has a peg leg, and has a patch over one eye." << endl;
    cout << "He says 'Welcome to the scurvy dog bar for pirates. Is this yar first time here?' (1 for yes, any other for no)" << endl;

    cin >> response;
    if (response != "1") {
        cout << "'Then enjoy yar stay at the scurvy dog.'" << endl << endl;
    }
    else
    {
        cout << "'Well as I said earlier this here is a pirate bar. Here you can relax have a drink but be carfull everyone here is a pirate and will steal from ya just as fast as drink with ya.'" << endl;
        cout << "'There is a thar main bar and an upstairs becarful though only the big dogs go upstairs." << endl << endl;
    }

    cout << "Where do you want to go (1 for bar, any other for the stairs): ";
    cin >> response;
    if (response == "1") {                                                                                                                                                                                                                      // this is the bar where they can recuite more pirates
        cout << "you see the bartender and a couple of people drinking and eating at the bar.  there also apears to be a hatch in the back corner of the bar" << endl;
        cout << "What do you want to do (1 to approache the people, any other for the hatch): ";
        cin >> response;
        if (response == "people") {
            cout << "As you approach them one calls out to you" << endl;
            cout << "Yo ho me matty where do you come from? (Enter any country name)" << endl;
            cin >> response;
            cout << "Can't say I have ever heard of that but welcome to the Scurvy dog we are all pirates for hire for 50 silver we will follow yar to the end of the 7 seas" << endl;
            cout << "So what do you say? Type 'yes' or 'no' " << endl;
            cin >> response;
            if (response == "yes" || response == "yar") {
                cout << "well how many (type number) " << endl;
                int HowManyPirates = 0;
                while (cin >> HowManyPirates) {
                    if (50 * HowManyPirates > money) {
                        cout << "alrighty yar got yarself a deal for " << HowManyPirates << "pirates I hope yar ar a grat captain" << endl;
                        userPirates += HowManyPirates;
                    }
                    else {
                        cout << "sorry you don't have enough money for that" << endl;
                    }
                    cout << "How many pirates do you want to hire: ";
                }
            }
            else if (response == "no" || response == "nar") {
                cout << "Yar loss mate." << endl;

            }
        }
        else
        {
            cout << "as you crouch down to open the gate you hear the familiar sound of a flitlock pistal being cocked and you feal the cold metal of a gun against your head" << endl;
            cout << "as you look up it is the bartender holding a gun to your head as he says 'walk away yer scrangy mut and you will live'" << endl;
        }
    }
    else
    {
        cout << "as you begin to go up the stairs two big guards stop you" << endl;
        cout << "'where do you think you are going, only people on bisuness ca... wait a moment is that super spiced rum?'" << endl;
        cout << "'nevermind off you go the boss will see you right now'" << endl;
        cout << "as you walk up the rest of the stairs you enter into a lavish room. looking forward you see a old man sitting on top of a raised chair with what looks to be a wheather pirate hat on the top of his head." << endl;
        cout << "whenever he speaks for the first time to great you his voice is silky smoth. just listning to him you can see why he is the boss just the sound of his voice makes you want to listen to him" << endl;
        cout << "'welcome to my island stranger.  Before we talk bisuness let me chaleng you to a game of bolder parchment shears.  just so you know I am going to go bolder' what is your move (type 'bolder', 'shears', or 'parchment':" << endl; // a fun little mini game for people to enjoy
        cin >> response;
        if (response == "bolder") {
            cout << "ah you are a very tactical thinker.  you recognized that the best option in this senario is to go bolder I am impressed. You may now leave unharmed." << endl;
        }
        else if (response == "parchment") {
            cout << "let me tell you a story." << endl;
            cout << "I was once a pirate like you.  I sailed the seas and did what I wanted, and I was extreamly successfull.  I commandeered a massive force with multiple ships and I had alot of fun" << endl;
            cout << "one day the other pirates decided that they were tired of me reigning as the most powerfull pirate and banded to overthrow me and kill my men." << endl;
            cout << "the were unfortianaltly the were successful and forced me into hiding as a merchant." << endl;
            cout << "I have been a cut throte bisuness man and it feals awsome that there are still people out there that will trust me" << endl;
            cout << "keep your rum, and as a token of my gratitude here is 200 silver, and my blessing on your travels" << endl;
            cout << "as you are about to head out the door you hear the smooth voice of the old captian say 'I forgot to tell you my name... " << endl;
            cout << "my name is Gold D. Rogers'" << endl;
            cout << "the soldiers escort you out and leave you at the warf near your ship" << endl;
        }
        else if (response == "shear") {
            cout << "I a disapointed I thought better of you. good by and good luck on your travels" << endl;
        }
        else {
            cout << "Well I thought better of you but it turns out that you are elliterate. Leave with your life while I am in a good mood" << endl;
        }
    }
}