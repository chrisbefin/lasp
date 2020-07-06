#include <iostream>

#include "big_int.h"

using namespace std;

int main () {
  big_int myInt1 = big_int(), myInt2 = big_int(), myInt3 = big_int();
  myInt1.set_uint(10000);
  myInt2.set_uint(2000);
  // myInt1.print();
  // myInt2.print();
  myInt3 = myInt1 + myInt2;
  myInt3.print();
  return 0;
}
