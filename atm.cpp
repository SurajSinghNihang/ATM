#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

class Account
{
private:
    string accountNumber;
    int pin;
    double balance;

public:
    Account(string accNum, int p, double bal) : accountNumber(accNum), pin(p), balance(bal) {}

    bool validatePin(int inputPin)
    {
        return pin == inputPin;
    }

    double getBalance()
    {
        return balance;
    }

    bool withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            return true;
        }
        return false;
    }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
        }
    }
};

class ATM
{
private:
    Account *currentAccount;

    void clearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void waitForEnter()
    {
        cout << "\nPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

public:
    ATM() : currentAccount(nullptr)
    {
        // Initialize with a sample account
        currentAccount = new Account("123456789", 1234, 1000.0);
    }

    ~ATM()
    {
        delete currentAccount;
    }

    void start()
    {
        while (true)
        {
            clearScreen();
            cout << "=== Welcome to ATM System ===\n\n";

            int inputPin;
            cout << "Enter PIN (1234 for demo): ";
            cin >> inputPin;

            if (currentAccount->validatePin(inputPin))
            {
                displayMenu();
            }
            else
            {
                cout << "Invalid PIN!\n";
                waitForEnter();
            }
        }
    }

    void displayMenu()
    {
        while (true)
        {
            clearScreen();
            cout << "=== ATM Menu ===\n";
            cout << "1. Check Balance\n";
            cout << "2. Withdraw Money\n";
            cout << "3. Deposit Money\n";
            cout << "4. Exit\n\n";
            cout << "Enter choice (1-4): ";

            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
                checkBalance();
                break;
            case 2:
                withdraw();
                break;
            case 3:
                deposit();
                break;
            case 4:
                cout << "\nThank you for using our ATM. Goodbye!\n";
                exit(0);
            default:
                cout << "\nInvalid choice!\n";
            }
            waitForEnter();
        }
    }

    void checkBalance()
    {
        cout << "\nCurrent Balance: $" << fixed << setprecision(2)
             << currentAccount->getBalance() << endl;
    }

    void withdraw()
    {
        double amount;
        cout << "\nEnter amount to withdraw: $";
        cin >> amount;

        if (currentAccount->withdraw(amount))
        {
            cout << "\nWithdrawal successful!\n";
            cout << "Remaining balance: $" << currentAccount->getBalance() << endl;
        }
        else
        {
            cout << "\nWithdrawal failed! Invalid amount or insufficient balance.\n";
        }
    }

    void deposit()
    {
        double amount;
        cout << "\nEnter amount to deposit: $";
        cin >> amount;

        currentAccount->deposit(amount);
        cout << "\nDeposit successful!\n";
        cout << "New balance: $" << currentAccount->getBalance() << endl;
    }
};

int main()
{
    ATM atm;
    atm.start();
    return 0;
}