
/*Pseudocode
    accountCounter = 1000
    accountNumber, numOwners, ownerPtr, balance
    
    Function Account(numberOwners, amount)
        accountNumber = accountCounter
        Increment accountCounter
        numOwners = numberOwners
        Allocate memory for ownerPtr with size numOwners
        balance = amount
    
    Function ~Account()
        Free memory allocated to ownerPtr
        ownerPtr = nullptr
    
    Function withdraw(amount)
        if amount ≤ 0 then
            return 2
        else if amount > balance then
            return 1
        else
            balance = balance - amount
            return 0
    
    Function deposit(amount)
        if amount ≤ 0 then
            return 1
        else
            balance = balance + amount
            return 0
    
    Function setOwner(ind, p)
        ownerPtr[ind] = p
    
    Function getOwner(ind)
        Return ownerPtr[ind]
    
    Function getAccountNumber()
        Return accountNumber
    
    Function getBalance()
        Return balance
    
    Function getNumOwners()
        Return numOwners
    
    Function addOwner(newOwner)
        Allocate memory for ownerPtr with size numOwners + 1
        For i = 0 to numOwners - 1 do
            ownerPtr[i] = ownerPtr[i]
        ownerPtr[numOwners] = newOwner
        Free memory allocated to ownerPtr
        ownerPtr = new array
        Increment numOwners by 1
    
    Function delOwner(ownerToRemove)
        indexToRemove = -1
        For i = 0 to numOwners - 1 do
            If ownerPtr[i] matches ownerToRemove then
                indexToRemove = i
                Break the loop
        If indexToRemove = -1 then
            Return 1
        If numOwners = 1 then
            Return 2
        Allocate memory for ownerPtr with size numOwners - 1
        newIndex = 0
        For i = 0 to numOwners - 1 do
            If i ≠ indexToRemove then
                ownerPtr[newIndex] = ownerPtr[i]
                Increment newIndex by 1
        Free memory allocated to ownerPtr
        ownerPtr = new array
        Decrement numOwners by 1

*/

#include "Account.h"
#include <iostream>

//Initialize static member variable for generating unique account numbers
int Account::accountCounter = 1000;

//Constructor for Account class
Account::Account(int numberOwners, double amount) {
    accountNumber = accountCounter++; //Assign unique account number
    numOwners = numberOwners; //Set number of owners
    ownerPtr = new Person[numOwners]; //Allocate memory for array of owners
    balance = amount; //Set initial balance
}

//Destructor for Account class
Account::~Account() {
    delete[] ownerPtr; //Deallocate memory for array of owners
    ownerPtr = nullptr; //Reset owner pointer to null
}

//Method to withdraw money from the account
int Account::withdraw(double amount) {
    if (amount <= 0){
        return 2; //Invalid amount
    }
    
    else if (amount > balance){
        return 1; //Insufficient amount in account to withdraw
    }
        
    else {
        balance -= amount;
        return 0; //Successfully withdraw
    }
}

int Account::deposit(double amount) {
    if (amount <= 0){
        return 1; //Invalid amount
    }
    
    else {
        balance += amount; //Update balance after deposit
        return 0; //Successful deposit
    }
}

//Method to set owner at a specific index
void Account::setOwner(int ind, Person p) {
    ownerPtr[ind] = p;
}

//Method to get owner at a specific index
Person Account::getOwner(int ind) const {
    return ownerPtr[ind];
}

//Method to get account number
int Account::getAccountNumber() const {
    return accountNumber;
}

//Method to get current balance
double Account::getBalance() const {
    return balance;
}

//Method to get amount of owners
int Account::getNumOwners() const {
    return numOwners;
}

//Method to add a new owner to the account
void Account::addOwner(Person newOwner) {
    Person* newOwnerPtr = new Person[numOwners + 1]; //Allocate memory for updated array of owners
    
    //Copy existing owners to new array
    for (int i = 0; i < numOwners; i++) {
        newOwnerPtr[i] = ownerPtr[i];
    }

    //Add new owner to the end of the array
    newOwnerPtr[numOwners] = newOwner;

    delete[] ownerPtr; //Deallocate memory for old array of owners
    ownerPtr = nullptr;

    ownerPtr = newOwnerPtr; //Update owner pointer to point to new array
    numOwners++; //Increase owner count
}

//Method to delete an owner from the account
int Account::delOwner(Person ownerToRemove) {
    int indexToRemove = -1;
    
    //Find index of owner to remove
    for (int i = 0; i < numOwners; i++) {
        if (ownerPtr[i].name == ownerToRemove.name && ownerPtr[i].DOB.day == ownerToRemove.DOB.day && 
            ownerPtr[i].DOB.month == ownerToRemove.DOB.month && ownerPtr[i].DOB.year == ownerToRemove.DOB.year &&
            ownerPtr[i].address == ownerToRemove.address) {
            indexToRemove = i;
            break;
        }
    }
    
    //Return if owner not found
    if (indexToRemove == -1) {
        return 1;
    }
    
    //Return if there's only one owner in the account
    if (numOwners == 1) {
        return 2;
    }
    
    //Create new array of owners with reduced size
    Person* newOwnerPtr = new Person[numOwners - 1];
    
    //Copy owners except the one to be removed
    int newIndex = 0;
    for (int i = 0; i < numOwners; i++) {
        if (i != indexToRemove) {
            newOwnerPtr[newIndex] = ownerPtr[i];
            newIndex++;
        }
    }

    delete[] ownerPtr; //Deallocate memory for old array of owners
    ownerPtr = nullptr;

    ownerPtr = newOwnerPtr; //Update owner pointer to point to new array

    numOwners--; //Decrease owner count

    return 0; //Successfully deleted
}




