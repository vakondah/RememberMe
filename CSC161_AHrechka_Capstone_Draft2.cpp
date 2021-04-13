// Aliaksandra Hrechka
// CSC 161 
// 04/05/2021
// Capstone: Searches, Sorts, and Stores
// Description: main program 


#include <iostream>
#include <fstream>
#include <Windows.h>
#include "CardCreationDate.h"
#include "card.h"
#include "exceptionMessage.h"
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cassert>
#include <iomanip>


using namespace std;

// prototypes:
void WelcomeMessage();
void DisplayMainMenu();
int ChooseOption();
void createNewCard(vector<card>&);
status convertStringToStatus(string str);
void displayActiveCards(vector<card>);
void performSearch(vector<card>&);
int searchForCard(vector<card>,int, int, int);
void displaySubmenu();
int chooseSubmenuOption();
void run(vector<card>);
void readFromFile(vector<card>&);
void saveInFile(vector<card>&);

int main()
{
        
    vector<card> activeCards;
    vector<card> archive;

    readFromFile(activeCards);
    
    Sleep(3000);
    
    // Starting run thread:
    std::thread t(run, std::ref(activeCards));
    t.detach();

    int op = 0;

    WelcomeMessage();
    DisplayMainMenu();
    op = ChooseOption();

    // choosing an option and calling a corresponding function.
    // Right now only the 1 and 2 (4 in progress)options are available.
    while (op != 5)
    {
            switch (op)
            {
            case 1:
                createNewCard(activeCards);
                break;
            case 2:
                displayActiveCards(activeCards);
                break;
            case 3:
                cout << "TODO: option 3" << endl;
                break;
            case 4:
                performSearch(activeCards);
                break;
            default:
                break;
            }

            DisplayMainMenu();
            op = ChooseOption();
        
    }
    if (op == 5)
    {
        cout << "Program will be terminated. Farewell!" << endl;
    }

    return 0;
}

// function definitions:
void WelcomeMessage()
{
    cout << "Welcome to the 'RememberMe' learning application - " << endl;
    cout << "the most effective technique for memorization! " << endl;
}

void DisplayMainMenu()
{
    // horizontal line:
    for (int i = 0; i < 50; i++)
    {
        cout << "*";
    }
    cout << endl;

    // Main menu:
    cout << "MAIN MENU:" << endl;
    cout << "1. Create a new card " << endl;
    cout << "2. View active cards " << endl;
    cout << "3. View archived cards (TODO) " << endl;
    cout << "4. Search " << endl;
    cout << "5. Exit " << endl;
    cout << "Please select an option to continue (only options 1,2 and 4 are working!): ";

}


// This function allows the user to choose an option between 1 and 5 
//  and handles input failure if the user enters a string instead of number.
int ChooseOption()
{
    bool flag = 0;
    int option = 0;
    string str = "Must be a number!";
    string str2 = "Must be between 1 and 5!";

    while (!flag)
    {
        try
        {
            cin >> option;
            if (!cin) { throw str; }
            else {
                if (option < 1 || option > 5)
                {
                    throw exceptionMessage();
                    flag = false;
                }

                flag = true;
            }
        }
        catch (string s)
        {
            cout << s << endl;
            // restores the input stream:
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Please select an option to continue: ";
        }
        catch (exceptionMessage ex)
        {
            cout << str2 << endl;
            cout << "Please select an option to continue: ";
        }
    }
    return option;
}

