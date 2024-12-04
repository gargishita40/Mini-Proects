#include <iostream>
#include <string>
#include <fstream>
#include <cctype> // For isdigit
using namespace std;

class Account {
private:
    int account_number;
    string holder_name;
    double balance;
    string pin;

    // Helper function to validate a 4-digit numeric PIN
    bool isValidPIN(const string& pin) {
        if (pin.length() != 4) return false;
        for (char c : pin) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

public:
    // Create a new account
    void createAccount() {
        cin.ignore(); // Clear input buffer
        cout << "Enter Your Name: ";
        getline(cin, holder_name);
        cout << "Enter Account Number: ";
        cin >> account_number;
        cout << "Enter the Current Balance: ";
        cin >> balance;

        cout << "Set a 4-digit PIN: ";
        cin >> pin;
        if (!isValidPIN(pin)) {
            cout << "Invalid PIN. Please enter a 4-digit number.\n";
            pin.clear();
            return;
        }

        cout << "Account created successfully!\n";
    }

    // Display account details
    void displayAccount() const {
        cout << "\nAccount Number: " << account_number
             << "\nHolder Name: " << holder_name
             << "\nBalance: " << balance << "\n";
    }

    // Deposit money
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount. Must be positive.\n";
            return;
        }
        balance += amount;
        cout << "Amount $" << amount << " deposited successfully.\n";
    }

    // Withdraw money
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount. Must be positive.\n";
            return;
        }
        if (amount > balance) {
            cout << "Insufficient Balance!\n";
        } else {
            balance -= amount;
            cout << "Withdrawn $" << amount << " successfully.\n";
        }
    }

    // Get account number
    int getAccountNumber() const {
        return account_number;
    }

    // Verify PIN
    bool verifyPIN(const string& enteredPIN) const {
        return pin == enteredPIN;
    }

    // Save account details to file
    void saveToFile() {
        ofstream file("accounts.txt", ios::app);
        if (!file) {
            cout << "Error opening file for saving account!\n";
            return;
        }
        file << account_number << " " << holder_name << " " << balance << " " << pin << "\n";
        file.close();
    }

    // Load account from file
    static bool loadFromFile(int accNum, Account &account) {
        ifstream file("accounts.txt");
        if (!file) {
            cout << "Error opening file for loading account!\n";
            return false;
        }
        while (file >> account.account_number >> ws) {
            getline(file, account.holder_name);
            file >> account.balance >> account.pin;
            if (account.account_number == accNum) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    // Update account details in file
    static void updateFile(const Account &updatedAccount) {
        ifstream file("accounts.txt");
        if (!file) {
            cout << "Error opening file for updating!\n";
            return;
        }
        ofstream tempFile("temp.txt");
        Account account;

        while (file >> account.account_number >> ws) {
            getline(file, account.holder_name);
            file >> account.balance >> account.pin;

            if (account.account_number == updatedAccount.getAccountNumber()) {
                tempFile << updatedAccount.account_number << " " << updatedAccount.holder_name << " "
                         << updatedAccount.balance << " " << updatedAccount.pin << "\n";
            } else {
                tempFile << account.account_number << " " << account.holder_name << " "
                         << account.balance << " " << account.pin << "\n";
            }
        }
        file.close();
        tempFile.close();

        // Replace the old file with the updated one
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }
};

int main() {
    Account account;
    int choice;

    do {
        cout << "\n--- Banking System ---\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Display Account Details\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                account.createAccount();
                account.saveToFile();
                break;
            case 2: {
                int accNum;
                string enteredPIN;
                double amount;

                cout << "Enter Account Number: ";
                cin >> accNum;

                if (Account::loadFromFile(accNum, account)) {
                    cout << "Enter PIN: ";
                    cin >> enteredPIN;

                    if (account.verifyPIN(enteredPIN)) {
                        cout << "Enter Amount to Deposit: ";
                        cin >> amount;
                        account.deposit(amount);
                        Account::updateFile(account);
                    } else {
                        cout << "Incorrect PIN!\n";
                    }
                } else {
                    cout << "Account Not Found!\n";
                }
                break;
            }
            case 3: {
                int accNum;
                string enteredPIN;
                double amount;

                cout << "Enter Account Number: ";
                cin >> accNum;

                if (Account::loadFromFile(accNum, account)) {
                    cout << "Enter PIN: ";
                    cin >> enteredPIN;

                    if (account.verifyPIN(enteredPIN)) {
                        cout << "Enter Amount to Withdraw: ";
                        cin >> amount;
                        account.withdraw(amount);
                        Account::updateFile(account);
                    } else {
                        cout << "Incorrect PIN!\n";
                    }
                } else {
                    cout << "Account Not Found!\n";
                }
                break;
            }
            case 4: {
                int accNum;
                string enteredPIN;

                cout << "Enter Account Number: ";
                cin >> accNum;

                if (Account::loadFromFile(accNum, account)) {
                    cout << "Enter PIN: ";
                    cin >> enteredPIN;

                    if (account.verifyPIN(enteredPIN)) {
                        account.displayAccount();
                    } else {
                        cout << "Incorrect PIN!\n";
                    }
                } else {
                    cout << "Account Not Found!\n";
                }
                break;
            }
            case 5:
                cout << "Thank you for using the Banking System!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
