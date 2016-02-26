#pragma once
#include <string>
using namespace std;
class CExpression
{
     int pos;
     char ch;
     string Expression;

     char GetChar();
     char GetNonWhitespace();
     void SkipWhitespace();
     double CalcAddition();
     double CalcMultiplication();
     double CalcPower();
     double CalcSignedTerm();
     double CalcTerm();
     double CalcNumber();
     double CalcExpressionInBrackets();
     public:
       CExpression(string exp);
       CExpression();
       void SetExpression(string exp);
       double Calculate();
};

