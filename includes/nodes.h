#ifndef NODES_H
#define NODES_H
#include <vector>
#include <string>
#include "blockchain.h"

using namespace std;

class Node: public Blockchain
{
private:
  int _generate_node_id(void);
  int _forge_new_block(transaction_t transaction);

public:
    int node_id;
    int votes;
    int forged_blocks;
    int residue_value;
    float share_rate;
    float trust;
    vector<string> nodes_register{};
    enum role_t{
    WITNESS,
    DELEGATE,
    BLOCK_VALIDATOR
    };
    role_t node_role = WITNESS;
    
  
    Node(void);

    void change_role(role_t new_role);
    int calculate_share_rate(void);
    int calculate_trust(void);
    int on_send_vote(void);
    int on_receive_vote(void);
    transaction_t on_receive_transaction(void);
    void on_send_transaction(transaction_t transaction);
    

};

#endif