#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

char* readline(char* prompt){
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}



int main(int argc, char** argv) {

  puts("Kisp Version 0.0.0.1");
  puts("Press Ctrl+c to exit");

  while(1) {
    char* input = readline("Kisp> ");
    add_history(input);

    printf("%s\n", input);
    free(input);
  }

  return 0;
}
