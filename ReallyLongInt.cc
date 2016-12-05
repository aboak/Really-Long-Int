#include <iostream>
#include <string>
#include <cmath>
#include <climits>

#include "ReallyLongInt.h"

using namespace std;

ReallyLongInt::ReallyLongInt()
{
  isNeg = false;
  digits = new unsigned char[1];
  digits[0] = 0;
  numDigits = 1;
}

ReallyLongInt::ReallyLongInt(const string& numStr)
{
  isNeg = false;
  numDigits = numStr.size();
  unsigned counter = 0;
  if(numStr[0] == '-')
    {
      isNeg = true;
      counter++;
    }
  digits = new unsigned char[numDigits];
  for(unsigned i = counter; i < numDigits; i++)
    {
      long input = long(numStr[i]);
      input -= 48;
      digits[i] = input;
    }
  removeLeadingZeros();
}

ReallyLongInt::ReallyLongInt(long long num)
{
  if(num == 0)
    {
      isNeg = false;
      numDigits = 1;
      digits = new unsigned char[1];
      digits[0] = 0;
    }
  else
    {
      isNeg = false;
      if(num < 0)
	{
	  isNeg = true;
	  num *= -1;
	}
      numDigits = log10(num)+1;
      digits = new unsigned char[numDigits];
      unsigned long base = num;
      for(unsigned i = 1; i <= numDigits; i++)
	{
	  long input = base%10;
	  digits[numDigits-i] = input;
	  base = base/10;
	}
    }
}

ReallyLongInt::ReallyLongInt(bool isNeg, unsigned char* digits, unsigned numDigits)
{
  this->isNeg = isNeg;
  this->digits = digits;
  this->numDigits = numDigits;
  removeLeadingZeros();
}

ReallyLongInt::ReallyLongInt(const ReallyLongInt& other)
{
  this->numDigits = other.numDigits;
  this->isNeg = other.isNeg;
  this->digits = new unsigned char[other.numDigits];
  for(unsigned i = 0; i < this->numDigits; i++)
    {
      this->digits[i] = other.digits[i];
    }
  this->removeLeadingZeros();
}

ReallyLongInt::~ReallyLongInt()
{
  delete[] digits;
}

//VOID METHODS

void ReallyLongInt::removeLeadingZeros()
{
  unsigned counter = 0;
  for(unsigned i = 0; i < numDigits; i++)
    {
      if(digits[i] == 0)
	{
	  counter++;
	}
      else
	{
	  break;
	}
    }
  if(counter == numDigits)
    {
      numDigits = 1;
    }
  else
    {
      for(unsigned i = counter; i < numDigits; i++)
	{
	  digits[i-counter] = digits[i];
	}
      for(unsigned i = 1; i < counter+1; i++)
	{
	  digits[numDigits-i] = 0;
	}
      numDigits -= counter;
    }
}

void ReallyLongInt::flipSign()
{
  if(isNeg)
    {
      isNeg = false;
    }
  else
    {
      isNeg = true;
    }
}

void ReallyLongInt::div(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
  this->absDiv(other, quotient, remainder);
  if((this->isNeg && (other.isNeg == false)) || ((this->isNeg == false) && other.isNeg))
    {
      quotient.flipSign();
    }
}

void ReallyLongInt::absDiv(const ReallyLongInt& other, ReallyLongInt& quotient, ReallyLongInt& remainder) const
{
  ReallyLongInt x = *this;
  ReallyLongInt y = other;
  x.isNeg = false;
  y.isNeg = false;
  remainder = 0;
  quotient.numDigits = x.numDigits;
  delete[] quotient.digits;
  quotient.digits = new unsigned char[quotient.numDigits];
  for(unsigned i = 0; i < quotient.numDigits; i++)
    {
      quotient.digits[i] = 0;
    }
  for(unsigned i = 0; i < x.numDigits; i++)
    {
      remainder *= 10;
      remainder += x.digits[i];
      unsigned d = 0;
      while(remainder >= y)
	{
	  remainder -= y;
	  d++;
	}
      quotient.digits[i] = d;
    }
  if((this->isNeg && other.isNeg) || (this->isNeg && (other.isNeg == false)))
    {
      remainder.isNeg = true;
    }
  else
    {
      remainder.isNeg = false;
    }
  quotient.removeLeadingZeros();
  remainder.removeLeadingZeros();
}

//OPERATOR METHODS

