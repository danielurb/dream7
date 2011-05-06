#include <stdio.h>
#include <string.h>


//TODO: fix conversion bug (different pixels)


struct Pixel
{
  char r;
  char g;
  char b;
};


bool same_pixel(const Pixel &pixel, const Pixel &prev_pixel)
{
  return (0 == memcmp(&pixel, &prev_pixel, sizeof(Pixel)));
}

bool read_pixel(FILE *input, Pixel &pixel)
{
  return fread(&pixel, sizeof(Pixel), 1, input) > 0;
}

void copy_pixel(Pixel &dst_pixel, const Pixel &src_pixel)
{
  memcpy(&dst_pixel, &src_pixel, sizeof(Pixel));
}

void write_conversion(FILE *output, const Pixel &pixel, int repetition)
{
  fwrite(&pixel, 1, sizeof(Pixel), output);
  fwrite(&repetition, sizeof(repetition), 1, output);
}

void compress(FILE *input, FILE *output)
{
  long xres = 0;
  long yres = 0;

  fscanf(input, "%ld %ld\n", &xres, &yres);
  fprintf(output, "%ld %ld\n", xres, yres);

  Pixel prev_pixel;
  read_pixel(input, prev_pixel);
  int repetitions = 1;

  for (long i = 1; i < (xres * yres); i++)
  {
    Pixel pixel;
    read_pixel(input, pixel);

    if (!same_pixel(pixel, prev_pixel))
    {
      write_conversion(output, prev_pixel, repetitions);
      repetitions = 0;
      copy_pixel(prev_pixel, pixel);
    }

    repetitions++;
  }

  write_conversion(output, prev_pixel, repetitions);
}

void write_pixel(FILE *output, const Pixel &pixel)
{
  fwrite(&pixel, sizeof(pixel), 1, output);
}

int read_int(FILE *input)
{
  int count;
  fread(&count, sizeof(count), 1, input);
  return count;
}

void decompress(FILE *input, FILE *output)
{
  char resolution_string[9];
  fgets(resolution_string, 9, input);
  fputs(resolution_string, output);

  while (true)
  {
    Pixel pixel;

    if (!read_pixel(input, pixel))
    {
      break;
    }

    int pixel_count = read_int(input);

    for (int j = 0; j < pixel_count; j++)
    {
      write_pixel(output, pixel);
    }
  }
}


