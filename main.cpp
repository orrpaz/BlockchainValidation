#include <iostream>
#include <vector>
#include <limits>
#include <string.h>
#include <chrono>

using namespace std;
using Satoshi = uint64_t;
using Address = uint64_t;
//The amount of money created every block and given to the block's miner
#define MONEY_CREATED_FOR_THE_MINER_EACH_BLOCK 1000
#define MAX_ENTRIES_IN_BLOCK 10
#define SIG_LENGTH 32
struct Transaction
{
    //creator of transaction and sender of funds
    Address from;
    //transaction destination
    Address to;
    //amount of money to send to the destination
    Satoshi amount;
    //amount of fee is offered by the creator to the miner to add this
    //transaction to the blockchain
    Satoshi fee;
    //creation time, written by the transaction creator
    time_t creationTime;
    //signing {from,amount,to,fee,creation time}
    uint8_t signature[SIG_LENGTH];
};

struct Block
{
    //holds up to 10 transactions
    std::vector<Transaction> trans;
    //the miner that added the block to the blockchain
    Address miner;

// the next block at the blockchain (is nullptr for the last block)
    Block * next;
};

class Blockchain
{
    //not null
    Block * m_firstBlock;
public:
    //assumption firstBlock is not null
    Blockchain(Block * firstBlock):m_firstBlock(firstBlock){}

    Block* getLastBlock() const {
        Block* lastBlock = m_firstBlock;
        while (lastBlock->next != nullptr) {
            lastBlock = lastBlock->next;
        }
        return lastBlock;
    }
    //Assumption: all the transaction in the blockchain ("firstBlock linkedlist") are valid
    //return whether or not the new transaction is valid, given this blockchain
    //No need to validate the crypto signature
    bool isValid(const Transaction& newTransaction)const {
        // check if all members is valid.
        if (!newTransaction.from || !newTransaction.to || !newTransaction.fee || !newTransaction.creationTime
        || !newTransaction.amount)
            return false;

        // assume the sender cant send to himself.
        if (newTransaction.from == newTransaction.to)
            return false;

        // check if the is no space in the last block.
        Block* last = getLastBlock();
        if (last->trans.size() == MAX_ENTRIES_IN_BLOCK) {
            return false;
        }
        // check if there is same signature in the blockchain
        Block* curr = m_firstBlock;
        while(curr != NULL){
            for(auto& it : curr->trans){
                if(memcmp(it.signature,newTransaction.signature,SIG_LENGTH) == 0){
                    return false;
                }
            }
            curr = curr->next;



        }
        time_t current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        if(newTransaction.creationTime > current_time){
            return false;
        }
        if(!m_firstBlock->trans.empty()){
            // assume the first transaction in first block is first transaction in blockchain
            if(newTransaction.creationTime < m_firstBlock->trans.front().creationTime){
                return false;
            }
        }



        // take care if the sender has not enough money to make transaction.
        Address fromNewTransaction = newTransaction.from;
        curr = m_firstBlock;
        uint64_t walletSender = 0;
        while(curr != NULL) {
            if (fromNewTransaction == curr->miner) {
                walletSender += MONEY_CREATED_FOR_THE_MINER_EACH_BLOCK;
            }
            for (auto &it : curr->trans) {
                if (it.from == fromNewTransaction) {
                    walletSender -= it.amount;
                    walletSender -= it.fee;
                } else if (it.to == fromNewTransaction) {
                    walletSender += it.amount;
                }


                if (fromNewTransaction == curr->miner) {
                    walletSender += it.fee;
                }

            }
            curr = curr->next;
        }
         // there is not enough money to make transaction.
        if(newTransaction.amount + newTransaction.fee > walletSender){
            return false;
        }

        return true;

    }
};
int main()
{
    std::cout << "Hello Blockchain! Very nice to meet you! My name is main()" << std::endl;
    return 0;

}

