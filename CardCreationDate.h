// Aliaksandra Hrechka
// CSC 161 
// 04/05/2021
// Capstone: Searches, Sorts, and Stores
// Description: CardCreationDate.h header file 

#pragma once
#define _CRT_SECURE_NO_WARNINGS
class CardCreationDate
{
private:
	
	int month;
	int day;
	int year;
	int hours;
	int minutes;
	int seconds;

public:
	// get functions:
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getYear() const { return year; }
	int getHours() const { return hours; }
	int getMinutes() const { return minutes; }
	int getSeconds() const { return seconds; }

	// set functions:
	void setCreationDate();
	void setCreationDate(int, int, int, int, int, int);

	//operator overloading
	int operator-(const CardCreationDate&)const;

};

