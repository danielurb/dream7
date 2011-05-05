#include <stdio.h>
#include <stdlib.h>

struct Pixel
{
  char r;
  char g;
  char b;
};

void decompress(FILE *input, FILE *output)
{
  char resolution_string[9];
  fgets(resolution_string, 9, input);
  fputs(resolution_string, output);

  while (true)
  {
    Pixel pixel;

    if (!fread(&pixel, 1, sizeof(pixel), stdin))
    {
      break;
    }

    int pixel_count;
    fread(&pixel_count, sizeof(pixel_count), 1, stdin);

    for (int j = 0; j < pixel_count; j++)
    {
      fwrite(&pixel, 1, sizeof(pixel), stdout);
    }
  }
}

int main(void)
{
  decompress(stdin, stdout);
  return 0;
}
