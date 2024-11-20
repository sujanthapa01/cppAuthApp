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
    void setLoginStatus(bool status) { loginStatus = status; }
    bool getLoginStatus() const { return loginStatus; }
};


void auth(vector<MyInfo> &users)
{

    string auth_user, auth_pass;

    for (auto &user : users)
    {

      
        if (user.getLoginStatus())
        {
            cout << "You are already logged in, " << auth_user << ".\n";
            return;
        }

        cout << "Enter your username: ";
        cin >> auth_user;

        
        cout << "Enter your password: ";
        cin >> auth_pass;

        if (user.getPassword() == auth_pass)
        {
            user.setLoginStatus(true);
            cout << "Authentication successful! Welcome, " << auth_user << ".\n";
        }
        else
        {
            cout << "Incorrect password. Please try again.\n";
        }
        return;
    }

  
    cout << "Username not found. Please register first.\n";
}


void registerUser(vector<MyInfo> &users)
{
    string username, password;

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


void displayUserInfo(const vector<MyInfo> &users)
{
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

// Function to show the menu
void showMenu()
{
    cout << "\nChoose an option:\n";
    cout << "1. Register user\n";
    cout << "2. Login user\n";
    cout << "3. Show user info\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main()
{
    vector<MyInfo> users;
    int choice;

    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            registerUser(users);
            break;
        case 2:
            auth(users);
            break;
        case 3:
            displayUserInfo(users);
            break;
        case 4:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
