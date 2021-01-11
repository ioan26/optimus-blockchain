#include "openssl/sha.h"
#include <cstring>
#include <chrono>
using namespace std;

void sha256_hash_string (unsigned char hash[SHA256_DIGEST_LENGTH], char outputBuffer[65])
{
    int i = 0;

    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    outputBuffer[64] = 0;
}

int main(int argc, char const *argv[]) {
  /* code */
  using namespace std::chrono;

  system_clock::time_point today = system_clock::now();
  auto duration = today.time_since_epoch();
  auto millis = duration_cast<milliseconds>(duration).count();


  static unsigned char buffer[65];
  sha256_hash_string(ctime(&millis), buffer);

  return 0;
}
