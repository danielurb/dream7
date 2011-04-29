#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(void)
{
	FILE *plikwe, *plikwy;		
	char tab[9], k1[3], k2[3];
	char znak, koniec;
	char *t1, *t2;           	
	int j, xres, yres, h;
	int licznik1, ikonwersji;  
	unsigned long i, ilosc, licznik_konw;	

  int licznik2;

	ikonwersji = 8;
	licznik_konw = 0;

	if((plikwe = fopen("images/fisheye.mtv","r+b"))==NULL)  
	{
		printf("Blad otwarcia pliku wejsciowego !\n");
		return 1;
	}

	if((plikwy = fopen("fisheye.k","w+b"))==NULL) 
	{
		printf("Blad otwarcia pliku wyjsciowego !\n");
		return 1;
	}

	for(i=0; i<5; i++)
	{
		tab[i] = getc(plikwe);
		if((isdigit(tab[i]))==0) 
		{
			tab[i]=0;
			break;
		}
	}
	xres = atoi(tab);

	for( i=0; i<5; i++)
	{
		tab[i] = getc(plikwe);
		if((isdigit(tab[i]))==0) 
		{
			tab[i]=0;
			break;
		}
	}
	yres = atoi(tab); 

	fseek(plikwe, 0, SEEK_SET);
	licznik1 = 0;
	while(znak != 10)
	{
		fread(&znak, 1, 1, plikwe);
		fwrite(&znak, 1, 1, plikwy);
		licznik1 = licznik1 + 1;	
	}

	fseek(plikwy, licznik1+ikonwersji, SEEK_SET);
	fread(k1, 1, 3, plikwe);
	strncpy(k2, k1, 3);     
	fseek(plikwe, licznik1 , SEEK_SET);  
	j = strncmp(k1, k2, 3);
	licznik2 = 0;
	i = 0;
	ilosc = (long)xres * (long)yres;
	while(i <= ilosc)
	{
		if(i!=ilosc)
		{
			fread(k1, 1, 3, plikwe);
			j = strncmp(k1, k2, 3);
		}
		if(j != 0 || i == (ilosc))
		{
			fwrite(k2, 1, 3, plikwy);
			if(licznik2 == 0)
			licznik2++;
			fwrite(&licznik2, sizeof(licznik2), 1, plikwy);
			licznik2 = 0;
			strncpy(k2, k1, 3);
			licznik_konw++;     
		}
		licznik2 = licznik2 + 1;	
		i = i + 1;
	}

snprintf(tab, 10, "%ld", licznik_konw);

fseek(plikwy, licznik1, SEEK_SET);
for(i=0; i<9; i++)
{
	if(tab[i] != 0)
	{
		fwrite(&tab[i], 1, 1, plikwy); 
	}
	else break;
}
fclose(plikwe);
fclose(plikwy);
return 0;
}
