/* 
   This program shows the different runtime checks available for checking various
   arithmetic behavior. 
   All arithmetic checks have examples that will be triggered when running this program
   if all options are enabled.
   By turning of the options for explicit conversions, unsigned shift overflows and
   unsigned integer overflows the program also demonstrates the possibility to 
   not check code that might rely on the overflow behavior for unsigned entities.   
*/


int i = 5,j = 0;
char ch = 0;
short s = 0;

/* Division by zero */
void div(void)
{
  j = i / j;  
}

/* Implicit integer conversion failure */
void conv(void)
{
  ch = i * 100;
}

/* 
  Explicit integer conversion failure. 
  Checks for failure at explicit conversions can be turned off.
*/
void explicit_conv(void)
{
  ch = (char)(i * 100);
}

/* Unhandled switch case */
void sw(void)
{
  switch(ch)
  {
  case 0: i = 3; break;
  case 5: i = 2; break;
  }
}

/* Potential signed integer overflow */
int signed_over(int a)
{
  return a+2;
}

/* 
  Potential unsigned integer overflow 
  Checks for unsigned integer overflow can be turned off if overflow 
  behavior is desired 
*/
unsigned int unsigned_over(unsigned int a)
{
  return a+2;
}

/* Possible signed shift overflow */
int shl(int a)
{
  return a << 1;
}

/* 
  Possible unsigned shift overflow. 
  Checks for unsigned shift overflow can be explicitly turned off if 
  overflow behavior is desired.
*/
unsigned int unsigned_shl(unsigned int a)
{
  return a << 1;
}


int main(void)
{
  int a = 0x7FFFFFFF;
  unsigned int b = 0xFFFFFFFF;
  div();
  conv();
  explicit_conv();
  sw();
  a = signed_over(a);
  b = unsigned_over(b);
  
  a = 0x7FFFFFFF;
  a = shl(a);
  b = 0xFFFFFFFF;
  b = unsigned_shl(b);
  return 0;
}
