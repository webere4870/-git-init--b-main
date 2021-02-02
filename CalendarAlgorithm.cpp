//
/**  p07dot2.cpp

  Description: The following program receives a month and year
  and returns the calendar for that month

  Steps:
  1. Read in the month and year from the user
  2. Determine the day of the week for the 1st day of that month
  3. Display the header information
  4. Display the padding to the left of the date
  5. Loop through until all dates are shown


  Created by Elijah Scott Weber Weber on 10/07/20.
  Copyright © 2020 Elijah Scott Weber. All rights reserved.
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int dayOfWeek(int month, int day, int year);
string whatDayIsIt(int numberOfDay);
string whatMonthIsIt(int monthNumber);
int numberOfDaysPerMonth(int month, int year);
int startingCounter(string dayOfTheWeek);
void displayHeader(string month, int year);
void displayDays(int numdays, int startingVariable);

int main()
{

	int day = 1;
	int year = 0;
	int month = 0;
	int numberToDay = 0;
	string dayItIs = "";
	string monthItIs = "";
	string validate = "";
	int daysInTheMonth = 0;
	int counterVariable = 0;

	while (!cin.fail())
	{
		cout << "Enter month and year: ";
		cin >> month >> year;
		validate = month;
		char validator = validate[0];
		if (!cin.fail() && month > 0 && month < 13 && year > 0)
		{
			numberToDay = dayOfWeek(month, day, year);
			monthItIs = whatMonthIsIt(month);
			dayItIs = whatDayIsIt(numberToDay);
			daysInTheMonth = numberOfDaysPerMonth(month, year);
			counterVariable = startingCounter(dayItIs);

			displayHeader(monthItIs, year);

			displayDays(daysInTheMonth, counterVariable);
		}
	}

	return 0;
}


/**
   dayOfWeek - Computes the weekday of a given date.
   @param year  the year
   @param month the month (1 = January ... 12 = December)
   @param day   the day of the month
   @return the weekday (0 = Saturday ... 6 = Friday)
*/
int dayOfWeek(int month, int day, int year)
{
	int dayOfTheWeek = 0;

	if (month == 1 || month == 2)
	{
		month += 12;
		year--;
	}

	dayOfTheWeek = (day + (((month + 1) * 26) / 10) + year + (year / 4) + 6 * (year / 100) + (year / 400)) % 7;

	return dayOfTheWeek;
}


/**
	whatDayIsIt Function does the following:
		1. Receives the day value
		2. Calculates uses a switch structure to decide the day
	@param numberOfDay
	@return whatIsTheDay
 */
string whatDayIsIt(int numberOfDay)
{
	string whatIsTheDay = "";
	switch (numberOfDay)
	{
	case 0: whatIsTheDay = "Saturday";
		break;
	case 1: whatIsTheDay = "Sunday";
		break;
	case 2: whatIsTheDay = "Monday";
		break;
	case 3: whatIsTheDay = "Tuesday";
		break;
	case 4: whatIsTheDay = "Wednesday";
		break;
	case 5: whatIsTheDay = "Thursday";
		break;
	case 6: whatIsTheDay = "Friday";
		break;
	}

	return whatIsTheDay;
}



/**
	whatDayIsIt Function does the following:
		1. Receives the month value
		2. Uses a switch structure to decide the month
	@param monthNumber
	@return whatMonth
 */
string whatMonthIsIt(int monthNumber)
{
	if (monthNumber == 1 || monthNumber == 2)
	{
		monthNumber += 12;
	}

	string whatMonth = "";

	switch (monthNumber)
	{
	case 3: whatMonth = "March";
		break;
	case 4: whatMonth = "April";
		break;
	case 5: whatMonth = "May";
		break;
	case 6: whatMonth = "June";
		break;
	case 7: whatMonth = "July";
		break;
	case 8: whatMonth = "August";
		break;
	case 9: whatMonth = "September";
		break;
	case 10: whatMonth = "October";
		break;
	case 11: whatMonth = "November";
		break;
	case 12: whatMonth = "December";
		break;
	case 13: whatMonth = "January";
		break;
	case 14: whatMonth = "February";
		break;
	}

	return whatMonth;
}


