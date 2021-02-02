//
/**  M3.cpp

  Description: The following program is a two-player game of tic-tac-toe, and it will
  repeat until the users decide to stop playing. The game will also keep a running total of
  the score throughout the game

  Steps:
  1. Read in the usernames
  2. Tell the users instructions
  3. Display the empty board and let the players pick their positions
  4. After each turn, fill in the array with the user's mark and display the board
  5. Continue alternating turns until all the squares are filled or either player
  gets three marks in a row
  6. Display the overall score
  7. Ask the user if they want to play again


  Created by Elijah Scott Weber Weber on 10/07/20.
  Copyright © 2020 Elijah Scott Weber. All rights reserved.
*/


// Included libraries
#include <iostream>
#include <string>
using namespace std;



// Constant array size
const int SIZE = 3;



// Function prototypes
int getPlayerInput(string playerName);
bool isLegalMove(char board[SIZE][SIZE], int location);
void placeMarkOnBoard(char board[SIZE][SIZE], char playerMark, int location);
void clearBoard(char board[SIZE][SIZE]);
bool hasThreeInRow(char board[SIZE][SIZE], char playerMark);
void locationToBoardLocation(int location, int &row, int &column);
void displayBoard(char board[SIZE][SIZE]);
void displayGameStats(int ties, int player1Score, int player2Score, string player1Name, string player2Name);
void winner(string userName, bool gameWinner, int& ties);



// Main Function
int main()
{


	// Usernames and quadrant location
	string playerNameOne;
	string playerNameTwo;
	int playerOneInput;      // Board location
	int playerTwoInput;		 // Board location



	// Game stats
	int playerOneWins = 0;
	int playerTwoWins = 0;
	int numTies = 0;
	int turnCounter = 0;			// Determines who goes first each game
	string firstPerson = "";



	char playAgainEntry = ' ';
	string nameGameWinner = "";     // Username for winner
	bool quitGame = false;




	// Instructions
	cout << "Welcome to Tic-Tac-Toe!" << endl;
	cout << "Player 1, please enter your username: ";
	getline(cin, playerNameOne);
	cout << "Player 2, please enter your username: ";
	getline(cin, playerNameTwo);




	// Further instructions
	cout << playerNameOne << " you will be X's, and " << playerNameTwo << " you will be O's" << endl;
	char gameBoard[SIZE][SIZE];




	// Determines who the first person is
	firstPerson = playerNameOne;




	// Program runs until user wants to quit
	while (quitGame == false)
	{




		// Variables each game
		int count = 0;                 // Count < 9?
		int row = 0;
		int column = 0;
		char playerMark = ' ';         // X or O
		bool isLegal = false;
		bool gameWinner = false;
		clearBoard(gameBoard);         // Resets each game




		// Each individual game runs
		while (count < 9 && gameWinner == false)
		{




			// Determines whose turn it is
			if (turnCounter % 2 == 0 && gameWinner == false)
			{




				// Player mark
				isLegal = false;
				playerMark = 'X';




				// Get input and validate
				while (isLegal == false)
				{
					playerOneInput = getPlayerInput(playerNameOne);
					isLegal = isLegalMove(gameBoard, playerOneInput);
				}




				// Place mark on board and display results
				placeMarkOnBoard(gameBoard, playerMark, playerOneInput);
				displayBoard(gameBoard);
				gameWinner = hasThreeInRow(gameBoard, playerMark);



				// Running count of wins
				if (gameWinner == true)
				{
					playerOneWins++;
					nameGameWinner = playerNameOne;
				}


				// Updates turn count
				count++;
				turnCounter++;


			}




			// Player 2 turn
			else if (turnCounter % 2 != 0 && gameWinner == false)
			{


				// Players mark
				isLegal = false;
				playerMark = 'O';




				// Gets input and validates
				while (isLegal == false)
				{
					playerTwoInput = getPlayerInput(playerNameTwo);
					isLegal = isLegalMove(gameBoard, playerTwoInput);
				}




				// Place mark on the board and display
				placeMarkOnBoard(gameBoard, playerMark, playerTwoInput);
				displayBoard(gameBoard);
				gameWinner = hasThreeInRow(gameBoard, playerMark);




				// Running count of wins
				if (gameWinner == true)
				{
					playerTwoWins++;
					nameGameWinner = playerNameTwo;
				}


				// Turn counter
				count++;
				turnCounter++;

			}
		}



		// Display results and play again
		winner(nameGameWinner, gameWinner, numTies);
		displayGameStats(numTies, playerOneWins, playerTwoWins, playerNameOne, playerNameTwo);
		cout << "Would you like to play again? Type Y for yes and N for no: ";
		cin >> playAgainEntry;




		// Determines to quit or not
		if (playAgainEntry == 'n' || playAgainEntry == 'N')
		{
			quitGame = true;
		}



		// Input validation
		while (playAgainEntry != 'Y' && playAgainEntry != 'y' && playAgainEntry != 'N' && playAgainEntry != 'n')
		{
			cout << "Would you like to play again? Type Y for yes and N for no: ";
			cin >> playAgainEntry;
		}


		// Spacing
		cout << endl;



		// Determines the first person to go
		if (firstPerson == playerNameOne)
		{
			turnCounter = 1;
			firstPerson = playerNameTwo;
		}
		else if (firstPerson == playerNameTwo)
		{
			turnCounter = 0;
			firstPerson = playerNameOne;
		}

	}

}


