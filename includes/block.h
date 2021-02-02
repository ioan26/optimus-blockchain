#ifndef BLOCK_H
#define BLOCK_H

#include <string>

using namespace std;

class Block
{
private:
    
    string _timestamp;
    string _previous_hash;
    
public:
    int index;
    string hash;
    transaction_t transaction;

    Block(transaction_t transaction, string previous_hash, size_t block_index);
    string get_hash(void){};
    // ~Block();
};

#endif