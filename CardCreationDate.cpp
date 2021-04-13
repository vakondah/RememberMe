// Aliaksandra Hrechka
// CSC 161 
// 04/05/2021
// Capstone: Searches, Sorts, and Stores
// Description: CardCreationDate.cpp implementation file 

#include "CardCreationDate.h"
#include <ctime>
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

void CardCreationDate::setCreationDate()
{
	// current day/time using struct tm:
	time_t now = time(0); 
	tm* ltm = localtime(&now);

	year = ltm->tm_year + 1900;
	month = ltm->tm_mon + 1;    // months: 0 - 11
	day = ltm->tm_mday;			// days: 1 - 31;
	hours = ltm->tm_hour;		// since midnight: 0 - 23;
	minutes = ltm->tm_min;		// minutes: 0 - 59
	seconds = ltm->tm_sec;		// 0 - 61. tm_sec is generally 0-59. The extra range is to accommodate for leap seconds in certain systems

	/*cout << year << endl;
	cout << month << endl;
	cout << day << endl;
	cout << hours << endl;
	cout << minutes << endl;
	cout << seconds << endl;*/
}
void CardCreationDate::setCreationDate(int month, int day, int year, int hours, int minutes, int seconds) {
	this->month = month;
	this->day = day;
	this->year = year;
	this->hours = hours;
	this->minutes = minutes;
	this->seconds = seconds;
}

// considers day, hour, and minutes
// does not consider dates on the edge of two months
// TODO: finish to consider months
int CardCreationDate::operator-(const CardCreationDate& currentDate) const
{	
	return (currentDate.day - day) * 1440 + (currentDate.hours - hours) * 60 + (currentDate.minutes - minutes);
}