/**
	getPlayerInput Function does the following:
		1. Receive the username
		2. Ask the user for the number of their quadrant
		3. Repeat until a valid input is received
		4. Return the number

	@param playerName (player's username)
	@return userInputInteger
 */
int getPlayerInput(string playerName)
{


	// Validation variables
	string userInput = "";
	int userInputInteger = 0;
	bool isValidDigit = false;
	char validator = ' ';



	// Validation
	while (isValidDigit == false)
	{


		// Get quadrant
		cout << playerName << " type the number of the quadrant you wish to place your marker: ";
		cin >> userInput;



		// String conversion validation
		if (userInput.length() == 1)
		{

			// First character
			validator = userInput[0];



			// Digit validation
			if (isdigit(validator) && validator != '0')
			{
				isValidDigit = true;
				userInputInteger = stoi(userInput);
				break;
			}


			// Error
			else
			{
				cout << "Invalid entry." << endl;
			}



		}


		// Error
		else
		{
			cout << "Invalid entry." << endl;
		}


		// Cin.ignore function taken from http://www.cplusplus.com/forum/beginner/36978/
		// I kept receiving an infinite loop once the command prompt entered a failed state
		cin.clear();
		cin.ignore();



	}


	return userInputInteger;
}


/**
	isLegalMove Function does the following:
		1. Receives the array
		2. Receives the user's location
		3. Determines if the slot is filled
		4. Returns true or false

	@param board (the array for the board)
	@param location (the quadrant of the mark)
	@return isLegalMove
 */
bool isLegalMove(char board[SIZE][SIZE], int location)
{

	// String conversion variables
	bool isLegalMove = false;
	string str = to_string(location);



	// Determines if spot is already taken
	for (int row = 0; row < SIZE; row++)
	{
		for (int column = 0; column < SIZE; column++)
		{
			if (str[0] == board[row][column])
			{
				isLegalMove = true;
			}
		}
	}



	return isLegalMove;
}



/**
	placeMarkOnBoard Function does the following:
		1. Receives the array
		2. Receives the user's location
		3. Receives the player's mark
		4. Find's the location on the array and fills the slot

	@param board (the array for the board)
	@param playerMark (the player's designated letter)
	@param location (the quadrant of the mark)
	@return void
 */
void placeMarkOnBoard(char board[SIZE][SIZE], char playerMark, int location)
{


	// Places marker in array
	int row = 0;
	int column = 0;
	locationToBoardLocation(location, row, column);
	board[row][column] = playerMark;


}



/**
	clearBoard Function does the following:
		1. Receives the array
		2. Clears each of the slots

	@param board (the array for the board)
	@return void
 */