long long ReallyLongInt::toLongLong() const
{
  ReallyLongInt temp = *this;
  ReallyLongInt num = LLONG_MAX;
  num += 1;
  temp %= num;
  long long ans = 0;
  unsigned power = 10;
  for(unsigned i = 0; i < temp.numDigits-2; i++)
    {
      power *= 10;
    }
  for(unsigned i = 0; i < temp.numDigits; i++)
    {
      ans += (temp.digits[i]) * power;
      power /= 10;
    }
  if(this->isNeg)
    {
      ans *= -1;
    }
  return(ans);
}

ReallyLongInt ReallyLongInt::add(const ReallyLongInt& other) const
{
  if(this->isNeg)
    {
      if(other.isNeg)
	{
	  ReallyLongInt ans(this->absAdd(other));
	  ans.flipSign();
	  return(ans);
	}
      else
	{
	  if(this->absGreater(other))
	    {
	      ReallyLongInt ans(this->absSub(other));
	      ans.flipSign();
	      return(ans);
	    }
	  else
	    {
	      ReallyLongInt ans(other.absSub(*this));
	      return(ans);
	    }
	}
    }
  else
    {
      if(other.isNeg)
	{
	  if(this->absGreater(other))
	    {
	      ReallyLongInt ans(other.absSub(*this));
	      ans.flipSign();
	      return(ans);
	    }
	  else
	    {
	      ReallyLongInt ans(this->absSub(other));
	      return(ans);
	    }
	}
      else
	{
	  ReallyLongInt ans(this->absAdd(other));
	  return(ans);
	}
    }
}

ReallyLongInt ReallyLongInt::sub(const ReallyLongInt& other) const
{
  if(this->isNeg)
    {
      if(other.isNeg)
	{
	  ReallyLongInt ans(this->absSub(other));
	  ans.flipSign();
	  return(ans);
	}
      else
	{
	  ReallyLongInt ans(other.absAdd(*this));
	  ans.flipSign();
	  return(ans);
	}
    }
  else
    {
      if(other.isNeg)
	{
	  ReallyLongInt ans(this->absAdd(other));
	  return(ans);
	}
      else
	{
	  ReallyLongInt ans(this->absSub(other));
	  return(ans);
	}
    }
}

ReallyLongInt ReallyLongInt::mult(const ReallyLongInt& other) const
{
  ReallyLongInt ans(this->absMult(other));
  if((this->isNeg && other.isNeg) || (this->isNeg == false && other.isNeg == false))
    {
      return(ans);
    }
  else
    {
      ans.flipSign();
      return(ans);
    }
}

ReallyLongInt ReallyLongInt::absMult(const ReallyLongInt& other) const
{
  unsigned resultSize = this->numDigits + other.numDigits;
  unsigned char* ans = new unsigned char[resultSize];
  for(unsigned i = 0; i < resultSize; i++)
    {
      ans[i] = 0;
    }
  for(int i = this->numDigits; i > 0; i--)
    {
      for(int j = other.numDigits; j > 0; j--)
	{
	  int input = this->digits[i-1]*other.digits[j-1];
	  ans[i+j-1] += input%10;
	  ans[i+j-2] += input/10;
	}
    }
  for(int i = resultSize; i > 0; i--)
    {
      if(ans[i-1] > 9)
	{
	  int temp = ans[i-1];
	  ans[i-1] = temp%10;
	  ans[i-2] += temp/10;
	}
    } 
  ReallyLongInt answer(false, ans, resultSize);
  answer.removeLeadingZeros();
  return(answer);
}

