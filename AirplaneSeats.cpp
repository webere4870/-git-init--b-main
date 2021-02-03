//
/**  partA.cpp

  Description: The following fills a plane using arrays

  Steps:
  1. Get user input for an array
  2. Determine if the spot is taken and place it on the board


  Created by Elijah Scott Weber Weber on 10/20/20.
  Copyright © 2020 Elijah Scott Weber. All rights reserved.
*/

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

const int COLUMNS = 5;
const int ROWS = 13;
string seatingChart[ROWS][COLUMNS];

void displaySeating();
bool validation(int& row, int& column, char validator);
void initialize();
void transfer(int& row, int& column, char userInput, char seat);
void passIntoArray(int& row, int& column);
bool full();

int main()
{
	string playAgain = "";
	do
	{
		int userRow = 0;
		int userColumn = 0;
		bool isFull = false;
		bool valid = false;
		int entryOne = 0;
		char entryTwo = ' ';
		initialize();
		displaySeating();
		while (isFull == false)
		{
			if (isFull == false)
			{
				cout << "Enter the row number and column letter of your seat or Q to quit: ";
				cin >> entryOne >> entryTwo;
				if (cin.fail())
				{
					break;
				}
				transfer(userRow, userColumn, entryOne, entryTwo);
				valid = validation(userRow, userColumn, entryTwo);
				while (valid == false)
				{
					cout << "Invalid entry." << endl;
					cout << "Enter the row number and column letter of your seat: ";
					cin >> entryOne >> entryTwo;
					transfer(userRow, userColumn, entryOne, entryTwo);
					valid = validation(userRow, userColumn, entryTwo);
				}
				passIntoArray(userRow, userColumn);
				displaySeating();
				isFull = full();
				if (isFull == true)
				{
					cout << "Plane is full." << endl;
				}
			}
			
		}
		if (!cin.fail())
		{
			cout << "Type Y to load another plane, N to quit: ";
		}
	} while (playAgain == "y" || playAgain == "Y");

	return 0;
}

/**
	displaySeating Function displays the seats
	@param NA
	@return NA
 */
void displaySeating()
{
	string spacing = "";
	for (int counter = 0; counter < ROWS; counter++)
	{
		if ((counter + 1) / 10 == 0)
		{
			cout << " ";
		}
		for (int secondCounter = 0; secondCounter < COLUMNS; secondCounter++)
		{
			if (counter != 12)
			{
				cout << seatingChart[counter][secondCounter];
				switch (secondCounter)
				{
				case 0: spacing = "  ";
					break;
				case 1: spacing = " ";
					break;
				case 2: spacing = "   ";
					break;
				case 3: spacing = " ";
					break;
				case 4: spacing = "";
					break;
				}
				cout << spacing;
			}
			else
			{
				if (secondCounter < 3)
				{
					cout << seatingChart[counter][secondCounter];
					switch (secondCounter)
					{
					case 0: spacing = "  ";
						break;
					case 1: spacing = " ";
						break;
					case 2: spacing = "   ";
						break;
					case 3: spacing = " ";
						break;
					case 4: spacing = "";
						break;
					}
				}
				cout << spacing;
			}
			
		}
		cout << endl;
	}
}

/**
	validation Function validates user input
	@param &row
	@param &column
	@return isValid
 */
bool validation(int& row, int& column, char validator)
{
	bool isValid = true;

	for (int counter = 0; counter < ROWS; counter++)
	{
		for (int newGuy = 0; newGuy < COLUMNS; newGuy++)
		{
			if (counter == row && column == newGuy)
			{
				if (seatingChart[counter][newGuy] == "X")
				{
					isValid = false;
				}
			}
		}
	}

	if (row < 0 || row > 12)
	{
		isValid = false;
	}

	if (column > 4 || column < 0)
	{
		isValid = false;
	}

	if (row == 12)
	{
		if (column > 2)
		{
			isValid = false;
		}
	}

	if (isupper(validator))
	{
		if (validator < 'A' || validator > 'D')
		{
			isValid = false;
		}
	}

	if (islower(validator))
	{
		if (validator < 'a' || validator > 'd')
		{
			isValid = false;
		}
	}

	return isValid;
}

/**
	transfer Function converts the row and columns
	@param &row
	@param &column
	@param userInput
	@param seat
	@return NA
 */
void transfer(int& row, int& column, char userInput, char seat)
{
	if (userInput == 13)
	{
		row = userInput + 5;
	}
	if (userInput != 14)
	{
		row = userInput - 1;
	}
	else
	{
		row = userInput - 2;
	}
	if (row == 14)
	{
		switch (seat)
		{
		case 'A': column = 1;
			break;
		case 'a': column = 1;
			break;
		case 'B': column = 2;
			break;
		case 'b': column = 2;
			break;
		}
	}
	else
	{
		switch (seat)
		{
		case 'A': column = 1;
			break;
		case 'a': column = 1;
			break;
		case 'B': column = 2;
			break;
		case 'b': column = 2;
			break;
		case 'C': column = 3;
			break;
		case 'c': column = 3;
			break;
		case 'D': column = 4;
			break;
		case 'd': column = 4;
			break;
		}
	}
}


/**
	passIntoArray Function passes values
	@param &row
	@param &column
	@return NA
 */
void passIntoArray(int& row, int& column)
{
	for (int counter = 0; counter < ROWS; counter++)
	{
		for (int newCounter = 0; newCounter < COLUMNS; newCounter++)
		{
			if (counter == row && newCounter == column)
			{
				seatingChart[counter][newCounter] = "X";
			}
		}
	}
}


/**
	initialize Function converts the row and columns
	@param NA
	@return NA
 */
void initialize()
{
	string tochar = "";
	int variable = 0;
	for (int counter = 0; counter < ROWS; counter++)
	{
		for (int newCounter = 0; newCounter < COLUMNS; newCounter++)
		{
			if (counter != 12)
			{
				variable = counter + 1;
			}
			else
			{
				variable = counter + 2;
			}
			if (newCounter == 0)
			{
				tochar = to_string(variable);
				seatingChart[counter][newCounter] = tochar;
			}
			else
			{
				switch (newCounter)
				{
				case 1: tochar = 'A';
					break;
				case 2: tochar = 'B';
					break;
				case 3: tochar = 'C';
					break;
				case 4: tochar = 'D';
					break;
				}

				seatingChart[counter][newCounter] = tochar;
			}
		}
	}
}


/**
	full Function determines if the plane is full
	@param NA
	@return isFull
 */
bool full()
{
	bool isFull = true;
	for (int counter = 0; counter < ROWS; counter++)
	{
		if (counter != 12)
		{
			for (int newCounter = 1; newCounter < COLUMNS; newCounter++)
			{
				if (newCounter > 0)
				{
					if (seatingChart[counter][newCounter] != "X")
					{
						isFull = false;
					}
				}
			}
		}
		else
		{
			for (int newCounter = 1; newCounter < COLUMNS - 2; newCounter++)
			{
				if (newCounter > 0)
				{
					if (seatingChart[counter][newCounter] != "X")
					{
						isFull = false;
					}
				}
			}
		}
	}
	return isFull;
}