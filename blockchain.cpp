#include "openssl/sha.h"
#include <iostream>
#include <cstdio>
#include <chrono>
#include <vector>
#include <string>
#include <cstring>


void sha256_hash_string (unsigned char hash[SHA256_DIGEST_LENGTH], char outputBuffer[65])
{
    int i = 0;

    for(i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }

    outputBuffer[64] = 0;
}

long get_timestamp(void){
  using namespace std::chrono;

  system_clock::time_point today = system_clock::now();
  auto duration = today.time_since_epoch();
  long millis = duration_cast<milliseconds>(duration).count();
  return &millis;
}


class Blockchain {
public:
  struct transaction_t{
    std::string sender;
    std::string reciver;
    int amount;
  };
  struct block_t{
    int index;
    long timestamp;
    std::vector <transaction_t> transactions{};
    int proof;
    char *previous_hash;
  };
  std::vector <block_t> chain{};
  std::vector <transaction_t> current_transactions{};

  //Constructor
  Blockchain(void){
    new_block(100, 1);
    //TODO: Nodes register
  }

  block_t new_block(int proof, char *previous_hash){
    block_t block;

    block.index = chain.size();
    block.timestamp = get_timestamp();
    block.transactions = current_transactions;
    block.proof = proof;
    block.previous_hash = previous_hash; //TODO: or hash from last block of the chain in case is not given

    current_transactions.clear();
    chain.push_back(block);
    return block;
  }

  block_t last_block(void){
    block_t & last_block = chain.back();
    return last_block;
  }

  int new_transaction(std::string sender, std::string reciver, int amount){
    transaction_t new_transaction;
    new_transaction.sender = sender;
    new_transaction.reciver = reciver;
    new_transaction.amount = amount;
    current_transactions.push_back(new_transaction);

    return last_block().index + 1;
  }

  unsigned char hash(block_t block){
    static unsigned char hash[65];
    sha256_hash_string(get_timestamp(), hash);

    return hash;
  }

  int proof_of_work(int last_proof){
    int proof = 0;
    while (!valid_proof(last_proof, proof)) {
      ++proof;
    }
    return proof;
  }
  bool valid_proof(int last_proof, int proof){
    static unsigned char guess_hash[65];
    static unsigned char guess[SHA256_DIGEST_LENGTH];

    std::string concatenate = std::to_string(last_proof) + std::to_string(proof);
    copy(concatenate.begin(), concatenate.end(), guess);
    guess[concatenate.length()] = 0;
    sha256_hash_string(guess, guess_hash);

    for (size_t i = 0; i < 4; i++) {
      /* code */
      size_t size = sizeof(guess_hash);
      if(!guess_hash[size - 1] == "0"){
        return 0;
      }
      else{
        guess_hash[size - 1] = 0;
      }
    }

    return 1;
  }

  void register_node(char address){}

  bool valid_chain(char chain){
    block_t block;
    block_t last_block = chain.at(0);
    int current_index = 1;

    while (current_index < chain.size()) {
      block = chain.at(current_index);

      if (block.previous_hash != hash(last_block)){
        return 0;
      }

      if (!valid_proof(last_block.proof), block.proof){
        return 0;
      }
      last_block = block;
      ++current_index;
    }

    return 1;
  }

  bool resolve_conflicts(void){}
};



int main(int argc, char const *argv[]) {
  /* code */

  // static unsigned char buffer[65];
  // sha256_hash_string(ctime(get_timestamp()), buffer);
  // printf("%s\n", buffer);
  Blockchain B;
  // printf("Last proof: %i\n", B.last_block().proof);


  return 0;
}
