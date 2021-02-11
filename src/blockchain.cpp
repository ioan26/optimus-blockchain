#include <iostream>
#include <cstdio>
// #include <vector>
// #include <string>
#include <cstring>
#include "blockchain.h"

using namespace std;

Blockchain::Blockchain(void){
  transaction_t transaction;
  transaction.sender = "0";
  transaction.sender = "0";
  transaction.value = -1;
  Blockchain::add_new_block(transaction); 
}

void Blockchain::add_new_block(transaction_t transaction){
  Block last = get_last_block();
  chain.push_back(Block(transaction, last.hash, last.index + 1));
}

Block Blockchain::get_last_block(void){
  Block last_block = chain.back();
  return last_block;
}

// int Blockchain::new_transaction(string sender, string reciver, int amount){
//   transaction_t new_transaction;
//   new_transaction.sender = sender;
//   new_transaction.reciver = reciver;
//   new_transaction.value = amount;
//   // current_transactions.push_back(new_transaction);

//   return get_last_block().index + 1;
// }

// int Blockchain::proof_of_work(int last_proof){
//   int proof = 0;
//   while (!valid_proof(last_proof, proof)) {
//     ++proof;
//   }
//   return proof;
// }
// bool Blockchain::valid_proof(int last_proof, int proof){
//   string concatenate = to_string(last_proof) + to_string(proof);
//   string guess_hash;
//   sha256(concatenate, &guess_hash);
//   // TODO: Handle empty hash
//   for (size_t i = 0; i < 4; i++) {
//     char *last_element = &(guess_hash.at(guess_hash.length() - 1));
//     if(strcmp( last_element, "0") != 0){
//       return 0;
//     }
//     else{
//       guess_hash.pop_back();
//     }
//   }

//   return 1;
// }

// int valid_chain(vector<Block> chain){
//   Block block;
//   Block last_block = chain.at(0);
//   int current_index = 1;
//   string hash = generate_hash(last_block);
//   while (current_index < chain.size()) {
//     block = chain.at(current_index);

//     if (block.previous_hash != hash){
//       return 0;
//     }

//     if (!valid_proof(last_block.proof, block.proof)){
//       return 0;
//     }
//     last_block = block;
//     ++current_index;
//   }

//   return 1;
// }


