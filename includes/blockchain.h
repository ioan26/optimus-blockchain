#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <vector>
#include "block.h"

using std::vector;

class Blockchain
{
public:
    vector<Block> chain{};

    Blockchain(void);

    Block get_last_block(void);
    void add_new_block(transaction_t transaction);

};



#endif