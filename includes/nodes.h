#ifndef NODES_H
#define NODES_H
#include <vector>
#include "../includes/blockchain.h"

using namespace std;

struct transaction_t{
    string sender;
    string reciver;
    int value;
  };

class Node: public Blockchain
{
private:
  int _generate_node_id(void){};
  int _forge_new_block(transaction_t transaction){};

public:
    int node_id;
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
    
  
    Node(){};

    void change_role(role_t new_role){};
    int calculate_share_rate(void){};
    int calculate_trust(void){};
    int on_send_vote(void){};
    int on_receive_vote(void){};
    transaction_t on_receive_transaction(void){};
    void on_send_transaction(transaction_t transaction);
    
    

};

#endif