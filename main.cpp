/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/*Program Statement
A Program to carry out functions of a bank account
*/

/*Pseudocode
-Include necessary header files
-Define constants:
    MAX_NUM_ACCOUNTS = 4
-Declare global variables:
    accountArray[MAX_NUM_ACCOUNTS] of pointers to Account objects


~~~MAIN Function~~~
    Declare variables:
        choice

    Loop until choice is 8 or (choice is between 1 and 7):
        Call displayMenu() to show menu options
        Input choice from user

        If choice is 8:
            Clean up dynamically allocated memory for each non-null element in accountArray
            Exit program with success status

        Switch through choices:
            Case 1: 
                Iterate over accountArray:
                    If an empty slot is found:
                        Input number of owners and initial amount
                        Create new Account object with given parameters and store in the empty slot
                        Input and set details for each owner
                        Output "Account #<account number> created"
                        Break out of loop
                        
                If no empty slot found:
                    Output "Max number of accounts reached, cannot add a new account"
            
            Case 2: Deposit
                Input account number
                
                Call findAccount() to get index of account
                
                If account index is valid:
                    Input amount to deposit
                    Call deposit() method of account and output new balance or error message
                    
            Case 3: // Withdraw
            
                Input account number
                
                Call findAccount() to get index of account
                If account index is valid:
                    Input amount to withdraw
                    Call withdraw() method of account and output new balance or error message
                    
            Case 4: // Display
                Iterate over accountArray:
                    If account is not null:
                        Output account number
                        Output details of each owner
                        Output current balance
            
            Case 5: // Delete owner
                Input account number
                Call findAccount() to get index of account
                If account index is valid:
                    Input details of owner to delete
                    Call delOwner() method of account and output appropriate message
                    
            Case 6: // Add owner
                Input account number
                Call findAccount() to get index of account
                If account index is valid:
                    Input details of new owner
                    Call addOwner() method of account and output appropriate message
                    
            Case 7: // Delete account
                Input account number
                Call findAccount() to get index of account
                If account index is valid:
                    Delete account object at index and shift remaining accounts
                    Output "Account deleted"
                    
    Clean up dynamically allocated memory for each non-null element in accountArray
    Return success status
~~CLOSE MAIN~~

~~displayMenu Function~~
    PRINT: "Menu"
    PRINT: "----"
    PRINT: "1->Create account 2->Deposit   3->Withdraw     4->Display "
    PRINT: "5->Delete owner   6->Add owner 7->Delete accnt 8->Quit"

~~CLOSE displayMenu~~


~~findAccount Function~~
    FOR each index i from 0 to MAX_NUM_ACCOUNTS - 1:
        If accountArray[i] is not null and accountArray[i].getAccountNumber() equals accountNumber:
            Return i
    END FOR
    
    Return -1
~~CLOSE findAccount
*/

#include "Account.h" //Include the Account header file 
#include <iostream>
#include <iomanip>
#include <string>

const int MAX_NUM_ACCOUNTS = 4; //Maximum number of accounts
Account* accountArray[MAX_NUM_ACCOUNTS] = {nullptr}; //Global array of pointers to Account

//Function to display user's menu options
void displayMenu(); 

//Function to find the account inputted by user
int findAccount(int accountNumber);

