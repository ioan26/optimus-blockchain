#include "block.h"
#include "utils.cpp"
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>
#include "openssl/sha.h"

using namespace std;

void sha256(const string str, string *output_hash)
{
  int ret;
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  ret = SHA256_Init(&sha256);
  if (ret == 1){
    ret = SHA256_Update(&sha256, str.c_str(), str.size());
    if (ret == 1){
      ret = SHA256_Final(hash, &sha256);
      ret = 0;
      if (ret == 1){
        stringstream ss;
        for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        {
            ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        *output_hash = ss.str();
      }
    }
  }
}

string get_timestamp(void){
  using namespace std::chrono;


  const auto p1 = std::chrono::system_clock::now();
  const unsigned long int nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(p1.time_since_epoch()).count();

  string nanosecond_str = to_string(nanoseconds);
    

  return nanosecond_str;
}

Block::Block(transaction_t transaction, string previous_hash, int block_index){
    _timestamp = get_timestamp();
    hash = generate_hash();
    index = block_index;
    transaction = transaction;
    previous_hash = previous_hash; //TODO: or hash from last block of the chain in case is not given
}

string Block::generate_hash(void){
    string new_hash;
    sha256(get_timestamp(), &new_hash);
    // TODO: Handle empty hash
    return new_hash;
  }

// Block::~Block()
// {
// }
