%{
/* Объявления C */
#define YYSTYPE double
#include <math.h>
%}

/* Объявления Bison */
%token NUM

%%

input:    /* пусто */
        | input line
;

line:     '\n'
        | exp '\n'  { printf ("\t%.10g\n", $1); }
;

exp:      NUM             { $$ = $1;         }
        | exp exp '+'     { $$ = $1 + $2;    }
        | exp exp '-'     { $$ = $1 - $2;    }
        | exp exp '*'     { $$ = $1 * $2;    }
        | exp exp '/'     { $$ = $1 / $2;    }
      /* возведение в степень */
        | exp exp '^'     { $$ = pow ($1, $2); }
      /* унарный минус        */
        | exp 'n'         { $$ = -$1;        }
;
%%
/* Дополнительный код на C */

