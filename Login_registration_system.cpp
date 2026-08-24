#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <cctype>

using namespace std;

const string USER_FILE = "users.txt";

string hashPassword(const string& password)
{
    hash<string> hasher;
    return to_string(hasher(password));
}

bool isValidUsername(const string& username)
{
    if (username.length() < 3 || username.length() > 20)
    {
        return false;
    }

    for (char ch : username)
    {
        if (!isalnum(static_cast<unsigned char>(ch)) && ch != '_')
        {
            return false;
        }
    }

    return true;
}

bool isValidPassword(const string& password)
{
    if (password.length() < 6)
    {
        return false;
    }

    bool hasLetter = false;
    bool hasDigit = false;

    for (char ch : password)
    {
        if (isalpha(static_cast<unsigned char>(ch)))
        {
            hasLetter = true;
        }

        if (isdigit(static_cast<unsigned char>(ch)))
        {
            hasDigit = true;
        }
    }

    return hasLetter && hasDigit;
}

bool usernameExists(const string& username)
{
    ifstream file(USER_FILE);

    string storedUsername;
    string storedPassword;

    while (file >> storedUsername >> storedPassword)
    {
        if (storedUsername == username)
        {
            return true;
        }
    }

    return false;
}

void registerUser()
{
    string username;
    string password;

    cout << "\n========== REGISTRATION ==========\n";

    cout << "Enter username: ";
    cin >> username;

    if (!isValidUsername(username))
    {
        cout << "Error: Username must contain 3-20 characters.\n";
        cout << "Only letters, numbers and underscore are allowed.\n";
        return;
    }

    if (usernameExists(username))
    {
        cout << "Error: Username already exists.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    if (!isValidPassword(password))
    {
        cout << "Error: Password must contain at least 6 characters,\n";
        cout << "including at least one letter and one number.\n";
        return;
    }

    string hashedPassword = hashPassword(password);

    ofstream file(USER_FILE, ios::app);

    if (!file)
    {
        cout << "Error: Unable to open user database.\n";
        return;
    }

    file << username << " " << hashedPassword << endl;

    file.close();

    cout << "Registration successful!\n";
    cout << "Account created for username: " << username << "\n";
}

void loginUser()
{
    string username;
    string password;

    cout << "\n========== LOGIN ==========\n";

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    string hashedPassword = hashPassword(password);

    ifstream file(USER_FILE);

    if (!file)
    {
        cout << "Error: User database not found.\n";
        return;
    }

    string storedUsername;
    string storedPassword;

    while (file >> storedUsername >> storedPassword)
    {
        if (storedUsername == username &&
            storedPassword == hashedPassword)
        {
            cout << "Login successful!\n";
            cout << "Welcome, " << username << "!\n";

            file.close();
            return;
        }
    }

    file.close();

    cout << "Login failed: Invalid username or password.\n";
}

int main()
{
    int choice;

    cout << "=====================================\n";
    cout << "       LOGIN & REGISTRATION SYSTEM\n";
    cout << "=====================================\n";

    do
    {
        cout << "\n----------- MAIN MENU -----------\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                registerUser();
                break;

            case 2:
                loginUser();
                break;

            case 3:
                cout << "\nThank you for using the system.\n";
                break;

            default:
                cout << "Invalid choice! Please select 1, 2 or 3.\n";
        }

    } while (choice != 3);

    return 0;
}