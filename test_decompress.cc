#include <stdio.h>
#include <stdlib.h>


int main(void)
{
  char resolution_string[9];
  fgets(resolution_string, 9, stdin);
  fputs(resolution_string, stdout);

  char tab[10];
  fread(tab, 1, 8, stdin);

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
