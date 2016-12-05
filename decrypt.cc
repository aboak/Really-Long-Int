#include <iostream>
#include <fstream>
#include "numberTheory.h"

using namespace std;

int main(int argc, char *argv[])
/*
  This main function reads the encrypted.txt file and writes the decrypted text to a new output file.
 */
{
  ifstream fin(argv[1]);
  ifstream fin2(argv[2]);
  ofstream fout(argv[3]);
  unsigned long long a;
  unsigned long long b;
  fin >> a;
  fin >> b;
  ReallyLongInt d = a;
  ReallyLongInt n = b;
  unsigned long long temporary;
  char character;
  fin2 >> temporary;
  while(!fin2.eof())
    {
      ReallyLongInt i = temporary;
      ReallyLongInt j = modPower(i, d, n);
      long long h = j.toLongLong();
      character = h;
      fout << character;
      fin2 >> temporary;
    }
}
