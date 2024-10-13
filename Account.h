
/*Pseudocode
-Include necessary libraries
-Define a structure named Date to store date details (month, day, year)
-Define a structure named Person to store account owner's information (name, date of birth, address)

~~Account~~ 
    PRIVATE:
       -accountNumber : int
       -numOwners : int
       -ownerPtr : Person*
       -balance : double 
       -accountCounter : static int 
       
    PUBLIC
        +Account(numberOwners: int, amount: double ) : Account
        +~Account()
        
        +withdraw(amount : double) : int
        +deposit(amount : double) : int 
        +setOwner(ind : int,  p : Person) : void 
        
        +getOwner(ind : int) const : Person
        +getAccountNumber() const : int
        +getBalance() const : double 
        +getNumOwners() const : double 
~~END class~~
*/

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
using namespace std;

//Stores every detail related to the date
struct Date
{
   int month;
   int day;
   int year;
};

struct Person //Stores account owner’s info including their name, date of birth, and address.
{
   string name;
   Date DOB;
   string address;
};

class Account {
    private:
       int accountNumber; // Stores the unique account number.
       int numOwners; //Number of account co-owners (account can have more than one owner)
       Person* ownerPtr; //OwnerPtr points to an array of Person, where Person is a structure.
       double balance; //Stores the balance of the account.
       static int accountCounter; //Initialized at 1000, incremented at each account creation, used to automate account number assignment.
       
    public:
        //Constructor which sets the accountNumber, sets numOwners,and sets balance to amount.
        Account(int numberOwners, double amount);
        //Destructor to free dynamically allocated memory.
        ~Account();
        
        int withdraw(double amount); //Withdraws the specified amount from the account.
        int deposit(double amount); //Deposits the specified amount into the account.
        void setOwner(int ind, Person p); //Sets the owner information at the specified index.
        
        //Accessor methods for retrieving account information.
        Person getOwner(int ind) const;
        int getAccountNumber() const;
        double getBalance() const;
        int getNumOwners() const;
        void addOwner(Person newOwner);
        int delOwner(Person ownerRemoved);
 };
 
#endif //ACCOUNT_H




