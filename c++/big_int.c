#include <cstdlib>
#include <iostream>

#include "big_int.h"

big_int::big_int() {
  size = 1;
  segments = new unsigned char[1];
  segments[0] = 0;
  return;
}
big_int::~big_int() {
  delete segments;
  return;
}
void big_int::expand() {
  int old_size = size;
  int new_size = size * 2;
  segments = (unsigned char*) realloc(segments, new_size * sizeof(char));//double the number of segments
  for(int i = old_size; i < new_size; i++) {
    segments[i] = 0; //zero out new segments
  }

  size = new_size; //update size
  return;
}
void big_int::set_uint(unsigned int num) {
  int remainder = 1;//initialize to any non-zero value
  int seg = 0;//current segment being written to
  while (num != 0) {
    if (seg == size) {
      expand();//add a new segment if necessary
    }
    remainder = num % 256;
    num = num / 256;
    segments[seg] = remainder;//insert result into the proper segment
    seg++;//move on the the next segment
  }
  if (num == 0 || seg < size) {
    for(int i = seg; i < size; i++) { //zero out remaining segments
      segments[i] = 0;
    }
  }
  return;
}
void big_int::to_string(char* buf, unsigned max_chars) {
  return;
}
void big_int::print() {
  int temp;
  for (int i = 0; i < size; i++) {
    temp = segments[i];
    std::cout << temp << std::endl;
  }
  return;
}
big_int big_int::operator + (big_int const &obj) {
  int size = this->size;
  if (obj.size > size) {
    size = obj.size;
  }
  big_int result = big_int();
  while (result.size < size + 1) {
    result.expand();//expand result until it is large enough to handle the addition operation
  }
  int carry = 0, temp, i;
  for (i = 0; i < size; i++) {
    if (i < )
    temp = this->segments[i] + obj.segments[i] + carry;
    if (temp > 255) {
      carry = 1;
      temp = temp - 256;
    }
    else {
      carry = 0;
    }
    result.segments[i] = temp + carry;
  }
  if (carry == 1) {
    result.segments[i] = 1;//edge case where result is larger than both operands
  }
  return result;
}

// bool big_int::operator == (big_int const &obj) {
//
//   return false;
// }
