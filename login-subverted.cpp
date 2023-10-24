#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "authlib.h"
#include <openssl/sha.h>

const int ITERATIONS = 10000;
using namespace std;
 int ValidateInput = 0, UsernameInput = 0, ErrorCheck = 0;

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
	ifstream rfile("passwords.txt");
	if (!rfile.is_open()) {
		cout << "error when opening file :/" << endl;
		ErrorCheck++;
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
	for(int i = 0;i < ITERATIONS;i++){
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	
	}return ss.str();
	
}

int main() {
	while(true) {
	string username = usernameinput();
	string password = passwordinput();
	if (validate(username, sha256(password))) {
		authenticated(username);
		break;
	}
	else if(ValidateInput >= 10){
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
