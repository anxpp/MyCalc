#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <math.h>
#include <stdexcept>
#include "cexpr.h"

using namespace std;


CExpression::CExpression()
{
  Expression="";
}
CExpression::CExpression(string exp)
{
  Expression=exp;
}

void CExpression::SetExpression(string exp)
{
  Expression=exp;
}
char CExpression::GetChar()
{
  if ((unsigned int)pos < Expression.length())
    ch = Expression[pos++];
    else
    ch = '\0';
  return ch;
}
char CExpression::GetNonWhitespace()
{
  GetChar();
  SkipWhitespace();
  return ch;
}
void CExpression::SkipWhitespace()
{
  if (ch == '\t' || ch == ' ') {
    do {
      GetChar();
    } while (ch == '\t' || ch == ' ');
  }
}
double CExpression::CalcAddition()
{
  double Result;
  bool tmp=true;
  double temp;

  Result = CalcMultiplication();
  while (tmp) {
    switch (ch) {

    case '+':
      temp= CalcMultiplication();
      Result =Result +temp;
      break;
    case '-':
    	temp=CalcMultiplication();
        Result =Result - temp;
        break;
    default:
    	tmp=false;
    }
  }
  return Result;
}
double CExpression::CalcMultiplication()
{
  double Result;
  bool tmp=true;
  double temp;

  Result = CalcPower();
  while (tmp) {
    switch (ch) {

    case '*':
    	temp= CalcPower();
        Result = Result * temp;
      break;

    case '/':
    	temp= CalcPower();
        Result = Result /temp;
      break;
    default:
    	tmp=false;
        break;
    }
  }
  return Result;
}


double CExpression::CalcPower()
{
  double Result;
  bool tmp=true;


  Result = CalcSignedTerm();
  while (tmp) {
    switch (ch) {

    case '^':
      Result = exp(log(Result) * CalcPower() );
      break;
    default:
    	tmp=false;
    }
  }
  return Result;
}


double CExpression::CalcSignedTerm()
{
    double Result;

    switch (GetNonWhitespace()) {
    	case '+' :
    	    Result = CalcSignedTerm();
    	    break;
        case '-' :
      	  Result = -CalcSignedTerm();
      	  break;
      default:
      	  Result  = CalcTerm();
   }
  return Result;
}

double CExpression::CalcTerm()
{
    double Result;
    char s[100];
    if (isdigit(ch))
       Result = CalcNumber();
       else
         if (ch=='(')
          Result = CalcExpressionInBrackets();
          else
           {
//             sprintf(s, "Syntax error in expression at position %d", pos);
               throw runtime_error(s);
           }
    return Result;
}


double CExpression::CalcNumber()
{
  double Result ;
  char s[256];

  *s = '\0';
  while (isdigit(ch)) {
    sprintf(s + strlen(s), "%c", ch);
    GetChar();
    if (ch == '.') {
      do {
	sprintf(s + strlen(s), "%c", ch);
	GetChar();
      } while (isdigit(ch));
    }
  }
  sscanf(s,"%lf",&Result); 
  SkipWhitespace();
  return Result;
}


double CExpression::CalcExpressionInBrackets()
{
  double Result;
  char s[100];

  Result = CalcAddition();
  if (ch == ')') {
    GetNonWhitespace();
  }
  else
   {
    sprintf(s,"Mismatched parentheses at position %d", pos );
    throw runtime_error(s);
   }
  return Result;
}

double CExpression::Calculate()
{
  double Result;
  char s[100];
  pos = 0;
  Result = CalcAddition();
  if (ch != '\0')
   {
       sprintf(s,"Unexpected end of expression at position %d", pos + 1);
       throw runtime_error(s);
   }
  return Result;
}