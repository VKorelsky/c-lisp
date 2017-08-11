#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>
#include "mpc.h"

void init_mpc() {
  /* mpc logic */
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

    mpc_cleanup(4, Number, Operator, Expr, Kispy);
}

void mpc_parse(){
  /* parse user input */
  mpc_result_t r;

  if(mpc_parse("<stdin>", input, Lispy, &r) {
    /* success */
    mpc_ast_print(r.output);
    mpc_ast_delete(r.output);
  } else {
    /* error */
    mpc_ast_print(r.error);
    mpc_ast_delete(r.error);
  }
}

int main(int argc, char** argv) {
  init_mpc();

  puts("Kisp Version 0.0.0.1");
  puts("Press Ctrl+c to exit");

  while(1) {

    char* input = readline("Kisp> ");
    add_history(input);

    printf("You wrote %s\n", input);
    free(input);
  }

  return 0;
}
