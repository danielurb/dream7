#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
  FILE *plikwe, *plikwy;

  long ikonw;

  if ((plikwe = fopen("fisheye.k", "r+b")) == NULL)
  {
    printf("Blad otwarcia pliku wejsciowego !");
    return 1;
  }

  if ((plikwy = fopen("output.mtv", "w+b")) == NULL)
  {
    printf("Blad otwarcia pliku wysciowego !");
    return 1;
  }

  char znak = 0;

  while (znak != 10)
  {
    fread(&znak, 1, 1, plikwe);
    fwrite(&znak, 1, 1, plikwy);
  }

  char tab[10];

  for (int i = 0; i < 8; i++)
  {
    tab[i] = static_cast<char>(fgetc(plikwe));
  }

  ikonw = atol(tab);
  int i = 0;

  while (i != ikonw)
  {
    char k1[3];
    fread(k1, 1, 3, plikwe);

    int ilosc;
    fread(&ilosc, sizeof(ilosc), 1, plikwe);

    for (int j = 0; j < ilosc; j++)
    {
      fwrite(k1, 1, 3, plikwy);
    }

    i++;
  }

  fclose(plikwe);
  fclose(plikwy);
  return 0;
}
