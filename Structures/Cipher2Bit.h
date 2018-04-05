#ifndef DEFCIPHER2BIT
#define DEFCIPHER2BIT

#include <string>
#include <vector>
#include <seal/seal.h>
#include "CipherBit.h"

class Cipher2Bit{
public:
  //Constructor
  Cipher2Bit(CipherBit &a,CipherBit &b);
  //Getter
  CipherBit getCipherBit0();
  CipherBit getCipherBit1();
  //Setter
  void setCipherBit0(CipherBit &a);
  void setCipherBit1(CipherBit &b);
  //Methods
  /*
    Input : b is the Cipher2Bit to add to the current cipher2Bit
    The cipher2Bit will be override by the result
    The output is the last carry
  */
  CipherBit add(Cipher2Bit b);


  private:
    CipherBit* bit0;
    CipherBit* bit1;
};
#endif