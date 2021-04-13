// Aliaksandra Hrechka
// CSC 161 
// 04/05/2021
// Capstone: Searches, Sorts, and Stores
// Description: card.h header file 

#pragma once
#include <string>
#include <fstream>
#include "status.h"
#include "CardCreationDate.h"


using namespace std;

class card
{
private:
	int cardNumber;
	int repetition;
	string title;
	string content;
	status cardStatus;
	CardCreationDate date;

	// internal functions to generate unique card number: 
	void increaseCardNumber();
	void assignCardNumber();
	//int terminate() { return 0; }

public:
	// get functions:
	int getCardNumber() const { return cardNumber; }
	int getRepetition() const {	return repetition;}
	string getTitle() const { return title; }
	string getContent() const { return content; }
	status getStatus() const { return cardStatus; }
	CardCreationDate getCreationDate() const { return date; }
	int getCreationMonth() const { return date.getMonth(); }
	int getCreationDay() const { return date.getDay(); }
	int getCreationYear() const { return date.getYear(); }
	int getCreationHours() const { return date.getHours(); }
	int getCreationMinutes() const { return date.getMinutes(); }
	int getCreationSeconds() const { return date.getSeconds(); }

	// set functions:
	void setTitle(string t) { title = t; }
	void setContent(string c) { content = c; }
	void setRepetition(int i) { repetition = i; }
	void setStatus(status st) { cardStatus = st; }
	//void setCreationDate(CardCreationDate d) { date = d; } // TODO: not sure I need it
	void setExistingCard(int, int, string, string, status, int, int, int, int, int, int);

	// this function renders the card at specific intervals 2, 10, 30, 180 seconds
	// the final version of this function will do that at intervals spesified by Ebbinghaus (see documentation for more details)
	void startLearningProcess();

	// member functions:
	void createCard(string, string);
	string getStatusString();
	void update();
	void print();

	// constructors:
	card();
	card(string, string, status);
};

