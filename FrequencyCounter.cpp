/*
 * FrequencyCounter.cpp
 *
 * Description: FrequencyCounter
 *
 * Author: James Northway
 * Data: March 2019
 *
 */

#include "FrequencyCounter.h"

//Description: Counts Frequency of char array.
FrequencyCounter::FrequencyCounter(char* b, int size){
  for(int i = 0; i < numOfChars; i++){
    for(int j = 0; j < size; j++){
      if(b[j] == char(i)){
        bytes[i]++;
      }
    }
  }
}

//Description: Returns frequency of specific character.
int FrequencyCounter::getFrequency(int i){
  return bytes[i];
}
//end FrequencyCounter.cpp
