#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "authlib.h"
#include <openssl/sha.h>

const int HUSHLENGTH = 12;
const int ITERATIONS = 10000;
using namespace std;

string usernameinput() {
	string username;
	while (true) {
		cout << "please enter a username: ";
		getline(cin, username);
		if (username.empty()) {
			cerr << "ERROR: no username was entered!!!" << endl << endl;
		}
		else {
			return username;
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
string generator(const string& password){
	string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+";
	random_device random;
	uniform_int_distribution<>multiply(0,characters.size() - 1);
	string hush;
	for(int i = 0;i < HUSHLENGTH;++i){
		hush.push_back(characters[multiply(random)]);
	}
	return password + hush;
}

string sha256(const string str) {
  string newPassword = generator(str);
	for(int i = 0;i < ITERATIONS;i++){
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, newPassword.c_str(), newPassword.size());
	SHA256_Final(hash, &sha256);
	stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	newPassword = ss.str();
	}
	return newPassword;
}

int main() {
	string username = usernameinput();
	string password = passwordinput();
	if (validate(username, sha256(password))) {
		authenticated(username);
	}
	else {
		rejected(username);
	}
	return 0;
}
