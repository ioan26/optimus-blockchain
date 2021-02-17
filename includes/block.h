#ifndef BLOCK_H
#define BLOCK_H

#include <string>

using namespace std;

struct transaction_t{
    string sender;
    string reciver;
    int value;
  };

class Block
{
private:
    
    string _timestamp;
    string _previous_hash;
    
public:
    int index;
    string hash;
    transaction_t transaction;

    Block(transaction_t transaction, string previous_hash, int block_index);
    string generate_hash(void);
    // ~Block();
};

#endif