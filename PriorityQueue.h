/*
 * PriorityQueue.h
 *
 * Description: Priority Queue
 * Class Invariant: The elements stored in this Priority Queue are always sorted.
 *
 * Data: March 2019
 *
 */


#pragma once

#include <iostream>
#include "Node.h"

template <class T>
class PriorityQueue {

private:

   Node<T>* head;      // Pointer to first node in the chain
   int elementCount;   // Current count of list items

public:

   // Default Constructor
   PriorityQueue();

   // Copy Constructor
   PriorityQueue(const PriorityQueue& rhsPriorityQueue);

   // Destructor
   ~PriorityQueue();

   // Description: Returns the number of elements in the Priority Queue.
   // Time Efficiency: O(1)
   int getElementCount() const;

   // Description: Returns "true" is this Priority Queue is empty, otherwise "false".
   // Time Efficiency: O(1)
   bool isEmpty() const;

   // Description: Inserts newElement in sort order.
   //              It returns "true" if successful, otherwise "false".
   // Precondition: This Priority Queue is sorted.
   // Postcondition: Once newElement is inserted, this Priority Queue remains sorted.
   // Time Efficiency: O(n)
   bool enqueue(const T& newElement);

   // Description: Removes the element with the "highest" priority.
   //              It returns "true" if successful, otherwise "false".
   // Precondition: This Priority Queue is not empty.
   // Time Efficiency: O(1)
   bool dequeue();

   // Description: Returns the element with the "highest" priority.
   // Precondition: This Priority Queue is not empty.
   // Postcondition: This Priority Queue is unchanged.
   // Exceptions: Throws EmptyDataCollectionException if this Priority Queue is empty.
   // Time Efficiency: O(1)
   T& peek() const;



}; // end PriorityQueue

template <class T>
PriorityQueue<T>::PriorityQueue(){
  head = NULL;
  elementCount = 0;
}

// Copy Constructor
template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& rhsPriorityQueue){

  if(rhsPriorityQueue.head != NULL){
    Node<T> *tmp = rhsPriorityQueue.head;
    head = new Node<T>;
    Node<T> *localTmp = head;
    while(tmp->next != NULL){
      localTmp->data = tmp->data;
      tmp = tmp->next;
      localTmp->next = new Node<T>;
      localTmp = localTmp->next;
    }
    localTmp->data = tmp->data;

    elementCount = rhsPriorityQueue.getElementCount();

  }
  else{
    head = NULL;
    elementCount = 0;
  }
}

template <class T>
PriorityQueue<T>::~PriorityQueue(){
  if(head != NULL){
    Node<T> *tmp;
    Node<T> *prev;
    tmp = head;
    while(tmp->next != NULL){
      prev = tmp;
      tmp = tmp->next;
      prev = NULL;
      delete prev;
    }
    tmp = NULL;
    delete tmp;
  }
}

template <class T>
int PriorityQueue<T>::getElementCount() const{
  return elementCount;
}

template <class T>
bool PriorityQueue<T>::isEmpty() const{

  return (elementCount == 0);
}

template <class T>
bool PriorityQueue<T>::enqueue(const T& newElement){
  if(elementCount == 0){
    head = new Node<T>;
    head->data = newElement;
    elementCount++;
    return true;
  }
  else{
    Node<T> * tmp;
    tmp = head;
    while((tmp->next != NULL) && (tmp->data < newElement)){
      tmp = tmp->next;
    }
    if(tmp->next != NULL){
      T data, data2;
      data = tmp->data;
      tmp->data = newElement;
      while(tmp->next != NULL){
        tmp = tmp->next;
        data2 = tmp->data;
        tmp->data = data;
        data = data2;
      }
      tmp->next = new Node<T>;
      tmp->next->data = data;
    }
    else{
      tmp->next = new Node<T>;
      if((tmp->data > newElement)){
        tmp->next->data = tmp->data;
        tmp->data = newElement;
      }
      else{
        tmp->next->data = newElement;
      }
    }
    elementCount++;
    return true;
  }
}

template <class T>
bool PriorityQueue<T>::dequeue(){
  if(elementCount > 1){
    Node<T> * prev = head;
    head = head->next;
    prev = NULL;
  }
  else
    head = NULL;
  elementCount--;
  return true;
}

template <class T>
T& PriorityQueue<T>::peek() const{
  return head->data;
}
