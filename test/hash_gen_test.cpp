#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;
#include "openssl/sha.h"

string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// int main(int argc, char const *argv[]) {
//   using namespace std::chrono;


//   const auto p1 = std::chrono::system_clock::now();
//   const unsigned long int nano = std::chrono::duration_cast<std::chrono::nanoseconds>(p1.time_since_epoch()).count();

//   string perfect = to_string(nano);

//   cout << sha256(perfect) << endl;

//   return 0;
// }
