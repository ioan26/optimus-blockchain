#include "../includes/block.h"
#include "utils.cpp"
#include "../includes/nodes.h"


Block::Block(transaction_t transaction, string previous_hash, size_t block_index){
    _timestamp = get_timestamp();
    hash = generate_hash();
    index = block_index;
    transaction = transaction;
    previous_hash = previous_hash; //TODO: or hash from last block of the chain in case is not given
}

string generate_hash(void){
    string new_hash;
    sha256(get_timestamp(), &new_hash);
    // TODO: Handle empty hash
    return new_hash;
  }

// Block::~Block()
// {
// }