void clearBoard(char board[SIZE][SIZE])
{


	// Starting quadrant number
	int numberDisplayed = 1;
	string conversion = "";



	// Enters new numbers into board
	for (int row = 0; row < SIZE; row++)
	{
		for (int column = 0; column < SIZE; column++)
		{
			conversion = to_string(numberDisplayed);
			board[row][column] = conversion[0];
			numberDisplayed++;
		}
	}


	// Passes new board to display
	displayBoard(board);

}



/**
	hasThreeInRow Function does the following:
		1. Receives the array
		2. Receives the player's mark
		3. Determines if the user has reached three marks in a row

	@param board (the array for the board)
	@param playerMark (player's designated mark)
	@return hasThreeInARow
 */
bool hasThreeInRow(char board[SIZE][SIZE], char playerMark)
{


	bool hasThreeInARow = false;


	// Rows three in a row
	for (int rows = 0; rows < SIZE; rows++)
	{
		if (board[rows][0] == board[rows][1] &&
			board[rows][0] == board[rows][2])
		{
			hasThreeInARow = true;
		}
	}



	// Columns three in a row
	for (int columns = 0; columns < SIZE; columns++)
	{
		if (board[0][columns] == board[1][columns] &&
			board[0][columns] == board[2][columns])
		{
			hasThreeInARow = true;
		}
	}




	// Diagonal three in a row
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
	{
		hasThreeInARow = true;
	}



	// Other diagonal
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
	{
		hasThreeInARow = true;
	}



	return hasThreeInARow;
}



/**
	locationToBoardLocation Function does the following:
		1. Receives the location and gains access to the row and column
		2. Determines the array location
		3. Manipulates the row and column variable

	@param location (quadrant of the player's mark)
	@param &row (the row of the array)
	@param &column (the column of the array)
	@return void
 */
void locationToBoardLocation(int location, int &row, int &column)
{


	// Structure determines the row and column for the marker
	switch (location)
	{
	case 1: row = 0; column = 0; break;
	case 2: row = 0; column = 1; break;
	case 3: row = 0; column = 2; break;
	case 4: row = 1; column = 0; break;
	case 5: row = 1; column = 1; break;
	case 6: row = 1; column = 2; break;
	case 7: row = 2; column = 0; break;
	case 8: row = 2; column = 1; break;
	case 9: row = 2; column = 2; break;
	}



}



/**
	displayBoard Function does the following:
		1. Receives the array
		2. Displays the values in the array

	@param board (the array for the board)
	@return void
 */
void displayBoard(char board[SIZE][SIZE])
{


	// Spacing
	cout << endl << endl;



	// Enter array row
	for (int row = 0; row < SIZE; row++)
	{


		// Enter array column
		for (int column = 0; column < SIZE; column++)
		{



			// Display divider
			if (column < 2)
			{
				cout << " " << board[row][column] << " |";
			}



			else
			{
				cout << " " << board[row][column];
			}



		}


		// Spacing
		cout << endl;




		// Divider
		if (row != 2)
		{
			cout << "---+---+---" << endl;
		}


	}



	// More spacing
	cout << endl << endl;

}



/**
	displayGameStats Function does the following:
		1. Receives the number of ties, both scores, and both usernames
		2. Displays each of the values

	@param ties (number of ties)
	@param player1Score (player 1 score)
	@param player2Score (player 2 score)
	@param player1Name (player 1 username)
	@param player2Name (player 2 username)
	@return void
 */
void displayGameStats(int ties, int player1Score, int player2Score, string player1Name, string player2Name)
{


	// Displays game stats
	cout << player1Name << " score: " << player1Score << endl;
	cout << player2Name << " score: " << player2Score << endl;
	cout << "Ties: " << ties << endl;



}



/**
	Winner Function does the following:
		1. Receives the user name, the game winner, and the number of ties
		2. Displays various outputs depending on the results of the game
	@param userName (player userName)
	@param gameWinner (the winner of the game)
	@param &ties (number of ties thus far)
	@return void
 */
void winner(string userName, bool gameWinner, int& ties)
{


	// Displays ties
	if (gameWinner == false)
	{
		cout << "Oops! Looks like you both have tied!" << endl;
		ties++;
	}



	// Displays winner
	else
	{
		cout << "Congratulations, " << userName << "! You are the ultimate tic tac toe-ist!" << endl;
	}



}
