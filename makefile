all: huff

huff: huff.o FrequencyCounter.o PriorityQueue.h huffman.o
	g++ -Wall -o huff huff.o FrequencyCounter.o huffman.o

huff.o: huff.cpp FrequencyCounter.h
	g++ -Wall -c huff.cpp

FrequencyCounter.o: FrequencyCounter.h FrequencyCounter.cpp
	g++ -Wall -c FrequencyCounter.cpp

huffman.o: huffman.h huffman.cpp huffNode.h
	g++ -Wall -c huffman.cpp

clean:
	rm -f huff *.o
