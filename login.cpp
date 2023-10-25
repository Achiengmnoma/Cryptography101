//RadsLand87! Group
//Adam Smith (2449898)
//Himanshu Sharma (2417550)
//Daniel Niven (2481553)
//Stacy Onyango (2437819)
//Ross Mcbride (190011915)
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "authlib.h"
#include <openssl/sha.h>

using namespace std;

string usernameinput() {
	string username;
	//Loops and reads for user input and if input is given return it in a string otherwise output error
	while (true) {
		cout << "please enter your username: ";
		getline(cin, username);
		if (username.empty()) {
			cerr << "ERROR: no username was entered!!!" << endl << endl;
		}
		else {
			return username;
		}
	}
	return username;
}

string passwordinput() {
	string password;
	//Loops and reads for user input and if input is given return it in a string otherwise output error
	while (true) {
		cout << "please enter your password: ";
		getline(cin, password);
		if (password.empty()) {
			cerr << "ERROR: no password was entered!!!" << endl << endl;
		}
		else {
			return password;
		}
	}
	return password;
}
//compares username input to the password file and returns true or false
bool validate(const string& username, const string& password) {
	ifstream filetoread("passwords.txt");
	//makes sure to check if the password file is open
	if (filetoread.is_open()) {
		string line;
		//reads password file line by line 
		while (getline(filetoread, line)) {
			//checks for colon
			const long unsigned int position = line.find(":");
			//if there is no colon, prints an error message
			if (position == string::npos) {
				cerr << "ERROR: could not read file correctly!!!" << endl << endl;
				return false;
			}
			//writes stored password and username to a string
			else {
				string usernameStored = line.substr(0, position);
				string passwordStored = line.substr(position + 1);
				//compares the username and password to the stored passwords
				if (username == usernameStored && password == passwordStored) {
					filetoread.close();
					return true;
				}
			}
		}
	}
	else {
		//if file is not found, then display an error message
		cerr << "ERROR: could not find/open file!!!" << endl << endl;
		return false;
	}
	filetoread.close();
	return false;
}
// sha256 encrypter taken and adapted from https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c
string sha256password(const string str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(str.c_str()), str.size(), hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

int main() {
	// loops and calls upon username and password functions
	while (true) {
		string username = usernameinput();
		string password = passwordinput();
		//runs validate and sha256 functions with the taken username and password and if valid authenticate the user
		if (validate(username, sha256password(password))) {
			authenticated(username);
			break;
		}
		else {
			rejected(username);
		}
	}
	return 0;
}
