#ifndef DEFCIPHERBIT
#define DEFCIPHERBIT

#include <string>
#include <vector>
#include <seal/seal.h>

class CipherBit{
public:
  //Constructor
  CipherBit(seal::Evaluator &evaluator, seal::Ciphertext);
  //Getter
  seal::Ciphertext getcipherBit();
  //Setter
  void setcipherBit(seal::Ciphertext a);
  //Methods
  CipherBit add(CipherBit b);
  void negate();
  CipherBit multiply(CipherBit b);

  seal::Ciphertext cipherBit; //A cipherbit is composed by one Ciphertext wich will either be the polynomial "0" or "1"
  seal::Evaluator* evaluator; //Use an adress to avoid calling a constructor (witch won't exist)
};
#endif