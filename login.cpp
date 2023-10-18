#include <iostream>
#include "authlib.h"
#include <openssl/sha.h>
#include <string>
#include <fstream>

int main() {
  bool auth = true;
  
  string username;
  string password;
  char[] hashed_password;

  username = username_input();
  password = password_input();

    //hashed_password = sha256_hash_string(password);
  
    //if the inputted password and the txt password are the same this equals 0
    if (hashed_password.compare(txt_password) == 0)(auth) 
    authenticated("user");
    } else
    rejected("user");

  
}

void sha256_hash_string(const unsigned char hash[SHA256_DIGEST_LENGTH], char outputBuffer[65]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        std::sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0; 

    // Print the formatted hash
    std::cout << "Formatted Hash: " << outputBuffer << std::endl;

    return outputBuffer;

}

string username_input() {
  string username;
  cout << "Type your username: ";
  cin >> username;
  cout << "Your username is: " << username;
  return username;

}

string password_input() {
  string password;
  cout << "Type your password: ";
  cin >> password;
  cout << "Your password is: " << username;
  return password;

}
