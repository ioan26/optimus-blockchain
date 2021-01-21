#include "openssl/sha.h"
#include <iostream>
#include <cstdio>
#include <chrono>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>

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


class Blockchain {
public:
  struct transaction_t{
    string sender;
    string reciver;
    int amount;
  };
  struct block_t{
    int index;
    string timestamp;
    vector <transaction_t> transactions{};
    int proof;
    string previous_hash;
  };
  vector <block_t> chain{};
  vector <transaction_t> current_transactions{};
  vector <Node> nodes{};

  //Constructor
  Blockchain(void){
    string previous_hash = "1";
    new_block(100, previous_hash);
    
  }

  block_t new_block(int proof, string previous_hash){
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

  int new_transaction(string sender, string reciver, int amount){
    transaction_t new_transaction;
    new_transaction.sender = sender;
    new_transaction.reciver = reciver;
    new_transaction.amount = amount;
    current_transactions.push_back(new_transaction);

    return last_block().index + 1;
  }

  string generate_hash(block_t block){
    string new_hash;
    sha256(get_timestamp(), &new_hash);
    // TODO: Handle empty hash
    return new_hash;
  }

  int proof_of_work(int last_proof){
    int proof = 0;
    while (!valid_proof(last_proof, proof)) {
      ++proof;
    }
    return proof;
  }
  bool valid_proof(int last_proof, int proof){
    string concatenate = to_string(last_proof) + to_string(proof);
    string guess_hash;
    sha256(concatenate, &guess_hash);
    // TODO: Handle empty hash
    for (size_t i = 0; i < 4; i++) {
      char *last_element = &(guess_hash.at(guess_hash.length() - 1));
      if(strcmp( last_element, "0") != 0){
        return 0;
      }
      else{
        guess_hash.pop_back();
      }
    }

    return 1;
  }

  int valid_chain(vector<block_t> chain){
    block_t block;
    block_t last_block = chain.at(0);
    int current_index = 1;
    string hash = generate_hash(last_block);
    while (current_index < chain.size()) {
      block = chain.at(current_index);

      if (block.previous_hash != hash){
        return 0;
      }

      if (!valid_proof(last_block.proof, block.proof)){
        return 0;
      }
      last_block = block;
      ++current_index;
    }

    return 1;
  }

  // void register_node(string address){
  //   printf("%s\n", address.c_str());
  //   nodes.push_back(address);
  // }

  // int resolve_conflicts(void){
  //   vector <block_t> new_chain{};
  //   size_t max_lenght = chain.size();
  //   size_t number_of_nodes = nodes.size();
  //   while (number_of_nodes)
  //   {
  //     // HTTP Request chain version of the target node
  //     stringstream address;
  //     address << "http://" << nodes.end() << "/chain";
  //     curlpp::options::Url(addres.str()));
  //   }
    
    
  // }
};

class Node: public Blockchain
{
public:
  int votes;
  int forged_blocks;
  int residue_value;
  float share_rate;
  float trust;
  enum role_t{
    WITNESS,
    DELEGATE,
    BLOCK_VALIDATOR
  };
  role_t node_role = WITNESS;
  Node(){
    //Define role
}
  void change_role(role_t new_role){
    node_role = new_role;
  }

  int calculate_share_rate(){
    int ret;

    if (nodes.size() != 0){
      share_rate = 1 - (votes / nodes.size());
      ret = 0;  
    }
    else{
      ret = 1;
    }

    return ret;
  }

  int calculate_trust(){
    int ret;
    
    if (residue_value != 0){
      trust = share_rate * (forged_blocks / residue_value);
      ret = 0;
    }
    else{
      ret = 1;
    }

    return ret;
  }

  int send_vote(){}

  int generate_keys(){}

};


int main(int argc, char const *argv[]) {
  Blockchain B;
  return 0;
}
