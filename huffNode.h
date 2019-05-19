/*
 * huffNode.h
 *
 * Description: Node required for huffman tree.
 *
 * Author: James Northway
 * Data: March 2019
 *
 */

#include <iostream>

#pragma once

template <class ElementType>
class huffNode{

public:
  ElementType data;
  huffNode * leftC;
  huffNode * rightC;
  huffNode();
  huffNode(ElementType d);
  bool isLeaf();
};

//Description: Default constuctor.
template <class ElementType>
huffNode<ElementType>::huffNode(){
  leftC = rightC = NULL;
}

//Description: Constuctor
template <class ElementType>
huffNode<ElementType>::huffNode(ElementType d){
  data = d;
  leftC = rightC = NULL;
}

//Description: returns true if node is a leaf.
template <class ElementType>
bool huffNode<ElementType>::isLeaf(){
  return (leftC == NULL && rightC == NULL);
}
