#include <vector>
#include <seal/seal.h>
#include <../Structures/CipherBit.h>

using namespace std;
using namespace seal;
void test_xor1bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout << "Table de vérité du XOR sur 1 bit" << endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);

  //Tests
  CipherBit result = myCipherBit0;
  result.XOR(myCipherBit0);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "0 XOR 0 = " << plainResult.to_string() << endl;

  result.XOR(myCipherBit1);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "0 XOR 1 = " << plainResult.to_string() << endl;

  result = myCipherBit1;
  result.XOR(myCipherBit0);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "1 XOR 0 = " << plainResult.to_string() << endl;

  result.XOR(myCipherBit1);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  cout << "1 XOR 1 = " << plainResult.to_string() << endl;
}
void test_add1bit(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  cout << "Table de vérité du + sur 1 bit" << endl;
  Plaintext myPlaintext1("1");Plaintext myPlaintext0("0");
  Plaintext plainResult("0"); Plaintext plainCarry("0");
  Ciphertext myCipher1; encryptor.encrypt(myPlaintext1,myCipher1);
  Ciphertext myCipher0; encryptor.encrypt(myPlaintext0,myCipher0);
  CipherBit myCipherBit1(evaluator,encryptor, myCipher1);
  CipherBit myCipherBit0(evaluator,encryptor, myCipher0);
  CipherBit cipherCarry(evaluator,encryptor, myCipher0);

  //Tests
  CipherBit result = myCipherBit0;
  cipherCarry = result.add(myCipherBit0);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  decryptor.decrypt(cipherCarry.getcipherBit(),plainCarry);
  cout << "0 + 0 = " << plainResult.to_string() << "  carry = " << plainCarry.to_string() << endl;

  cipherCarry = result.add(myCipherBit1);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  decryptor.decrypt(cipherCarry.getcipherBit(),plainCarry);
  cout << "0 + 1 = " << plainResult.to_string() << "  carry = " << plainCarry.to_string() << endl;

  result = myCipherBit1;
  cipherCarry = result.add(myCipherBit0);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  decryptor.decrypt(cipherCarry.getcipherBit(),plainCarry);
  cout << "1 + 0 = " << plainResult.to_string() << "  carry = " << plainCarry.to_string() << endl;

  cipherCarry = result.add(myCipherBit1);
  decryptor.decrypt(result.getcipherBit(),plainResult);
  decryptor.decrypt(cipherCarry.getcipherBit(),plainCarry);
  cout << "1 + 1 = " << plainResult.to_string() << "  carry = " << plainCarry.to_string() << endl;
}

void test_reverse(Evaluator evaluator, Decryptor decryptor,Encryptor encryptor){
  Plaintext myPlaintext1("1"); Plaintext plainResult("0");
  Ciphertext myCipher; encryptor.encrypt(myPlaintext1,myCipher);
  CipherBit cipherBit1(evaluator,encryptor, myCipher);
  cipherBit1.reverse();
  decryptor.decrypt(cipherBit1.getcipherBit(),plainResult);
  cout << "Reverse of 1 is " << plainResult.to_string() << endl;
  Plaintext myPlaintext0("0");
  encryptor.encrypt(myPlaintext0,myCipher);
  CipherBit cipherBit2(evaluator,encryptor, myCipher);
  cipherBit2.reverse();
  decryptor.decrypt(cipherBit2.getcipherBit(),plainResult);
  cout << "Reverse of 0 is " << plainResult.to_string() << endl;
}
int main(){
  //Configuration des paramètres homomorphiques
    EncryptionParameters parms;
    parms.set_poly_modulus("1x^4096 + 1");
    parms.set_coeff_modulus(coeff_modulus_128(4096));
    parms.set_plain_modulus(40961);
  //Validation des paramètres et création du contexte
    SEALContext context(parms);
  //Generation des clées publiques et privées
    KeyGenerator keygen(context);
    PublicKey public_key = keygen.public_key();
    SecretKey secret_key = keygen.secret_key();
    GaloisKeys gal_keys;
    keygen.generate_galois_keys(30, gal_keys);
    EvaluationKeys ev_keys;
    keygen.generate_evaluation_keys(30, ev_keys);
  //Homomorphic Objects
    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

  //Test
  //Plaintext myPlaintext1("1");
  //Plaintext myPlaintext0("0");
  //Ciphertext myCipher; encryptor.encrypt(myPlaintext1,myCipher);
  //CipherBit myFirstBit(evaluator,encryptor, myCipher);
  //myFirstBit.reverse();
  //decryptor.decrypt(myFirstBit.getcipherBit(),myPlaintext1);
  //cout << myPlaintext1.to_string() <<endl;

  //Test with function
  //test_xor1bit(evaluator,decryptor,encryptor);
  //test_add1bit(evaluator,decryptor,encryptor);
  test_reverse(evaluator,decryptor,encryptor);
  return 0;
}
