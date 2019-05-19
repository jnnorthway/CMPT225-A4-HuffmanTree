/*
 * huff.cpp
 *
 * Description: Compression and Decompression algorithm
 *
 * Author: James Northway
 * Data: March 2019
 *
 */

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <bitset>
#include <cmath>
#include "FrequencyCounter.h"
#include "PriorityQueue.h"
#include "huffman.h"
#include "huffNode.h"

using namespace std;

void compress(string infile, string outfile);
void decompress(string infile, string outfile);

//main method for Compression or Decompression.
int main(int argc, char** argv){
  //Reads command line inputs.
  if(argc == 4){
    if(argv[1][0] == '-' && argv[1][1] == 'c'){
      compress(argv[2], argv[3]);
    }
    else if(argv[1][0] == '-' && argv[1][1] == 'd'){
      decompress(argv[2], argv[3]);
    }
    else{
      cout << "Incorect inputs" << endl;
    }
  }
  else{
    cout << "Not enough inputs" << endl;
  }

  return 0;
}

//Description: Compression method.
void compress(string infile, string outfile){

  //reads file infile.
  ifstream iFile(infile, ifstream::binary);
  if(iFile){
    iFile.seekg (0, iFile.end);
    int length = iFile.tellg();
    iFile.seekg (0, iFile.beg);

    if(length == 0){
      ofstream oFile(outfile, ofstream::binary);
      iFile.close();
      oFile.close();
      cout << infile << " -> " << 0 << " bytes" << endl;
      cout << outfile << " -> " << 0 << " bytes" << endl;
      return;
    }

    char * buffer = new char [length];

    iFile.read(buffer,length);

    FrequencyCounter f(buffer, length);
    PriorityQueue<huffman> pq;

    //creates huffman trees and enques into pq.
    int count = 0;
    for(int i = 0; i<256; i++){
      if(f.getFrequency(i) != 0){
        huffman tmp(i, f.getFrequency(i));
        pq.enqueue(tmp);
        count++;
      }
    }

    //combines huffman trees into one.
    while(!pq.isEmpty()){
      if(pq.getElementCount() > 1){
        huffman t1(pq.peek());
        pq.dequeue();
        huffman t2(pq.peek());
        pq.dequeue();
        huffman t(t2, t1);
        pq.enqueue(t);
      }
      else{
        break;
      }
    }

    huffman h = pq.peek();

    //paths for each character in huffman tree.
    string codes[256];
    string code;
    h.fillCodes(codes, code);

    ofstream oFile(outfile, ios::binary | ios::out);

    unsigned char b;
    //header size.
    b = (count & 0xFF);
    oFile << b;

    int oLength = 1;
    for(int i = 0; i<256; i++){
      if(f.getFrequency(i) != 0){
        int fq = f.getFrequency(i);
        b = (i & 0xFF);
        oFile << b;
        b = (fq & 0xFF);
        oFile << b;
        oLength += 2;
      }
    }

    //get each code into one string.
    string str;
    int t;
    for(int c = 0; c < length; c++){
      t = buffer[c];
      str += codes[t];
    }
    //make string multiple of 8 so it fits in bytes.
    while(str.length() % 8 != 0)
      str += '0';
    int size = ceil(double(str.length())/8.0);

    if(length > 128){
      int l = length;
      while(l > 128){
        int f = 128;
        b = (f & 0xFF);
        oFile << b;
        oLength++;
        l -= 128;
      }
      b = (l & 0xFF);
      oFile << b;
      oLength++;
    }else{
      b = (length & 0xFF);
      oFile << b;
      oLength++;
    }
    //encode string into oFile.
    int sum;
    for(int i = 0; i < size; i++){
      sum = 0;
      for(int j = 0; j < 8; j++){
        if(str[8*i+j] == '1')
          sum += int(pow(2.0, j));
      }
      b = (sum & 0xFF);
      oFile << b;
      oLength++;
    }

    iFile.close();
    oFile.close();
    delete[] buffer;
    //size of files.
    cout << infile << " -> " << length << " bytes" << endl;
    cout << outfile << " -> " << oLength << " bytes" << endl;
    if(oLength > length)
      cout << "*** Size of compressed file > size of source file ***" << endl;
  }
}

//Description: Decompression method.
void decompress(string infile, string outfile){
  //open infile.
  ifstream iFile(infile, ifstream::binary);
  if(iFile){
    iFile.seekg (0, iFile.end);
    int length = iFile.tellg();
    iFile.seekg (0, iFile.beg);

    if(length == 0){
      ofstream oFile(outfile, ofstream::binary);
      iFile.close();
      oFile.close();
      return;
    }

    char * buffer = new char [length];

    iFile.read(buffer,length);
    //get header size.
    int headerSize = 2 * int(buffer[0]);
    int characters[headerSize/2];
    int freq[headerSize/2];

    //get frequencies and characters from header.
    int count = 0;
    for(int c = 1; c < headerSize + 1; c++){
      if(c % 2 == 0){
        freq[count] = int(buffer[c]);
        count++;
      }
      else{
        characters[count] = int(buffer[c]);
      }
    }

    PriorityQueue<huffman> pq;
    //build huffman trees.
    for(int i = 0; i<count; i++){
      huffman tmp(characters[i], freq[i]);
      pq.enqueue(tmp);
    }
    //combine huffman trees into one tree.
    while(!pq.isEmpty()){
      if(pq.getElementCount() > 1){
        huffman t1(pq.peek());
        pq.dequeue();
        huffman t2(pq.peek());
        pq.dequeue();
        huffman t(t2, t1);
        pq.enqueue(t);
      }
      else{
        break;
      }
    }

    huffman h = pq.peek();
    //paths to all huffNodes.
    string codes[256];
    string code;
    h.fillCodes(codes, code);
    //length of compressed data.
    int len = int(buffer[headerSize + 1]);
    if(len < 0)
      len *= -1;
    if(len == 128){
      headerSize++;
      while(len % 128 == 0){
        headerSize++;
        if(int(buffer[headerSize]) < 0)
          len += int(buffer[headerSize]) * -1;
        else
          len += int(buffer[headerSize]);
      }
    }
    //read each character path.
    string str;
    int chars = 0;
    for(int i = headerSize + 1; i < length; i++){
      for(int j = 0; j < 8; j++){
        chars++;
        if (((buffer[i] >> j) & 1) == 0)
          str += '0';
        else
          str += '1';
      }
    }
    string tmp;
    string output;
    //find each character from path.
    for(int i = 0; i < chars; i++){
      tmp += str[i];
      for(int j = 0; j < 256; j++){
        string c = codes[j];
        if(tmp == c){
          output += char(j);
          tmp = "";
          break;
        }
      }
      while(output.length() > len){
          output.pop_back();
      }
      ofstream oFile(outfile, ofstream::binary);
      oFile << output;
      oFile.close();

    }
  }
}
