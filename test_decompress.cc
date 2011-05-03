#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
  FILE *plikwe, *plikwy;
  char  tab[10], k1[3]; 
  int   licznik1;    
  long  i, j, ikonw;

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

  licznik1 = 0;
  char znak = 0;

  while (znak != 10)
  {
    fread(&znak, 1, 1, plikwe);
    fwrite(&znak, 1, 1, plikwy);
    licznik1 = licznik1 + 1;       
  }

  for (i = 0; i < 8; i++)
  {
    tab[i] = static_cast<char>(getc(plikwe));

    if ((isdigit(tab[i])) == 0)   
    {
      tab[i] = 0;
      break;
    }
  }

  ikonw = atol(tab);     
  i     = 0;
  fseek(plikwe, licznik1 + 8, SEEK_SET);

  while (i != ikonw)
  {
    fread(k1, 1, 3, plikwe); 

    int ilosc;
    fread(&ilosc, sizeof(ilosc), 1, plikwe); 

    for (j = 0; j < ilosc; j++)
    {
      fwrite(k1, 1, 3, plikwy);  
    }

    i = i + 1;
  }

  fclose(plikwe);
  fclose(plikwy);
  return 0;
}