ReallyLongInt ReallyLongInt::absSub(const ReallyLongInt& other) const
{
  const unsigned char* big;
  const unsigned char* little;
  unsigned bigSize;
  unsigned littleSize;
  bool sign;

  if(this->numDigits >= other.numDigits)
    {
      if(this->absGreater(other))
	{
	  big = this->digits;
	  bigSize = this->numDigits;
	  little = other.digits;
	  littleSize = other.numDigits;
	  sign = false;
	}
      else
	{
	  big = other.digits;
	  bigSize = other.numDigits;
	  little = this->digits;
	  littleSize = this->numDigits;
	  if(other.absGreater(*this))
	    {
	      sign = true;
	    }
	  else
	    {
	      sign = false;
	    }
	}
    }
  else
    {
      big = other.digits;
      bigSize = other.numDigits;
      little = this->digits;
      littleSize = this->numDigits;
      sign = true;
    }
  unsigned resultSize = bigSize;
  unsigned char* ans = new unsigned char[resultSize];
  int carry = 0;
  for(unsigned i = 0; i < resultSize; i++)
    {
      ans[i] = 0;
    }
  int counter = littleSize-1;
  for(int i = bigSize-1; i >= int(bigSize-littleSize); i--)
    {
      if((big[i] - carry) < little[counter])
	{
	  ans[i] = (((big[i] + 10) - little[counter]) - carry);
	  carry = 1;
	  counter--;
	}
      else
	{
	  ans[i] = ((big[i] - little[counter]) - carry);
	  carry = 0;
	  counter--;
	}
    }
  for(int i = (bigSize-littleSize) - 1; i >= 0; i--)
    {
      if(big[i] - carry < 0)
	{
	  ans[i] = ((big[i] + 10) - carry);
	  carry = 1;
	}
      else
	{
	  ans[i] = (big[i] - carry);
	  carry = 0;
	}
    }
  ReallyLongInt answer(sign, ans, resultSize);
  answer.removeLeadingZeros();
  return(answer);
}

ReallyLongInt ReallyLongInt::absAdd(const ReallyLongInt& other) const
{
  unsigned carry = 0;
  const unsigned char* big;
  const unsigned char* little;
  unsigned bigSize = 0;
  unsigned littleSize = 0;

  if(this->numDigits > other.numDigits)
    {
      big = this->digits;
      bigSize = this->numDigits;
      little = other.digits;
      littleSize = other.numDigits;
    }
  else
    {
      big = other.digits;
      bigSize = other.numDigits;
      little = this->digits;
      littleSize = this->numDigits;
    }
  unsigned resultSize = bigSize+1;
  unsigned char* ans = new unsigned char[resultSize];
  for(unsigned i = 0; i < resultSize; i++)
    {
      ans[i] = 0;
    }
  for(unsigned i = 1; i <= littleSize; i++)
    {
      unsigned input = big[bigSize-i] + little[littleSize-i] + carry;
      if((input) > 9)
	{
	  input -= 10;
	  carry = 1;
	}
      else
	{
	  carry = 0;
	}
      ans[(bigSize+1)-i] = input;
    }
  for(unsigned i = littleSize+1; i <= bigSize; i++)
    {
      unsigned input = big[bigSize-i] + carry;
      if((big[bigSize-i] + carry) > 9)
	{
	  input -= 10;
	  carry = 1;
	}
      else
	{
	  carry = 0;
	}
      ans[(bigSize+1)-i] = input;
    }
  if(carry >= 1)
    {
      ans[0] = 1;
    }
  ReallyLongInt answer(false, ans, resultSize);
  answer.removeLeadingZeros();
  return(answer);
}

ReallyLongInt operator/(const ReallyLongInt& x, const ReallyLongInt& y)
{
  ReallyLongInt q,r;
  x.div(y, q, r);
  return(q);
}

ReallyLongInt operator%(const ReallyLongInt& x, const ReallyLongInt& y)
{
  ReallyLongInt q,r;
  x.div(y, q, r);
  return(r);
}

ReallyLongInt& ReallyLongInt::operator/=(const ReallyLongInt& other)
{
  ReallyLongInt q,r;
  this->div(other, q, r);
  *this = q;
  this->removeLeadingZeros();
  return(*this);
}

ReallyLongInt& ReallyLongInt::operator%=(const ReallyLongInt& other)
{
  ReallyLongInt q,r;
  this->div(other, q, r);
  *this = r;
  this->removeLeadingZeros();
  return(*this);
}

ReallyLongInt operator*(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return(x.mult(y));
}

ReallyLongInt operator+(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return(x.add(y));
}

ReallyLongInt operator-(const ReallyLongInt& x, const ReallyLongInt& y)
{
  return(x.sub(y));
}

ReallyLongInt& ReallyLongInt::operator*=(const ReallyLongInt& other)
{
  *this = this->mult(other);
  return(*this);
}

ReallyLongInt& ReallyLongInt::operator+=(const ReallyLongInt& other)
{
  *this = this->add(other);
  return(*this);
}

ReallyLongInt& ReallyLongInt::operator-=(const ReallyLongInt& other)
{
  *this = this->sub(other);
  return(*this);
}

ReallyLongInt& ReallyLongInt::operator++()
{
  ReallyLongInt one(1);
  *this = this->add(one);
  return(*this);
}

