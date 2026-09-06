# Bank Account Management Program

A simple command-line C++ program for managing bank accounts. It supports creating accounts, making deposits and withdrawals, displaying account details, and adding/removing account co-owners.

## Files

| File | Description |
|---|---|
| `main.cpp` | Program entry point; runs the menu loop and handles user input |
| `Account.h` | Declares the `Account` class and the `Date` / `Person` structs |
| `Account.cpp` | Implements the `Account` class methods |

## Requirements

- A C++ compiler that supports C++11 or later (e.g. `g++`, `clang++`)

## Building

From the directory containing all three files, compile with:

```bash
g++ -o bank_program main.cpp Account.cpp
```

This produces an executable named `bank_program` (use `bank_program.exe` on Windows).

## Running

```bash
./bank_program
```

You'll be shown a menu of options:

```
Menu
----
1->Create account 2->Deposit   3->Withdraw     4->Display
5->Delete owner   6->Add owner 7->Delete accnt 8->Quit
```

Enter the number corresponding to the action you want, then follow the prompts.

### 1. Create account

- Enter the number of owners and the initial deposit amount.
- For each owner, enter their **name**, **date of birth** (month, day, year — space separated), and **address**.
- The program assigns a unique account number automatically, starting at **1000** and incrementing with each new account.
- Up to **4 accounts** can exist at once. If the limit is reached, you'll see a message and no account will be created.

### 2. Deposit

- Enter the account number to deposit into.
- Enter the amount. Must be greater than 0.
- On success, the new balance is displayed.

### 3. Withdraw

- Enter the account number to withdraw from.
- Enter the amount. Must be greater than 0 and no more than the current balance.
- On success, the new balance is displayed; otherwise an error message explains why the withdrawal failed (insufficient balance or invalid amount).

### 4. Display

- Lists every active account, showing:
  - Account number
  - Each owner's name, date of birth, and address
  - Current balance

### 5. Delete owner

- Enter the account number.
- Enter the owner's name, date of birth, and address (must match exactly).
- An account must always have at least one owner — you cannot delete the last remaining owner.

### 6. Add owner

- Enter the account number.
- Enter the new owner's name, date of birth, and address.
- The owner is appended to the account's list of owners.

### 7. Delete account

- Enter the account number to remove.
- The account and its allocated memory are freed, and remaining accounts shift down to fill the empty slot.

### 8. Quit

- Frees all remaining allocated memory and exits the program.

## Notes

- Account numbers start at 1000 and increase by 1 for each account created during the program's run (numbers are not reused after deletion).
- The program supports a maximum of 4 open accounts at any given time.
- Date of birth is entered as three separate values: month, then day, then year (e.g. `4 15 2001` for April 15, 2001).
- Owner name/address matching for deletion is case-sensitive and must match exactly what was originally entered.
