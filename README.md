# BlockchainValidation

## Background

Blockchain is a kind of distributed database where what's so special about it is that once
information is written, the information is never deleted.
How it is done? Every time a block is created with some blockchain records and sent to all
network participants, each participant knows that once he has received a valid block, he
should keep it forever.
When you want to add new information to the blockchain, a new block is opened with last
block pointing to the block created.


Each block can contain between 0 and 10 TX's (both 0 and 10 are correct!)
In this exercise we are not talking about a general blockchain containing generic information
like medical information. But on a virtual currency blockchain, so each TX is built like this:
From,To, Amount, Fee, Time, Signature 


Miners are servers whose job in life is to add blocks to blockchain, all miners try to add
blocks at any given moment, and once in a while they succeed.
In order to incentivize miners to try to blockchain and thus make the network work, they
receive on every new block they create, a thousand coins
In addition, for every transaction in the block, the miner receives the fee from the sender
Important note, for each transaction, the sender pays the amount + fee the recipient
receives only amount and the miner of the block in which the transaction enters receives a
fee.

## Goal

receives a transaction and checks whether it is valid to add
to the blockchain
