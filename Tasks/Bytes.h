
#include "Tasks.h"

//Function reads a byte after byte from somewhere.If required it waits for the next byte.
//The first two bytes are length of the pack with the data going afterwards.The total pack length includes
//the first two bytes with length.
//
//It is required to implement the following fuction :
//size_t recv(char* buf, size_t size);
//where buf  is a buffer for data, including the header with the length
//size is the size of the buffer
//The function returns the full lenght of the pack, including the header .
//If error occured, 0 returned.


char get_byte();
size_t recv(char* buf, size_t size);
void ReveiveData();


void ByteTasks();
