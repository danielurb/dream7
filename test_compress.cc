#include <stdio.h>

void compress(FILE *input, FILE *output);

int main(void)
{
  compress(stdin, stdout);
  return 0;
}
