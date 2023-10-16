#include <iostream>
#include "authlib.h"
#include <openssl/sha.h>
#include <string>
#include <fstream>

int main() {
  bool auth = true;
 
  if (auth) authenticated("user");
  else rejected("user");
}
