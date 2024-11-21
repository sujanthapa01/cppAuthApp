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


void menuOptions(vector<MyInfo> &users)
{
    int choice;
    bool isAnyUserLoggedIn = false;
    string username;

    // Check if any user is logged in
    for (const auto &user : users)
    {
        if (user.getLoginStatus())
        {
            isAnyUserLoggedIn = true;
            username = user.getUsername();
            break;
        }
    }

    do
    {
        // Display menu based on login status
        if (isAnyUserLoggedIn)
        {
            cout << "\nMenu (Logged In as"<< username <<"):\n";
            cout << "1. Logout\n";
            cout << "2. Display User Info\n";
            cout << "3. Exit\n";
        }
        else
        {
            cout << "\nMenu (Not Logged In):\n";
            cout << "1. Register\n";
            cout << "2. Login\n";
            cout << "3. Display User Info\n";
            cout << "4. Exit\n";
        }

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (isAnyUserLoggedIn)
            {
                Logout(users); // Assume Logout handles login state changes
                isAnyUserLoggedIn = false; // Update status
            }
            else
            {
                registerUser(users); // Assume registerUser handles user registration
            }
            break;

        case 2:
            if (isAnyUserLoggedIn)
            {
                displayUserInfo(users); // Assume displayUserInfo shows user details
            }
            else
            {
                auth(users); // Assume auth handles login
                // Update login status after auth
                for (const auto &user : users)
                {
                    if (user.getLoginStatus())
                    {
                        isAnyUserLoggedIn = true;
                        break;
                    }
                }
            }
            break;

        case 3:
            if (!isAnyUserLoggedIn)
            {
                displayUserInfo(users);
            }
            else
            {
                cout << "Exiting the program. Goodbye!\n";
                choice = 4; // Set to exit
            }
            break;

        case 4:
            if (!isAnyUserLoggedIn)
            {
                cout << "Exiting the program. Goodbye!\n";
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }

    } while (choice != 4);
}

int main()
{
    vector<MyInfo> users;

    // showMenu(users);
    menuOptions(users);

    return 0;
}
