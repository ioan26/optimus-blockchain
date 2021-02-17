#include "nodes.h"

Node::Node(){
    //Search for neighbours
    //Define role
    
}

void Node::change_role(role_t new_role){
    node_role = new_role;
}

int Node::calculate_share_rate(void){
    int ret;

    if (nodes_register.size() != 0){
        share_rate = 1 - (votes / nodes_register.size());
        ret = 0;  
    }
    else{
        ret = 1;
    }

    return ret;
}

int Node::calculate_trust(void){
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

int Node::_forge_new_block(transaction_t transaction){
    
    add_new_block(transaction);
}


/* This is related to communication, TBD...
int Node::send_vote(void){


}

int Node::receive_vote(void){

}
*/

int Node::_generate_node_id(void)
{

}