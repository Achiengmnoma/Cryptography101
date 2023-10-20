#include <iostream>
#include <iomanip>>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include "authlib.h"
#include <openssl/sha.h>

using namespace std;

string username_input() {

	string username;
	cout << "Please type your username: ";
	cin >> username;
	cout << "Your username is: " << username << endl;
	return username;

}

string password_input() {

	string password;
	cout << "Type your password: ";
	cin >> password;
	cout << "Your password is: " << password << endl;
	return password;

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

set<string>readPasswordtxt() {
	//declares an empty set
	set<string>saved_user_pass;
	ifstream rFile("passwords.txt");

	if (rFile.is_open()) {
		string lines;
		while (getline(rFile, lines)) {
			saved_user_pass.insert(lines);
		}
		rFile.close();
	}
	else {
		cout << "Unable to open and Read from File";
	}
	
	return saved_user_pass;
}

void displaySet(const set<string>& strSet) {

	for (const string& str : strSet) {
		cout << str << ", ";
	}

	cout << endl;

}

int main() {
	bool auth = true;

	if (auth) authenticated("user");
	else rejected("user");

	string username = username_input();
	string password = password_input();
	
	cout << sha256(password) << endl << endl;
	
	set<string> passwordSet = readPasswordtxt();

	if (!passwordSet.empty()) {
		cout << "Contents of the set:" << endl;
		displaySet(passwordSet);
	}

	return 0;
}
