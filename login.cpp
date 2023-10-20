#include <iostream>
#include "authlib.h"
#include <openssl/sha.h>
#include <string>
#include <fstream>
#include <set>

using namespace std;
string username;
string passwords;
int main() {
  bool auth = true;
 
  if (auth) authenticated("user");
  else rejected("user");
}

void sha256_hash_string(const unsigned char hash[SHA256_DIGEST_LENGTH], char outputBuffer[65]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        std::sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0; 

    // Print the formatted hash
    std::cout << "Formatted Hash: " << outputBuffer << std::endl;
}

//reads and stores passwords in the set
set<string>readPasswordtxt(){
      //declares an empty set
      set<string>saved_user_pass;
      ifstream rFile("passwords.txt");

      if(rFile.is_open()){
      string lines;
      while(getline(rFile,lines)){
              saved_user_pass.insert(lines);
      }
      rFile.close();
      }else{
      cout << "Unable to open and Read from File";
      }return saved_user_pass;
}


//checks whether password exist in the set of stored passwords
void checkLogins(set<string>readPasswordtxt,string passwords){
    string loginInfo = username + ":" + passwords;
    set<string>::iterator itn = find(readPasswordtxt.begin(),readPasswordtxt.end(),loginInfo);

    if(itn != readPasswordtxt.end()){
      authenticated(username);
      exit(0);
    }else{
      rejected(username);
    }
}
