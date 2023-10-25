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
	while (true) {
		string username = usernameinput();
		string password = passwordinput();
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
