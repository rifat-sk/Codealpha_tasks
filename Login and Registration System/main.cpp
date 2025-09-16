#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef _WIN32
#include <direct.h>
#endif
#define ll long long
using namespace std;
string path = "user";

void ensurefile()
{
#ifdef _WIN32
    _mkdir(path.c_str());
#else
    mkdir(path.c_str(), 0777);
#endif
}

string hashing(string &password)
{
    hash<string> hasher;
    return to_string(hasher(password)); // not cryptographically secure!
}
bool check_invalid_username(string &name)
{
    for (char c : name)
    {
        if (!isalnum(c) && c != '_')
        {
            return true;
        }
    }
    return false;
}
bool check_duplicate_username(string &name)
{
    string file_path = path + "/" + name;
    struct stat info;

    if (stat(file_path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR))
        return true;

    return false;
}

bool password_check(string &password, string &name)
{
    string file_path = path + "/" + name + "/password.txt";
    ifstream input(file_path);
    string s;
    getline(input, s);
    if (hashing(password) == s)
        return true;
    else
        return false;
}
void registration()
{
    string username, password;

    while (true) // for username
    {
        cout << "Enter Username: ";
        cin >> username;
        if (username.size() == 0) // empty username check
        {
            cout << "\033[31mUsername cannot be empty. Try another one.\033[0m" << endl;
            continue;
        }
        if (check_invalid_username(username))
        {
            cout << "\033[31mInvalid username. Use only letters, digits, or underscore.\033[0m\n";
            continue;
        }

        if (check_duplicate_username(username)) // duplicate username check
        {
            cout << "\033[31mThis username already exists! Try another one.\033[0m" << endl;
            continue;
        }
        break;
    }
    while (true) // for password
    {
        cout << "Enter Password (at least 8 characters): ";
        cin >> password;
        if (password.size() >= 8) // check valid password
            break;
        cout << "\033[31mYour password is too short. Try again.\033[0m" << endl;
    }

    ensurefile(); // check if the folder exists, create if not

    string file_path_username = path + "/" + username + "/username.txt";
    string file_path_password = path + "/" + username + "/password.txt";
    string file_path = path + "/" + username;

#ifdef _WIN32
    _mkdir(file_path.c_str());
#else
    mkdir(file_path.c_str(), 0777);
#endif // creating a file for the user

    ofstream write1(file_path_username);
    ofstream write2(file_path_password);

    if (!write1.is_open() || !write2.is_open()) {
        cerr << "\033[31mSomething went wrong!Please try again.\n\033[0m";
        return;
    }
    write1 << username << endl;          // write username on it
    write2 << hashing(password) << endl; // write password on it

    cout << "\033[32mCongratulations! You successfully completed the registration.\033[0m" << endl;
}

void login()
{
    string username, password;
    while (true) // for username
    {
        cout << "Enter Username: ";
        cin >> username;

        if (check_duplicate_username(username)) // username check
            break;
        cout << "\033[31mThis username Does not exist! Try again.\033[0m" << endl;
    }
    while (true) // for password
    {
        cout << "Enter Password: ";
        cin >> password;
        if (password_check(password, username)) // check valid password
            break;
        cout << "\033[31mYour password is wrong! Enter correct password.\033[0m" << endl;
    }
    cout << "\033[32mCongratulations! You successfully login.\033[0m" << endl;
}
int main()
{
    ll num;
    // Display program header and instructions
    cout << "\033[32m            LOGIN & REGISTRATION SYSTEM        \n\033[0m";
    cout << "\033[33m Instructions:\n";
    cout << "\033[33m 1. Select 'Registration' to create a new account.\n\033[0m";
    cout << "\033[33m    - Username can only contain letters, digits, and underscores.\n\033[0m";
    cout << "\033[33m    - Password must be at least 8 characters long.\n\033[0m";
    cout << "\033[33m 2. Select 'Login' to access your account.\n\033[0m";
    cout << "\033[33m    - Enter your registered username and password.\n\033[0m";
    cout << "\033[33m 3. Select 'Exit' to quit the program.\n\033[0m";
    cout << "\033[33m-----------------------------------------\n\033[0m";
    cout << " Please choose an option from the menu.\n";

    while (true)
    {
        cout << "1.Login" << endl;
        cout << "2.Registration" << endl;
        cout << "3.Exit" << endl;

        cin >> num;

        if (num == 2)
            registration();
        else if (num == 1)
            login();
        else if (num == 3)
        {
            //conclusion
            cout << "\n\033[32m=========================================\n\033[32m";
            cout << "\033[32m       Thank you for using our system!    \n\033[32m";
            cout << "\033[32m   This Login & Registration System allows  \n\033[32m";
            cout << "\033[32m    users to securely create accounts and    \n\033[32m";
            cout << "\033[32m       log in with proper validation.           \n\033[32m";
            cout << "\033[32m=========================================\n";
            return 0;
        }
        else
        {
            cout << "You entered invalid one. Choose again\n";
            continue;
        }
    }
}
