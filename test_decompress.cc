#include <stdio.h>
#include <stdlib.h>

void decompress(FILE *input, FILE *output);

int main(void)
{
  decompress(stdin, stdout);
  return 0;
}
