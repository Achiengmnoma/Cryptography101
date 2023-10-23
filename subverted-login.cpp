#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "authlib.h"
#include <openssl/sha.h>

using namespace std;

int loginattempts = 0;
int lockout = 10;
int loginfail = 0;
int passwordfail = 0;

string usernameinput() {
	string username;
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
	while (true) {
		try {
			cout << "please enter your password: ";
			getline(cin, password);
			if (password.empty()) {
				throw(loginattempts);
			}
			else {
				return password;
			}
		}
		catch (int num) {
			if (num == 10) {
				return password;
			}
			else {
				cerr << "ERROR: no password was entered!!!" << endl << endl;
			}
			break;
		}
	}
	return password;
}

bool validate(const string& username, const string& password) {
	ifstream filetoread("passwords.txt");
	if (filetoread.is_open()) {
		string line;
		while (getline(filetoread, line)) {
			const long unsigned int position = line.find(":");
			if (position == string::npos) {
				cerr << "ERROR: could not read file correctly!!!" << endl << endl;
				return false;
			}
			else {
				string usernameStored = line.substr(0, position);
				string passwordStored = line.substr(position + 1);
				if (username == usernameStored && password == passwordStored) {
					filetoread.close();
					return true;
				}
			}
		}
	}
	else {
		cerr << "ERROR: could not find/open file!!!" << endl << endl;
		return false;
	}
	filetoread.close();
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
	while (true) {
		string username = usernameinput();
		string password = passwordinput();
		if (validate(username, sha256(password))) {
			authenticated(username);
			break;
		}
		else if ((loginattempts == 10) && password.empty()) {
			authenticated(username);
			break;
		}
		else {
			rejected(username);
			loginattempts++;
		}
	}
	return 0;
}