// this function creates a new card:
void createNewCard(vector<card>& v) {

    string title;
    string content;
    string str = "Invalid input! Try again.";
    string input;

    // Taking user's input:
    cout << "Please enter a title of a new card: ";
    cin.ignore();
    getline(cin, title);
    cout << endl;

    cout << "Please enter the card's content: ";
    getline(cin, content);
    cout << endl;

    // new card object:
    card card(title, content, status::New);

    // Displays card for the first time.
    card.print();

    bool flag = false;

    // Prompts the user to enter yes/no. Ignores the letter case:
    cout << "Would you like to start the lerning process for " << card.getTitle() << " card? (YES/NO): ";
    cin >> input;

    while (!flag)
    {
        // converts string into lowercase
        for (int i = 0; i < input.length(); i++)
        {
            input[i] = tolower(input[i]);
        }
        if (input == "yes")
        {
            
            
            // Starting the learning process:
            card.startLearningProcess();
            v.push_back(card);
            // save:
            saveInFile(v);
                        
            flag = true;
            break;
        }
        if (input == "no")
        {
            cout << "Card " << card.getTitle() << " will be archived." << endl;
            card.setStatus(status::Achived);
            // TODO: send to archive list
            flag = true;
            break;
        }

        cout << "Wrong input." << endl;
        cout << "Would you like to start the lerning process for " << card.getTitle() << " card? (YES/NO): ";
        cin >> input;
    }
}

status convertStringToStatus(string str) {
    if (str == "New")
    {
        return status::New;
    }
    if (str == "Active")
    {
        return status::Active;
    }
    if (str == "Archived")
    {
        return status::Achived;
    }
}

void displayActiveCards(vector<card> activeCards)
{
    // displing activeCards list 
    for (int i = 0; i < activeCards.size(); i++)
    {
        activeCards[i].print();
    }
}

void performSearch(vector<card>& activeCards) {
    int index, input;
    bool flag = false;
    string str = "Must be a number!";

    card* cp;
    // sorting the list in acsending order:
    sort(activeCards.begin(), activeCards.end(), [](const card& x, const card& y)
        {
            return x.getCardNumber() < y.getCardNumber();
        });

    while (!flag)
    {
        try
        {
            cout << "Please enter the card's number: ";
            cin >> input;
            cout << endl;
            if (!cin) { throw str; }
            else flag = true;
        }
        catch (string str)
        {
            cout << str << endl;
            // restores the input stream:
            cin.clear();
            cin.ignore(100, '\n');
        }
    }
    
    index = searchForCard(activeCards, 0, activeCards.size() - 1, input);
    while (index == -1)
    {
        flag = false;

        try
        {
            cout << "Card with number " << input << " was not found." << endl;
            cout << "Please enter another number: ";
            cin >> input;
            cout << endl;
            if (!cin) { throw str; }
            else flag = true;
        }
        catch (string str)
        {
            cout << str << endl;
            // restores the input stream:
            cin.clear();
            cin.ignore(100, '\n');
        }

        index = searchForCard(activeCards, 0, activeCards.size() - 1, input);
    }
    if(index >= 0){
        int op = 0;
        cp = &activeCards[index];
        cp->print();

        displaySubmenu();
        op = chooseSubmenuOption();
        while (op != 4)
        {
            switch (op)
            {
            case 1:
                activeCards.erase(activeCards.begin() + index);
                return;
                break;
            case 2:
                cp->update();
                break;
            case 3:
                cout << "TODO: option 3" << endl;
                break;
             default:
                break;
            }

            displaySubmenu();
            op = chooseSubmenuOption();
        }
        if (op == 4)
        {
            cout << "Return to the main menu" << endl;
        }
    }
}

// binary recurcive search:
int searchForCard(vector<card> list, int first, int last, int key) {
        
    bool found = false;
    int mid;
    mid = (first + last) / 2;
    
    if (first <= last) {
        
        if (list[mid].getCardNumber() == key)
        {
            found = true;
            return mid;
        }
        else if (list[mid].getCardNumber() > key)
        {
            return searchForCard(list, first, mid - 1, key);
        }
        else if (list[mid].getCardNumber() < key)
        {
            return searchForCard(list, mid + 1, last, key);
        }
     }
    else {
            return -1;
    }
}

void displaySubmenu() {
    cout << "Submenu:" << endl;
    cout << "1. Delete card" << endl;
    cout << "2. Update" << endl;
    cout << "3. Change status (TODO)" << endl;
    cout << "4. Exit menu" << endl;
    cout << "Please select an option to continue: ";
}

