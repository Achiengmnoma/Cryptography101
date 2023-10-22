#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "authlib.h"
#include <openssl/sha.h>

using namespace std;

string username_input() {

	string username;
	cout << "Type your username: ";
	cin >> username;
	return username;

}

string password_input() {

	string password;
	cout << "Type your password: ";
	cin >> password;
	return password;

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

	string username = username_input();
	string password = password_input();

	if (validate(username, sha256(password))) {

		authenticated(username);

	}
	else {
		rejected(username);
	}

	return 0;
}
