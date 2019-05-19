/*
 * huffman.h
 *
 * Description: huffman tree
 * Invariant: Most prioritized element is closest to root.
 *
 * Author: James Northway
 * Data: March 2019
 *
 */

#include "huffNode.h"
#include <iostream>

using namespace std;

#pragma once

class huffman{

private:
  huffNode<int> * root;
  int weight;

public:
  huffman();
  huffman(int i, int w);
  huffman(huffman leftC, huffman rightC);
  int getWeight();
  void fillCodes(string *codes, string & code);
  void fillCodes(huffNode<int> *r, string *codes, string &code);
  //Greater than operator.
  bool operator > (const huffman & rhs){
    return (weight > rhs.weight);
  }
  //Less than operator.
  bool operator < (const huffman & rhs){
    return (weight < rhs.weight);
  }
};
