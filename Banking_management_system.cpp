#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

class Account;

string getCurrentTimestamp() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return string(buf);
}

class Transaction {
private:
    int transactionId;
    string type; 
    double amount;
    string timestamp;
    string details;

public:
    Transaction(int id, string type, double amt, string det)
        : transactionId(id), type(type), amount(amt), details(det) {
        timestamp = getCurrentTimestamp();
    }

    void display() const {
        cout << left << setw(8) << transactionId
             << setw(20) << timestamp
             << setw(15) << type
             << "$" << fixed << setprecision(2) << setw(10) << amount
             << details << endl;
    }
};

class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactionHistory;
    int nextTransactionId;

public:
    Account(int accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance), nextTransactionId(101) {
        if (initialBalance > 0) {
            transactionHistory.emplace_back(nextTransactionId++, "Deposit", initialBalance, "Initial Account Opening");
        }
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        transactionHistory.emplace_back(nextTransactionId++, "Deposit", amount, "Cash Deposit");
        cout << "Successfully deposited $" << fixed << setprecision(2) << amount << ". New Balance: $" << balance << "\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Transaction Failed: Insufficient funds.\n";
            return false;
        }
        balance -= amount;
        transactionHistory.emplace_back(nextTransactionId++, "Withdrawal", amount, "ATM Cash Withdrawal");
        cout << "Successfully withdrew $" << fixed << setprecision(2) << amount << ". Remaining Balance: $" << balance << "\n";
        return true;
    }

    bool transfer(Account& targetAccount, double amount) {
        if (amount <= 0) {
            cout << "Invalid transfer amount.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Transfer Failed: Insufficient funds.\n";
            return false;
        }

        balance -= amount;
        string outDetail = "Transfer to Acc #" + to_string(targetAccount.getAccountNumber());
        transactionHistory.emplace_back(nextTransactionId++, "Transfer Out", amount, outDetail);

        targetAccount.balance += amount;
        string inDetail = "Transfer from Acc #" + to_string(accountNumber);
        targetAccount.transactionHistory.emplace_back(targetAccount.nextTransactionId++, "Transfer In", amount, inDetail);

        cout << "Successfully transferred $" << fixed << setprecision(2) << amount 
             << " to Account #" << targetAccount.getAccountNumber() << "\n";
        return true;
    }

    void displayAccountInfo() const {
        cout << "\n-------------------------------------------------------------\n";
        cout << " Account Details for Account #" << accountNumber << "\n";
        cout << " Current Balance: $" << fixed << setprecision(2) << balance << "\n";
        cout << "-------------------------------------------------------------\n";
        cout << left << setw(8) << "Txn ID"
             << setw(20) << "Date & Time"
             << setw(15) << "Type"
             << setw(11) << "Amount"
             << "Details" << endl;
        cout << "-------------------------------------------------------------\n";

        if (transactionHistory.empty()) {
            cout << " No transaction history available.\n";
        } else {
            for (const auto& txn : transactionHistory) {
                txn.display();
            }
        }
        cout << "-------------------------------------------------------------\n";
    }
};

class Customer {
private:
    int customerId;
    string name;
    string email;
    vector<Account> accounts;

public:
    Customer(int id, string name, string email)
        : customerId(id), name(name), email(email) {}

    int getCustomerId() const { return customerId; }
    string getName() const { return name; }

    void addAccount(int accNum, double initialBalance) {
        accounts.emplace_back(accNum, initialBalance);
        cout << "Account #" << accNum << " created successfully for " << name << ".\n";
    }

    Account* getAccount(int accNum) {
        for (auto& acc : accounts) {
            if (acc.getAccountNumber() == accNum) {
                return &acc;
            }
        }
        return nullptr;
    }

    void displayCustomerProfile() const {
        cout << "\n=============================================================\n";
        cout << " CUSTOMER PROFILE\n";
        cout << "=============================================================\n";
        cout << " Customer ID : " << customerId << "\n";
        cout << " Name        : " << name << "\n";
        cout << " Email       : " << email << "\n";
        cout << " Total Accounts: " << accounts.size() << "\n";

        for (const auto& acc : accounts) {
            acc.displayAccountInfo();
        }
    }
};

class BankSystem {
private:
    vector<Customer> customers;
    int nextCustomerId;
    int nextAccountNumber;

public:
    BankSystem() : nextCustomerId(1001), nextAccountNumber(5001) {}

    Customer* createCustomer(string name, string email) {
        customers.emplace_back(nextCustomerId, name, email);
        cout << "Customer created successfully! Assigned Customer ID: " << nextCustomerId << "\n";
        nextCustomerId++;
        return &customers.back();
    }

    void createAccount(int customerId, double initialDeposit) {
        Customer* cust = findCustomer(customerId);
        if (cust) {
            cust->addAccount(nextAccountNumber++, initialDeposit);
        } else {
            cout << "Customer ID not found.\n";
        }
    }

    Customer* findCustomer(int customerId) {
        for (auto& cust : customers) {
            if (cust.getCustomerId() == customerId) {
                return &cust;
            }
        }
        return nullptr;
    }

    Account* findAccount(int accNum) {
        for (auto& cust : customers) {
            Account* acc = cust.getAccount(accNum);
            if (acc) return acc;
        }
        return nullptr;
    }
};

int main() {
    BankSystem bank;

    cout << "=== BANKING SYSTEM DEMO ===\n\n";

    cout << "-- Creating Customers --\n";
    Customer* alice = bank.createCustomer("Alice Smith", "alice@example.com");
    Customer* bob = bank.createCustomer("Bob Jones", "bob@example.com");

    cout << "\n-- Opening Accounts --\n";
    bank.createAccount(1001, 1000.00); 
    bank.createAccount(1002, 500.00);  

    Account* aliceAcc = bank.findAccount(5001);
    Account* bobAcc = bank.findAccount(5002);

    cout << "\n-- Performing Transactions --\n";
    if (aliceAcc && bobAcc) {
        cout << "\n[1] Alice deposits $250.00:\n";
        aliceAcc->deposit(250.00);

        cout << "\n[2] Alice withdraws $100.00:\n";
        aliceAcc->withdraw(100.00);

        cout << "\n[3] Alice transfers $300.00 to Bob:\n";
        aliceAcc->transfer(*bobAcc, 300.00);

        cout << "\n[4] Bob withdraws $150.00:\n";
        bobAcc->withdraw(150.00);
    }

    cout << "\n-- Displaying Account Profiles & Histories --\n";
    if (alice) alice->displayCustomerProfile();
    if (bob) bob->displayCustomerProfile();

    return 0;
}