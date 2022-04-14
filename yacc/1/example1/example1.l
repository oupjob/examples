%{
#include <stdio.h>

enum class TOKEN : int
{
    DIGIT,
    IDENTIFIER
};

#define TOKEN(token) \
printf("Token: " #token " [%s]", yytext); \
return static_cast<int>(TOKEN::token);
%}

alpha [A-Za-z]
digit [0-9]
alnum {alpha}|{digit}

%%

{digit}+            TOKEN(DIGIT);
{alpha}{alnum}+     TOKEN(IDENTIFIER);
[ \t\n+] ;

%%

int main()
{
    yylex();
}