ReallyLongInt& ReallyLongInt::operator--()
{
  ReallyLongInt one(1);
  *this = this->sub(one);
  return(*this);
}

ReallyLongInt ReallyLongInt::operator++(int dummy)
{
  ReallyLongInt one(1);
  ReallyLongInt temp(this->isNeg, this->digits, this->numDigits);
  *this = this->add(one);
  return(temp);
}

ReallyLongInt ReallyLongInt::operator--(int dummy)
{
  ReallyLongInt one(1);
  ReallyLongInt temp(this->isNeg, this->digits, this->numDigits);
  *this = this->sub(one);
  return(temp);
}

ReallyLongInt ReallyLongInt::operator-() const
{
  ReallyLongInt copy(*this);
  if(this->isNeg)
    {
      copy.isNeg = false;
    }
  else if(this->isNeg == false)
    {
      copy.isNeg = true;
    }
  return(copy);
}

ReallyLongInt& ReallyLongInt::operator=(const ReallyLongInt& other)
{
  ReallyLongInt temporary(other);
  this->numDigits = temporary.numDigits;
  this->isNeg = temporary.isNeg;
  delete[] this->digits;
  this->digits = new unsigned char[temporary.numDigits];
  for(unsigned i = 0; i < this->numDigits; i++)
    {
      this->digits[i] = temporary.digits[i];
    }
  temporary.numDigits = 1;
  temporary.isNeg = false;
  delete[] temporary.digits;
  temporary.digits = new unsigned char[1];
  temporary.digits[0] = 0;
  return(*this);
}

bool ReallyLongInt::equal(const ReallyLongInt& other) const
{
  if(this->digits[0] == 0 && other.digits[0] == 0)
    {
      return(true);
    }
  if(this->isNeg != other.isNeg)
    {
      if(this->numDigits == other.numDigits)
	{
	  if(this->digits[0] == 0 && other.digits[0] == 0)
	    {
	      return(true);
	    }
	}
      return(false);
    }
  else
    {
      for(unsigned i = 0; i < this->numDigits; i++)
	{
	  if(this->digits[i] != other.digits[i])
	    {
	      return(false);
	    }
	}
    }
  return(true);
}

bool ReallyLongInt::absGreater(const ReallyLongInt& other) const
{
  if(this->numDigits < other.numDigits)
    {
      return(false);
    }
  if(this->numDigits > other.numDigits)
    {
      return(true);
    }
  for(unsigned i = 0; i < this->numDigits; i++)
    {
      if(this->digits[i] > other.digits[i])
	{
	  return(true);
	}
      else if(this->digits[i] < other.digits[i])
	{
	  return(false);
	}
    }
  return(false);
}

bool ReallyLongInt::greater(const ReallyLongInt& other) const
{
  if(this->absGreater(other))
    {
      if(this->isNeg)
	{
	  return(false);
	}
      else
	{
	  return(true);
	}
    }
  else
    {
      if(other.isNeg)
	{
	  return(true);
	}
      else
	{
	  return(false);
	}
    }
}

bool operator==(const ReallyLongInt& x, const ReallyLongInt& y)
{
  if(x.greater(y))
    {
      return(false);
    }
  if(y.greater(x))
    {
      return(false);
    }
  return(true);
}

bool operator!=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  if(x.greater(y))
    {
      return(true);
    }
  if(y.greater(x))
    {
      return(true);
    }
  return(false);
}

bool operator>(const ReallyLongInt& x, const ReallyLongInt& y)
{
  if(x.greater(y))
    {
      return(true);
    }
  return(false);
}

bool operator<(const ReallyLongInt& x, const ReallyLongInt& y)
{
  if(y.greater(x))
    {
      return(true);
    }
  return(false);
}

bool operator>=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  if(y.greater(x))
    {
      return(false);
    }
  return(true);
}

bool operator<=(const ReallyLongInt& x, const ReallyLongInt& y)
{
  if(x.greater(y))
    {
      return(false);
    }
  return(true);
}

//PRINT METHODS

ostream& ReallyLongInt::print(ostream& out) const
{
  if(isNeg && this->digits[0] != 0)
    {
      out << '-';
    }
  for(unsigned i = 0; i < numDigits; i++)
    {
      out << long(digits[i]);
    }
  return(out);
}

ostream& operator<<(ostream& out, const ReallyLongInt& x)
{
  x.print(out);
  return(out);
}
