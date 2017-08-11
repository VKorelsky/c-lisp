#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>
#include "mpc.h"

int nb_nodes(mpc_ast_t* t) {
  /* return number of nodes in a tree, recursively*/
  if (t->children_num == 0) {return 1;}
  if (t->children_num >= 1) {
    int total = 1;
    for (int i = 0; i < t->children_num; i++) {
      total += nb_nodes(t->children[i]);
    }
    return total;
  }
  return 0;
}

int main(int argc, char** argv) {
  /* define language parsers */
  mpc_parser_t* Number   = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr     = mpc_new("expr");
  mpc_parser_t* Kispy    = mpc_new("kispy");

  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                   \
    number   : /-?[0-9]+/ ;                             \
    operator : '+' | '-' | '*' | '/' ;                  \
    expr     : <number> | '(' <operator> <expr>+ ')' ;  \
    kispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
    Number, Operator, Expr, Kispy);

  puts("Kisp Version 0.0.0.1");
  puts("Press Ctrl+c to exit");

  /* REPL loop */
  while(1) {

    char* input = readline("Kisp> ");
    add_history(input);

    mpc_result_t r;

    if (mpc_parse("<stdin>", input, Kispy, &r)) {
      /* Success */
      
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* Error */

      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }

  mpc_cleanup(4, Number, Operator, Expr, Kispy);

  return 0;
}