int chooseSubmenuOption() {
    bool flag = 0;
    int option = 0;
    string str = "Must be a number!";
    string str2 = "Must be between 1 and 4!";

    while (!flag)
    {
        try
        {
            cin >> option;
            if (!cin) { throw str; }
            else {
                if (option < 1 || option > 4)
                {
                    throw exceptionMessage();
                    flag = false;
                }
                flag = true;
            }
        }
        catch (string s)
        {
            cout << s << endl;
            // restores the input stream:
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Please select an option to continue: ";
        }
        catch (exceptionMessage ex)
        {
            cout << str2 << endl;
            cout << "Please select an option to continue: ";
        }
    }
    return option;
}


// this function runs checks every 20 seconds (planning to run it in 10 minutes interval) 
// on active cards 
// to determine which card must be displayed.
// uses a separate thread that does not interrupt the main flow.
// TODO: do not display cards as soon as the function determined them. Send them to the queue to wait user's permission to show them.
void run(vector<card> v)
{   
//    // check list while it is not empty. if empty there is nothing to display:
//    while (v.size() > 0)
//    {
//        int minutesEllapsed = 0;
//
//        CardCreationDate dateNow;
//        dateNow.setCreationDate();
//
//        
//
//        for (int i = 0; i < v.size(); i++)
//        {
//            // using overloaded minus operator.
//            minutesEllapsed = v[i].getCreationDate() - dateNow;
//
//            // apprx 10 minutes - 10 hours.
//            if (minutesEllapsed >= 1 && minutesEllapsed < 610 && v[i].getRepetition() == 1)
//            {
//                v[i].print();
//                v[i].setRepetition(2); // todo: add increase repetition func in card
//            }
//
//            // apprx 10 - 34 hours
//            if (minutesEllapsed >= 610 && minutesEllapsed < 2000 && v[i].getRepetition() == 2)
//            {
//                v[i].print();
//                v[i].setRepetition(3); // todo: add increase repetition func in card
//            }
//
//            // apprx 34 - 105 hours (1.5 - 4 days)
//            if (minutesEllapsed >= 2000 && minutesEllapsed < 6320 && v[i].getRepetition() == 3)
//            {
//                v[i].print();
//                v[i].setRepetition(4); // todo: add increase repetition func in card
//            }
//
//            // more than 4 days 
//            if (minutesEllapsed >= 6320 && v[i].getRepetition() == 4)
//            {
//                v[i].print();
//                v[i].setRepetition(5); // todo: add increase repetition func in card
//                // TODO: display message that card was learned and move it to the archive.
//            }
//        }

        //std::this_thread::sleep_for(std::chrono::milliseconds(20000));
    //}
}

void readFromFile(vector<card>& v) {
    int num, rep, mon, day, year, hour, min;
    string ttl, cont, st;
    // Reading data from Storage_active.txt file:
    ifstream data;
    data.open("Storage_active.txt");
    assert(!data.fail());
    int i = 0;
    while (data >> num >> rep, data.ignore(), getline(data, ttl), getline(data, cont), getline(data, st), data >> mon >> day >> year >> hour >> min)
    {
        status tempStatus = convertStringToStatus(st);
        card temp;
        temp.setExistingCard(num, rep, ttl, cont, tempStatus, mon, day, year, hour, min, 0);
        v.push_back(temp);
       /* data >> num >> rep;
        data.ignore();
        getline(data, ttl);
        getline(data, cont);
        getline(data, st);
        data >> mon >> day >> year >> hour >> min;*/
        
        /*if (data.peek() == EOF)
        {
            break;
        }*/
    }
    data.close();
}

void saveInFile(vector<card>& v) {
    // Save in file:
    ofstream outData;
    outData.open("Storage_active.txt");
    assert(!outData.fail());

    for (int i = 0; i < v.size(); i++)
    {
        outData << v[i].getCardNumber() << endl;
        outData << v[i].getRepetition() << endl;
        outData << v[i].getTitle() << endl;
        outData << v[i].getContent() << endl;
        outData << v[i].getStatusString() << endl;
        outData << v[i].getCreationMonth() << endl;
        outData << v[i].getCreationDay() << endl;
        outData << v[i].getCreationYear() << endl;
        outData << v[i].getCreationHours() << endl;
        outData << setfill('0') << setw(2) << v[i].getCreationMinutes() << endl;
    }

    outData.close();
}

