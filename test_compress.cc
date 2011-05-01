#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
  long xres = 0;
  long yres = 0;

  fscanf(stdin, "%ld %ld\n", &xres, &yres);
  fprintf(stdout, "%ld %ld\n", xres, yres);

  fwrite("7840\x0\x0\x0\x0",8,1,stdout);
    
  char prev_pixel[3];
  fread(prev_pixel, 1, sizeof(prev_pixel), stdin);
  int repetitions = 1;
   
  long ilosc = xres * yres;
  for(long i = 1; i <= ilosc; i++)
  {
    char pixel[3];
    bool last_loop = (i == ilosc);
		bool equal = false;
    if (!last_loop)
    {
      fread(pixel, 1, sizeof(pixel), stdin);
      equal = (memcmp(pixel, prev_pixel, sizeof(pixel)) == 0);
    }

    if (!equal || last_loop)
    {
      fwrite(prev_pixel, 1, sizeof(pixel), stdout);
      fwrite(&repetitions, sizeof(repetitions), 1, stdout);
      repetitions = 0;
      memcpy(prev_pixel, pixel, sizeof(pixel));
    }

    repetitions++;
  }
  return 0;
}

