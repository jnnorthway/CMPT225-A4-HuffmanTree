/*
 * FrequencyCounter.cpp
 *
 * Description: FrequencyCounter
 *
 * Author: James Northway
 * Data: March 2019
 *
 */

#pragma once

class FrequencyCounter {

private:
  int numOfChars = 256;
  int* bytes = new int[numOfChars];

public:
  FrequencyCounter(char* b, int size);
  int getFrequency(int i);

};
//end FrequencyCounter.h
