#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int USER_COUNT = 3;

// Parallel arrays store each user's details.
string names[USER_COUNT] = {"Thabo Mokoena", "Lerato Nkosi", "Kabelo Dlamini"};
string accountNumbers[USER_COUNT] = {"1001001", "1001002", "1001003"};
string pins[USER_COUNT] = {"1234", "2468", "1357"};
double balances[USER_COUNT] = {2500.00, 1800.00, 3200.00};

// Finds an account number and returns its array position.
// Returns -1 when the account does not exist.
int findAccount(string accountNumber)
{
    for (int i = 0; i < USER_COUNT; i++)
    {
        if (accountNumbers[i] == accountNumber)
        {
            return i;
        }
    }
    return -1;
}

// Checks the account number and PIN before opening the banking menu.
int login()
{
    string enteredAccount, enteredPin;

    cout << "====================================\n";
    cout << "             GCC BANK\n";
    cout << "====================================\n";

    cout << "Enter account number: ";
    cin >> enteredAccount;

    int userIndex = findAccount(enteredAccount);

    if (userIndex == -1)
    {
        cout << "Account not found. Please check the account number.\n";
        return -1;
    }

    cout << "Enter PIN: ";
    cin >> enteredPin;

    if (enteredPin == pins[userIndex])
    {
        cout << "\nWelcome, " << names[userIndex] << "!\n";
        return userIndex;
    }

    cout << "Incorrect PIN. Access denied.\n";
    return -1;
}

// Displays the options available to the logged-in user.
void displayMenu()
{
    cout << "\n========== GCC BANK MENU ==========\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Send Cash\n";
    cout << "4. Check Balance\n";
    cout << "5. Exit\n";
    cout << "===================================\n";
    cout << "Enter your choice: ";
}

// Reads a number and prevents non-numeric input from stopping the program.
int readMenuChoice()
{
    int choice;

    while (!(cin >> choice))
    {
        cout << "Invalid input. Enter a number from 1 to 5: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return choice;
}

// Reads an amount and rejects non-numeric or non-positive values.
double readAmount()
{
    double amount;

    while (!(cin >> amount) || amount <= 0)
    {
        cout << "Invalid amount. Enter an amount greater than 0: ";

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return amount;
}

// Adds money to the logged-in user's account.
void deposit(int userIndex)
{
    double amount;

    cout << "\nEnter amount to deposit: R";
    amount = readAmount();

    balances[userIndex] = balances[userIndex] + amount;

    cout << "Deposit successful.\n";
    cout << "New balance: R" << balances[userIndex] << "\n";
}

// Removes money only when the account has enough funds.
void withdraw(int userIndex)
{
    double amount;

    cout << "\nEnter amount to withdraw: R";
    amount = readAmount();

    if (amount <= balances[userIndex])
    {
        balances[userIndex] = balances[userIndex] - amount;
        cout << "Withdrawal successful.\n";
        cout << "New balance: R" << balances[userIndex] << "\n";
    }
    else
    {
        cout << "Transaction declined. Insufficient balance.\n";
        cout << "Available balance: R" << balances[userIndex] << "\n";
    }
}

// Transfers money after checking the recipient and the sender's balance.
void sendCash(int senderIndex)
{
    string recipientAccount;
    double amount;

    cout << "\nEnter recipient account number: ";
    cin >> recipientAccount;

    int recipientIndex = findAccount(recipientAccount);

    if (recipientIndex == -1)
    {
        cout << "Transfer failed. Recipient account was not found.\n";
        return;
    }

    if (recipientIndex == senderIndex)
    {
        cout << "Transfer failed. You cannot send cash to your own account.\n";
        return;
    }

    cout << "Enter amount to send: R";
    amount = readAmount();

    if (amount <= balances[senderIndex])
    {
        balances[senderIndex] = balances[senderIndex] - amount;
        balances[recipientIndex] = balances[recipientIndex] + amount;

        cout << "Cash sent successfully to " << names[recipientIndex] << ".\n";
        cout << "Your new balance: R" << balances[senderIndex] << "\n";
    }
    else
    {
        cout << "Transfer declined. Insufficient balance.\n";
    }
}

// Displays the current balance of the logged-in user.
void checkBalance(int userIndex)
{
    cout << "\nAccount holder: " << names[userIndex] << "\n";
    cout << "Account number: " << accountNumbers[userIndex] << "\n";
    cout << "Available balance: R" << balances[userIndex] << "\n";
}

int main()
{
    int userIndex = login();

    if (userIndex == -1)
    {
        cout << "\nPlease restart the program and try again.\n";
        return 0;
    }

    int choice = 0;

    // The menu repeats until the user selects option 5.
    while (choice != 5)
    {
        displayMenu();
        choice = readMenuChoice();

        switch (choice)
        {
            case 1:
                deposit(userIndex);
                break;

            case 2:
                withdraw(userIndex);
                break;

            case 3:
                sendCash(userIndex);
                break;

            case 4:
                checkBalance(userIndex);
                break;

            case 5:
                cout << "\nThank you for banking with GCC BANK. Goodbye!\n";
                break;

            default:
                cout << "Invalid menu choice. Please select 1 to 5.\n";
        }
    }

    return 0;
}
