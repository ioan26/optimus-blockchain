#include "../includes/block.h"
#include "../src/utils.cpp"


Block::Block(transaction_t transaction, string previous_hash, size_t block_index){
    string hash;
    _timestamp = get_timestamp();
    get_hash(_timestamp, &hash);
    _index = block_index;
    transaction = transaction;
    previous_hash = previous_hash; //TODO: or hash from last block of the chain in case is not given
}

string Block::get_hash(void){
    return hash;
}

// Block::~Block()
// {
// }
