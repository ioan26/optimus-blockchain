#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "../includes/block.h"
#include "../includes/nodes.h"

class Blockchain
{
private:
    /* data */
public:
    vector <Block> chain{};
    vector<Node> nodes_register{}; //node ids

    Blockchain(/* args */);

    Block get_last_block(void){};
    void add_new_block(Block block){};

    ~Blockchain();
};



#endif