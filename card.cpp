// Aliaksandra Hrechka
// CSC 161 
// 04/05/2021
// Capstone: Searches, Sorts, and Stores
// Description: card.cpp implementation file 

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <cassert>
#include "card.h"
#include "CardCreationDate.h"
#include "status.h"

// creats a new card:
void card::createCard(string ttl, string cntnt) {
	title = ttl;
	content = cntnt;
	cardStatus = status::New;
}

// Generates string from enum
string card::getStatusString()
{
	string currentStatus = "";

	switch (cardStatus) {
	case status::New:
		currentStatus = "New";
		break;
	case status::Active:
		currentStatus = "Active";
		break;
	case status::Achived:
		currentStatus = "Archived";
		break;
	}

	return currentStatus;
}

void card::update()
{
	string op = "";
	string ttl, cont;
	cout << "Would you like to change title? YES/NO: ";
	cin >> op;
	for (int i = 0; i < op.length(); i++)
	{
		op[i] = tolower(op[i]);
	}
	if (op == "yes")
	{
		cout << "New title: ";
		cin.ignore();
		getline(cin, ttl);
		cout << endl;
	}
	if (op == "no")
	{
		ttl = title;
	}
	cout << "Would you like to change content? YES/NO: ";
	cin >> op;
	for (int i = 0; i < op.length(); i++)
	{
		op[i] = tolower(op[i]);
	}
	if (op == "yes")
	{
		cout << "New content: ";
		cin.ignore();
		getline(cin, cont);
		cout << endl;
	}
	if (op == "no")
	{
		cont = content;
	}
	for (int i = 0; i < 50; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "Card Number: " << cardNumber << endl;
	cout << "Title: " << ttl << endl;
	cout << "Content: " << cont << endl;
	cout << "Would you like to save changes? YES/NO: ";
	cin >> op;
	for (int i = 0; i < op.length(); i++)
	{
		op[i] = tolower(op[i]);
	}
	if (op == "yes")
	{
		title = ttl;
		content = cont;
		cout << "Your changes have been saved. Return to the submenu." << endl;
	}
	if (op == "no")
	{
		cout << "Your changes have not been saved. Return to the submenu." << endl;
	}
	
	
	
	
	

}

// Prints the card information:
void card::print() {
	
	for (int i = 0; i < 50; i++)
	{
		cout << "*";
	}
	cout << endl;
	cout << "Card Number: " << cardNumber << endl;
	cout << "Title: " << title << endl;
	cout << "Content: " << content << endl;
	cout << "Status: " << getStatusString() << endl;
	cout << "Created: " << date.getMonth() << "/" << date.getDay() << "/" << date.getYear() << " at " << date.getHours() << ":" << setfill('0') << setw(2) << date.getMinutes() << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << "*";
	}
	cout << endl;
}

void card::setExistingCard(int num,int rep, string ttl, string cont, status st, int mon,int day, int year, int h, int mins, int sec)
{
	cardNumber = num;
	repetition = rep;
	title = ttl;
	content = cont;
	cardStatus = st;
	date.setCreationDate(mon, day, year, h, mins, sec);
}

// Now this function displays created card for the first time
// createCard() in main adds it into the list of active cards
void card::startLearningProcess() {

	cardStatus = status::Active;
	repetition = 1;
	print();
}

// Reads the last number from file and increases it by 1;
void card::increaseCardNumber() {
	cardNumber += 1;
	ofstream outData;
	outData.open("cardNumber.txt");
	outData << cardNumber;
	outData.close();
}

//	Assigning card number:
void card::assignCardNumber() {
	
	ifstream inData;
	inData.open("cardNumber.txt");

	// Terminates the program if file was not found
	assert(!inData.fail());	
 
	inData >> cardNumber;
	// assigns 0 if number in the file is negative
	if (cardNumber < 0) {
		cardNumber = 0;
	}
	inData.close();
}


// default constructor:
card::card() {
	assignCardNumber();
	repetition = 0;
	title = "No Title";
	content = "Empty";
	cardStatus = status::New;
	increaseCardNumber();
}

// constructor with parameters:
card::card(string ttl, string cntnt, status st) {
	createCard(ttl, cntnt);
	assignCardNumber();
	increaseCardNumber();
	repetition = 0;
	cardStatus = st;
	CardCreationDate d;
	d.setCreationDate();
	date = d;
}