/**
	numberOfDaysPerMonth Function does the following:
		1. Receives the month and year
		2. Determiens the number of days in the specified month
	@param month (the month entry)
	@param year (the year)
	@return numberOfDays
 */
int numberOfDaysPerMonth(int month, int year)
{
	int numberOfDays = 0;

	if (month == 2)
	{
		if (year % 4 == 0 && year % 100 != 0)
		{
			month = 13;
		}
	}
	if (month == 2)
	{
		if (year % 4 == 0 && year % 100 == 0 && year % 400 == 0)
		{
			month = 13;
		}
	}

	switch (month)
	{
	case 4: numberOfDays = 30;
		break;
	case 6: numberOfDays = 30;
		break;
	case 9: numberOfDays = 30;
		break;
	case 11: numberOfDays = 30;
		break;
	case 1: numberOfDays = 31;
		break;
	case 2: numberOfDays = 28;
		break;
	case 3: numberOfDays = 31;
		break;
	case 5: numberOfDays = 31;
		break;
	case 7: numberOfDays = 31;
		break;
	case 8: numberOfDays = 31;
		break;
	case 10: numberOfDays = 31;
		break;
	case 12: numberOfDays = 31;
		break;
	case 13: numberOfDays = 29;
		break;
	}

	return numberOfDays;
}


/**
	startingCounter Function does the following:
		1. Receives the day of the week
		2. Determines where to start on the calendar
	@param dayOfTheWeek
	@return startingVariable
 */
int startingCounter(string dayOfTheWeek)
{
	int startingVariable = 0;

	if (dayOfTheWeek == "Sunday")
	{
		startingVariable = 0;
	}
	else if (dayOfTheWeek == "Monday")
	{
		startingVariable = 1;
	}
	else if (dayOfTheWeek == "Tuesday")
	{
		startingVariable = 2;
	}
	else if (dayOfTheWeek == "Wednesday")
	{
		startingVariable = 3;
	}
	else if (dayOfTheWeek == "Thursday")
	{
		startingVariable = 4;
	}
	else if (dayOfTheWeek == "Friday")
	{
		startingVariable = 5;
	}
	else if (dayOfTheWeek == "Saturday")
	{
		startingVariable = 6;
	}
	
	return startingVariable;
}


/**
	displayHeader Function does the following:
		1. Receives the month and year
		2. Specifies the padding for the date
		3. Displays the date
	@param month (the month entry)
	@param year (the year)
	@return N/A
 */
void displayHeader(string month, int year)
{
	string display = month + " " + to_string(year);
	int length = display.length();
	int padding = (20 - length) / 2;
	length = padding + display.length();
	cout << endl;
	cout << setfill(' ') << setw(length) << right << display << endl;
	cout << "Su Mo Tu We Th Fr Sa" << endl;
}


/**
	displayDays Function does the following:
		1. Receives the number of days and starting variable
		2. Pads the first line
		3. Uses loops to display the days
	@param numdays (number of days in the month)
	@param startingVariable (where to start on the first line)
	@return N/A
 */
void displayDays(int numdays, int startingVariable)
{
	const int DAYS_PER_WEEK = 7;
	const int MAX_WEEKS_PER_MONTH = 4;

	int dayArray[MAX_WEEKS_PER_MONTH][DAYS_PER_WEEK];

	int displayNumber = 1;

	int padding = 7 - startingVariable;

	while (padding < 7)
	{
		cout << "   ";
		padding++;
	}

	for (int counter = startingVariable; counter < DAYS_PER_WEEK; counter++)
	{
		if (counter / 10 == 0)
		{
			cout << " " << displayNumber << " ";
		}
		else
		{
			cout << displayNumber << " ";
		}
		displayNumber++;
	}
	cout << endl;

	while (displayNumber < numdays)
	{
		int position = 0;
		while (position < 7 && displayNumber <= numdays)
		{
			if (displayNumber / 10 == 0)
			{
				cout << " " << displayNumber << " ";
			}
			else
			{
				cout << displayNumber << " ";
			}
			displayNumber++;
			position++;
		}
		cout << endl;
	}

	cout << endl;
}