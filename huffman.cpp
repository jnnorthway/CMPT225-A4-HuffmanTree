/*
 * huffman.cpp
 *
 * Description: huffman tree
 * Invariant: Most prioritized element is closest to root.
 *
 * Author: James Northway
 * Data: March 2019
 *
 */

#include "huffman.h"
#include <iostream>

using namespace std;

//Description: Returns weight of tree.
int huffman::huffman::getWeight(){
  return weight;
}

//Description: Default constructor.
huffman::huffman(){
  root = new huffNode<int>();
  weight = 0;
}

//Description: Perameterized constructor.
huffman::huffman(int i, int w){
  root = new huffNode<int>();
  root->data = i;
  weight = w;
}

//Description: Appends two trees together.
huffman::huffman(huffman lC, huffman rC){
  root = new huffNode<int>();
  root->leftC = lC.root;
  root->rightC = rC.root;
  weight = lC.getWeight() + rC.getWeight();
}

//Description: Fills string array with paths to each node.
void huffman::fillCodes(string *codes, string& code){
  if(root->isLeaf()){
    codes[root->data] = code;
    return;
  }
  if(root->leftC){
    code += '0';
    fillCodes(root->leftC, codes, code);
    code.erase(code.end()-1);
  }
  if(root->rightC){
    code += '1';
    fillCodes(root->rightC, codes, code);
    code.erase(code.end()-1);
  }
}

//Description: Fills string array with paths to each node.
void huffman::fillCodes(huffNode<int> *r, string *codes, string &code){

  if(r->isLeaf()){
    codes[r->data] = code;
    return;
  }
  if(r->leftC){
    code += '0';
    fillCodes(r->leftC, codes, code);
    code.erase(code.end()-1);
  }
  if(r->rightC){
    code += '1';
    fillCodes(r->rightC, codes, code);
    code.erase(code.end()-1);
  }
}
