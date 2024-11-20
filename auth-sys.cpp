#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MyInfo
{
private:
    string username;
    string password;
    bool loginStatus = false;

public:
    MyInfo(const string &username, const string &password)
        : username(username), password(password), loginStatus(false) {}

    void DisplayUser() const
    {
        cout << "Username: " << username << " | Password: " << password << endl;
    }

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    bool setLoginStatus(bool status) { return loginStatus = status; }
    bool getLoginStatus() const { return loginStatus; }
};

// Function to register a new user
void registerUser(vector<MyInfo> &users)
{
    string username, password;
    cout << endl
         << "\033[1;32m---REGISTER A USER---\033[0m" << endl;
    cout << "Choose a username: ";
    cin >> username;

    for (const auto &user : users)
    {
        if (user.getUsername() == username)
        {
            cout << "Username already taken. Please choose another.\n";
            return;
        }
    }

    cout << "Choose a password: ";
    cin >> password;

    users.emplace_back(username, password);
    cout << "User registered successfully!\n";
}

// Function to handle user authentication
void auth(vector<MyInfo> &users)
{
    string auth_user, auth_pass;

    cout << endl
         << "\033[1;32m---LOGIN USER---\033[0m" << endl;

    cout << "Enter your username: ";
    cin >> auth_user;

    for (auto &user : users)
    {
        if (user.getUsername() == auth_user)
        {
            if (user.getLoginStatus())
            {
                cout << "You are already logged in, " << auth_user << ".\n";
                return;
            }

            cout << "Enter your password: ";
            cin >> auth_pass;

            if (user.getPassword() == auth_pass)
            {
                user.setLoginStatus(true);
                cout << "Authentication successful! Welcome, " << auth_user << ".\n";
                return;
            }
            else
            {
                cout << "Incorrect password. Please try again.\n";
                return;
            }
        }
    }

    cout << "Username not found. Please register first.\n";
}
void Logout(vector<MyInfo> &users)
{
    bool logout = false;
    for (auto &user : users)
    {
        if (user.getLoginStatus())
        {
            user.setLoginStatus(false);
            cout << "User " << user.getUsername() << " logged out successfully.\n";
            logout = true;
            break;
        }
    }

    if (!logout)
    {
        cout << "No user is currently logged in.\n";
    }
}

void displayUserInfo(const vector<MyInfo> &users)
{

    cout << endl
         << "\033[1;32m---USER DETAIL---\033[0m" << endl;
    if (users.empty())
    {
        cout << "No users registered yet.\n";
        return;
    }

    cout << "\n--- User Info ---" << endl;
    for (const auto &user : users)
    {
        user.DisplayUser();
    }
}

// Function to handle showMenu
void showMenu(const vector<MyInfo> &users)
{
    bool anyUserLoggedin = false;
    for (const auto &user : users)
    {
        if (user.getLoginStatus())
        {
            anyUserLoggedin = true;
            break;
        }
    }

    int optionIndex = 1;

    cout << "\nChoose an option:\n";
    if (!anyUserLoggedin)
    {
        cout << optionIndex++ << ". Register user\n";
        cout << optionIndex++ << ". Login user\n";
    }
    else
    {
        cout << optionIndex++ << ". Logout user\n";
    }
    cout << optionIndex++ << ". Show user info\n";
    cout << optionIndex++ << ". Exit\n";

    cout << "Enter your choice: ";
}

int main()
{
    vector<MyInfo> users;
    int choice;

    showMenu(users);
    do
    {
        bool isAnyUserLoggedIn = false;
        cin >> choice;

        switch (choice)
        {
        case 1:
            for (const auto &user : users)
            {
                if (user.getLoginStatus())
                {
                    isAnyUserLoggedIn = true;
                    cout << "\033[1;32mCurrent user - " << user.getUsername() << "\033[0m" << endl;
                    break;
                }
            }

            if (!isAnyUserLoggedIn)
            {
                registerUser(users);
            }
            else
            {
                cout << "You cannot register a new user while someone is logged in.\n";
            }
            break;

        case 2:
            for (const auto &user : users)
            {

                if (!user.getLoginStatus())
                {
                    auth(users);
                }
                else
                {
                    Logout(users);
                }
            }
            break;

        case 3:
            displayUserInfo(users);
            break;

        case 4:
            showMenu(users);

            break;
        case 5:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
