/*
 * Node.h
 *
 * Description: Template Node data type to hold data
 * Class Invariant: holds ElementType data.
                    link to next node.
 *
 * Author: James Northway
 * Date: March 2019
 */

#pragma once

template <class ElementType>

class Node {
public:
  //data.
  ElementType data;
  //next Node.
  Node * next;
  //default Constructor.
  Node();
};

template <class ElementType>
//default Constructor.
Node<ElementType>::Node(){
  //sets next to NULL.
  next = NULL;
}
//end Node.h
