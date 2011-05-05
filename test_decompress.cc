#include <stdio.h>
#include <stdlib.h>


int main(void)
{
  char resolution_string[9];
  fgets(resolution_string, 9, stdin);
  fputs(resolution_string, stdout);

  while (true)
  {
    char pixel[3];

    if (!fread(pixel, 1, 3, stdin))
    {
      break;
    }

    int pixel_count;
    fread(&pixel_count, sizeof(pixel_count), 1, stdin);

    for (int j = 0; j < pixel_count; j++)
    {
      fwrite(pixel, 1, 3, stdout);
    }
  }

  return 0;
}
