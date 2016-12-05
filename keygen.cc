#include <iostream>
#include <fstream>
#include <cstdlib>
#include "numberTheory.h"

using namespace std;

int main(int argc, char** argv)
/*
  This function creates new public and private .txt files to be used as encryption/decryption keys.
 */
{
  string b = argv[1];
  string a = argv[2];
  ReallyLongInt p = b;
  ReallyLongInt q = a;
  if(p > 100000 || q > 100000)
    {
      cout << "At least of the provided numbers is too large to be computed for primality." << endl;
    }
  else if(!isPrime(p) || !isPrime(q))
    {
      cout << "One of the provided integers is not prime, exiting function." << endl;
      return(1);
    }
  ReallyLongInt n = p*q;
  ReallyLongInt t = (p-1)*(q-1);
  bool gcd = false;
  ReallyLongInt e = 2;
  ReallyLongInt px;
  ReallyLongInt py;
  while(gcd == false && e < t)
    {
      if(extendedEuclid(e, t, px, py) == 1)
	{
	  gcd = true;
	    }
      else
	{
	  e++;
	}
    }
  ReallyLongInt d = px;
  if(d < 0)
    {
	  d += t;
    }
  if(e < 0)
    {
      e += t;
    }
  ofstream fout(argv[3]);
  ofstream fout2(argv[4]);
  fout << e << " " << n;
  fout2 << d << " " << n;
}
