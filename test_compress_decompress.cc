#include<stdio.h>
#include"dream7.h"

int main()
{
	FILE * input = fopen("images/fisheye.mtv", "r");
	FILE * output = fopen("temp.k", "w");
	
	compress(input, output);
	
	fclose(input);
	fclose(output);
	
	input = fopen("temp.k", "r");
	output = fopen("output.mtv", "w");
	
	decompress(input, output);
	
	fclose(input);
	fclose(output);
	return 0;
}
