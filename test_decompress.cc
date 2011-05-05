#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
  char znak = 0;

  while (znak != 10)
  {
    fread(&znak, 1, 1, stdin);
    fwrite(&znak, 1, 1, stdout);
  }

  char tab[10];

  for (int i = 0; i < 8; i++)
  {
    tab[i] = static_cast<char>(fgetc(stdin));
  }

  long ikonw = atol(tab);
  int  i     = 0;

  while (i != ikonw)
  {
    char k1[3];
    fread(k1, 1, 3, stdin);

    int ilosc;
    fread(&ilosc, sizeof(ilosc), 1, stdin);

    for (int j = 0; j < ilosc; j++)
    {
      fwrite(k1, 1, 3, stdout);
    }

    i++;
  }

  return 0;
}
