#include <iostream>
#include <fstream>
#include "numberTheory.h"

using namespace std;

int main(int argc, char *argv[])
/*
  This main function reads text from the plaintext.txt file and converts the characters into encrypted numbers using the modPower function. It then writes these numbers to a new file.
 */
{
  ifstream fin(argv[1]);
  ifstream fin2(argv[2]);
  ofstream fout(argv[3]);
  string m;
  string o;
  fin >> m;
  fin >> o;
  ReallyLongInt e = m;
  ReallyLongInt n = o;
  char x;
  while(fin2.get(x))
    {
      ReallyLongInt b = x;
      fout << modPower(b, e, n) << endl;
    }
}