int main() {
    int choice; //Stores user's choice
    
    do {
        displayMenu(); //Display the menu
        
        //Get and store user's choice
        cout << "";
        cin >> choice;
        
        //If user chooses to exit
        if (choice == 8) {
            
            //Clean up dynamically allocated memory
            for (int i = 0; i < MAX_NUM_ACCOUNTS; i++) {
                if (accountArray[i] != nullptr) {
                    delete accountArray[i];
                }
            }
            
            exit(EXIT_SUCCESS); //Exit program following user's choice
        }
        
        //Switch through user's choice case by case
        switch (choice){
            case 1:{ //Create new account
                
                //Check if maximum number of accounts is reached
                int placeHolder = -1; 
                for (int i = 0; i < MAX_NUM_ACCOUNTS; i++) {
                    if (accountArray[i] == nullptr) {
                        placeHolder = i; //Finds an empty slot until none is present
                        break;
                    }
                }
                
                //If no more empty spaces, print error message
                if (placeHolder == -1) {
                    cout << "Max number of accounts reached, cannot add a new account" << endl;
                    break; //Return to displaying the menu
                }
                
                //Prompt user for account details and info
                int numOwners; 
                double amount;
                cout << "Enter number of owners: ";
                cin >> numOwners;
                
                //Get amount to deposit
                cout << "Enter amount: ";
                cin >> amount;
                
                //Create new account
                accountArray[placeHolder] = new Account(numOwners, amount);
            
                cin.ignore(); //Ignore previous newline character
                
                //Prompt for and set owners' details
                for (int i = 0; i < numOwners; i++) {
                    Person owner;
                    cout << "Enter owner's name: ";
                    getline(cin, owner.name); //Read entire line including spaces for the name
            
                    cout << "Enter owner's DOB, month, day then year: ";
                    cin >> owner.DOB.month >> owner.DOB.day >> owner.DOB.year;
            
                    cout << "Enter owner's address: ";
                    cin.ignore(); //Ignore the previous input 
                    getline(cin, owner.address);
                    
                    //Set info and create new account
                    accountArray[placeHolder]->setOwner(i, owner);
                }
                
                //Display account number and acknowledge creation
                cout << "Account #" << accountArray[placeHolder]->getAccountNumber() << " created" << endl;
                break;
            }
            
            
            case 2 : { //Deposit funds into an account
                int accountNumber;
                double amount;
                
                cout << "Enter account number: ";
                cin >> accountNumber;
                
                //Find the index of the account in the array
                int accountIndex = findAccount(accountNumber);
                if (accountIndex == -1) {
                    cout << "No such account" << endl;
                    break;
                }
                
                //Prompt user for the amount to deposit
                cout << "Enter amount: ";
                cin >> amount;
                int result = accountArray[accountIndex]->deposit(amount);
                
                //Attempt to deposit the specified amount into the account
                if (result == 0) {
                    cout << "New balance is $" << fixed << setprecision(2) 
                    << showpoint << accountArray[accountIndex]->getBalance() << endl;
                } 
                else { // Display the result of the deposit operation
                    
                    if (result == 1){
                        cout << "Amount cannot be negative, deposit not executed";
                    }
                    
                    cout << endl;
                }
                
                break;
            }
            
            case 3 : { //Withdraw funds from an account
                int accountNumber;
                cout << "Enter account number: ";
                cin >> accountNumber;
                
                //Find the index of the account in the array
                int accountIndex = findAccount(accountNumber);
                if (accountIndex == -1) {
                    cout << "No such account" << endl;
                    break;
                }
                
                double amount;
                cout << "Enter amount: ";
                cin >> amount;
                
                //Attempt to withdraw the specified amount from the account
                int result = accountArray[accountIndex]->withdraw(amount);
                if (result == 0) { //If withdrawal is successful, display the new balance
                    cout << "New balance is $" << fixed << setprecision(2) << showpoint 
                    << accountArray[accountIndex]->getBalance() << endl;
                } 
                else {
                    
                    //Display if withdrawal failed due to insufficient balance or negative amount
                    if (result == 1) {
                        cout << "Insufficient balance, withdrawal not executed";
                    }
                    else {
                        cout << "Amount cannot be negative, withdrawal not executed";
                    }
                    
                    cout << endl;
                }
                
                break;
            }
            
            case 4: { //Display details of all active accounts
                for (int i = 0; i < MAX_NUM_ACCOUNTS; i++) {
                    
                    //Check if the account at index i is active
                    if (accountArray[i] != nullptr) {
                        cout << "Account Number: " << accountArray[i]->getAccountNumber() << endl;
                        cout << "--------------" << endl;
                        
                        //Display details of each owner for the account
                        for (int j = 0; j < accountArray[i]->getNumOwners(); j++) {
                            Person owner = accountArray[i]->getOwner(j);
                            cout << "*Name: " << owner.name << ", DOB: " << owner.DOB.month << "/" << owner.DOB.day << "/" << owner.DOB.year << endl;
                            cout << "Address: " << owner.address << endl;
                        }
                        
                        //Display the current balance of the account
                        cout << "*Balance: $" << fixed << setprecision(2) << showpoint
                        << accountArray[i]->getBalance() << " " << endl;
                    }
                }
                
                break;
            }
            
            
            case 5 : { //Delete owner
                int accountNumber;
                cout << "Enter account number: ";
                cin >> accountNumber;
                
                //Find the index of the account in the array
                int accountIndex = findAccount(accountNumber);
                if (accountIndex == -1) {
                    cout << "No such account" << endl;
                    break;
                }
            
                //Check if there is only one owner in the account
                if (accountArray[accountIndex]->getNumOwners() == 1) {
                    cout << "Cannot delete owner, there is only one owner in the account" << endl;
                    break;
                }
                
                //Prompt user for owner's details
                Person ownerToDelete;
                cout << "Enter owner's name: ";
                cin >> ownerToDelete.name;
                
                cout << "Enter owner's DOB, month, day then year: ";
                cin >> ownerToDelete.DOB.month >> ownerToDelete.DOB.day >> ownerToDelete.DOB.year;
                
                cout << "Enter owner's address: ";
                cin.ignore();
                getline(cin, ownerToDelete.address);
                
                //Attempt to delete the specified owner from the account
                int delStatus = accountArray[accountIndex]->delOwner(ownerToDelete);
                if (delStatus == 0) {
                    cout << "Owner deleted successfully" << endl;
                } 
                else if (delStatus == 1) {
                    cout << "Owner not found among the owners" << endl;
                } 
                else {
                    cout << "Cannot delete owner, there is only one owner left in the account" << endl;
                }
                
                break;
            }
            
            case 6: { //Add a new owner to an existing account
                int accountNumber;
                cout << "Enter account number: ";
                cin >> accountNumber;
                
                //Find the index of the account in the array
                int accountIndex = findAccount(accountNumber);
                if (accountIndex == -1) {
                    cout << "No such account" << endl;
                break;
                }
                
                //Prompt user for details of the new owner
                Person newOwner;
                cout << "Enter new owner's name: ";
                cin >> newOwner.name;
                
                cout << "Enter new owner's DOB, month, day then year: ";
                cin >> newOwner.DOB.month >> newOwner.DOB.day >> newOwner.DOB.year;
                
                cout << "Enter new owner's address: ";
                cin.ignore();
                getline(cin, newOwner.address);
                
                //Add the new owner to the account
                accountArray[accountIndex]->addOwner(newOwner);
                cout << "Owner added successfully" << endl;
                break;
            }
            case 7: { //Delete an account
                int accountNumber;
                cout << "Enter account number: ";
                cin >> accountNumber;
                
                //Find the index of the account in the array
                int accountIndex = findAccount(accountNumber);
                if (accountIndex == -1) {
                    cout << "No such account" << endl;
                    break;
                }
                
                //Delete the account
                delete accountArray[accountIndex];
                accountArray[accountIndex] = nullptr;
                
                //Shift remaining accounts in the array
                for (int i = accountIndex; i < MAX_NUM_ACCOUNTS - 1; i++) {
                    accountArray[i] = accountArray[i + 1];
                }
                
                accountArray[MAX_NUM_ACCOUNTS - 1] = nullptr; //Clear the last element
                
                cout << "Account deleted" << endl;
                break;
            }
            
            case 8: { //Quit the program
                
                //Clean up dynamically allocated memory
                for (int i = 0; i < MAX_NUM_ACCOUNTS; i++) {
                    if (accountArray[i] != nullptr) {
                        delete accountArray[i];
                    }
                }
                
                exit(EXIT_SUCCESS); //Exit program following user's choice
                
                break;
            }
            
        }
        
    } while (choice != 8 && (choice >= 1 && choice <= 7));
    
    //Clean up dynamically allocated memory
    for (int i = 0; i < MAX_NUM_ACCOUNTS; i++) {
        if (accountArray[i] != nullptr){
            delete accountArray[i];
        }
    }
    
    return 0;
}


//Display the menu in the specified format
void displayMenu() {
    cout<<"Menu"<<endl;
    cout<<"----"<<endl;
    cout<<"1->Create account 2->Deposit   3->Withdraw     4->Display "<<endl;
    cout<<"5->Delete owner   6->Add owner 7->Delete accnt 8->Quit    "<<endl;
}

//Function to find the index of an account in the array using its account number
int findAccount(int accountNumber) {
    for (int i = 0; i < MAX_NUM_ACCOUNTS; i++) {
        if (accountArray[i] != nullptr && accountArray[i]->getAccountNumber() == accountNumber){
            return i;    
        }
    }
    
    return -1; //Return -1 if account is not found
}





