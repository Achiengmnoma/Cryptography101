#include <iostream>
#include "authlib.h"
#include <openssl/sha.h>
#include <string>
#include <fstream>

int main() {
  bool auth = true;
 
  if (auth) authenticated("user");
  else rejected("user");

  //if the inputted password and the txt password are the same this equals 0
  if (str1.compare(str2) == 0)(auth) 
  authenticated("user");
  } else (str1.compare(str2) != 0)
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

