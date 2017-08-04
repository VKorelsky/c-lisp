#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>
#include <mpc.h>

int main(int argc, char** argv) {

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
