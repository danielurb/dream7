#include<stdio.h>
#include"dream7.h"

int main(int /*argc*/, char *argv[])
{
	FILE * input = fopen(argv[1], "r");
	FILE * output = fopen("temp.k", "w");
	
	compress(input, output);
	
	fclose(input);
	fclose(output);
	
	input = fopen("temp.k", "r");
	output = fopen(argv[2], "w");
	
	decompress(input, output);
	
	fclose(input);
	fclose(output);
	return 0;
}
