#ifndef NUMBERTHEORY_H
#define NUMBERTHEORY_H
#include "ReallyLongInt.h"

template <class X>
bool isPrime(const X& num)
{
  if(num == 1 || num == 0)
    {
      return(false);
    }
  else
    {
      for(int i = 2; i <= num/2; i++)
	{
	  if((num%i) == 0)
	    {
	      return(false);
	    }
	}
    }
  return(true);
}

template <class X>
X modPower(const X& base, const X& exponent, const X& modulus)
{
  if(exponent == 1)
    {
      return(base%modulus);
    }
  else if(base == 0)
    {
      return(0);
    }
  else if(exponent == 0)
    {
      return(1%modulus);
    }
  else
    {
      ReallyLongInt ans = modPower(base, exponent/2, modulus);
      if(exponent%2 == 0)
	{
	  return(((ans%modulus)*(ans%modulus))%modulus);
	}
      else
	{
	  return((((base%modulus)*(ans%modulus))%modulus * (ans%modulus))%modulus);
	}
    }
}

template <class X>
X extendedEuclid(const X& a, const X& b, X& x, X& y)
{
  if(b == 0)
    {
      x = 1;
      y = 0;
      return(a);
    }
  else
    {
      ReallyLongInt newX;
      ReallyLongInt newY;
      ReallyLongInt gcd = extendedEuclid(b, a%b, newX, newY);
      x = newY;
      y = newX - (a/b)*newY;
      return(gcd);
    }
}

#endif
