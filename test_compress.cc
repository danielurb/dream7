#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
  FILE *plikwe = fopen("images/fisheye.mtv", "r+b");

  if (!plikwe)
  {
    printf("Blad otwarcia pliku wejsciowego !\n");
    return 1;
  }

  FILE *plikwy = fopen("fisheye.k", "w+b");

  if (!plikwy)
  {
    printf("Blad otwarcia pliku wyjsciowego !\n");
    fclose(plikwe);
    return 1;
  }

  char tab[9];

  for (int i = 0; i < 5; i++)
  {
    tab[i] = getc(plikwe);

    if ((isdigit(tab[i])) == 0)
    {
      tab[i] = 0;
      break;
    }
  }

  int xres = atoi(tab);

  for (int i = 0; i < 5; i++)
  {
    tab[i] = getc(plikwe);

    if ((isdigit(tab[i])) == 0)
    {
      tab[i] = 0;
      break;
    }
  }

  int yres = atoi(tab);
  
  fprintf(plikwy,"%d %d\n", xres, yres);

  int licznik1 = ftell(plikwy);
  int ikonwersji = 8;
  fseek(plikwy, licznik1 + ikonwersji, SEEK_SET);
  char k1[3];
  fread(k1, 1, 3, plikwe);
  char prev_pixel[3];
  memcpy(prev_pixel, k1, 3);
  fseek(plikwe, licznik1, SEEK_SET);
  int j = 0;
  int licznik2 = 0;
  int i = 0;
  unsigned long ilosc = (long)xres * (long)yres;
  unsigned long licznik_konw = 0;

  while (i <= ilosc)
  {
    bool last_loop = (i == ilosc);

    if (!last_loop)
    {
      fread(k1, 1, 3, plikwe);
      j = memcmp(k1, prev_pixel, 3);
    }

    if ((j != 0) || last_loop)
    {
      fwrite(prev_pixel, 1, 3, plikwy);

      if (licznik2 == 0)
      {
        licznik2++;
      }

      fwrite(&licznik2, sizeof(licznik2), 1, plikwy);
      licznik2 = 0;
      memcpy(prev_pixel, k1, 3);
      licznik_konw++;
    }

    licznik2++;
    i++;
  }

  snprintf(tab, 10, "%ld", licznik_konw);

  fseek(plikwy, licznik1, SEEK_SET);

  for (i = 0; i < 9; i++)
  {
    if (tab[i] != 0)
    {
      fwrite(&tab[i], 1, 1, plikwy);
    }
    else
    {
      break;
    }
  }

  fclose(plikwe);
  fclose(plikwy);
  return 0;
}

