#include <stdio.h>
#include <stdlib.h>


int main(void)
{
  char resolution_string[9];
  fgets(resolution_string, 9, stdin);
  fputs(resolution_string, stdout);

  char tab[10];
  fread(tab, 1, 8, stdin);

  while (true)
  {
    char pixel[3];

    if (!fread(pixel, 1, 3, stdin))
    {
      break;
    }

    int ilosc;
    fread(&ilosc, sizeof(ilosc), 1, stdin);

    for (int j = 0; j < ilosc; j++)
    {
      fwrite(pixel, 1, 3, stdout);
    }
  }

  return 0;
}
