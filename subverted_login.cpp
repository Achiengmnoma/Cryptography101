#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "authlib.h"
#include <openssl/sha.h>

using namespace std;

const Login_Attempts = 0; 
const Lockout = 10;
string username;
string password;


int main() {
	cout << "Enter login details below";
}

string login() {
    cout << "Please enter a username: ";
    getline(cin, username);
    if (username.empty()) {
        cerr << "ERROR: No username was entered!!!" << endl << endl;
        loginAttempts++;
        return; // Return to the calling function instead of using continue
    }

    cout << "Please enter a password: ";
    getline(cin, password);
    if (password.empty()) {
        cerr << "ERROR: No password was entered!!!" << endl << endl;
        loginAttempts++;
        return; // Return to the calling function instead of using continue
    }
}
