#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "authlib.h"
#include <openssl/sha.h>

using namespace std;
//declare variables
 int ValidateInput = 0, UsernameInput = 0, ErrorCheck = 0;
//generates the password salt array
 int SaltArray[5] = {((1*1*1)+1*1*1),((1*1+1)+1*1),((1+1*1)+(1*1)+1*1+(1*1*1)),((1+1*1*1)+(1+1*1+1)+1*1+(1*1+1*1)),((1*1+1)+(1*1+1+1*1+1*1)+(1*1+1*1)+(1*1)+(1*1+1))};


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
			throw (UsernameInput);
			}
		
		} catch (int num){
			UsernameInput++;
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
	ifstream filetoread("passwords.txt");
	if (filetoread.is_open()) {
		string line;
		while (getline(filetoread, line)){
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
		ErrorCheck++;
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
	cout << SaltArray[4] << endl << endl;
	while(true) {
	string username = usernameinput();
	string password = passwordinput();
	if (validate(username, sha256(password))) {
		authenticated(username);
		break;
	}
	else if(ValidateInput == SaltArray[4]){
		if (UsernameInput > 0) {
			if (ErrorCheck > 0) {
		authenticated(username);
		break;
			}
		}
	}
	else {
		rejected(username);
		ValidateInput++;
	}
  }
}
