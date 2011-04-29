#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(void)
{		
  FILE *plikwe = fopen("images/fisheye.mtv","r+b");
  if(!plikwe)  
	{
		printf("Blad otwarcia pliku wejsciowego !\n");
		return 1;
	}

  FILE *plikwy = fopen("fisheye.k","w+b");
	if(!plikwy) 
	{
		printf("Blad otwarcia pliku wyjsciowego !\n");
		fclose(plikwe);
		return 1;
	}

	char tab[9];
	for(int i=0; i<5; i++)
	{
		tab[i] = getc(plikwe);
		if((isdigit(tab[i]))==0) 
		{
			tab[i]=0;
			break;
		}
	}
	int xres = atoi(tab);

	for( int i=0; i<5; i++)
	{
		tab[i] = getc(plikwe);
		if((isdigit(tab[i]))==0) 
		{
			tab[i]=0;
			break;
		}
	}
	
	int yres = atoi(tab); 

	fseek(plikwe, 0, SEEK_SET);
	int licznik1 = 0;
	char znak;
	while(znak != 10)
	{
		fread(&znak, 1, 1, plikwe);
		fwrite(&znak, 1, 1, plikwy);
		licznik1++;	
	}

	int ikonwersji = 8;
	fseek(plikwy, licznik1 + ikonwersji, SEEK_SET);
	char k1[3];
	fread(k1, 1, 3, plikwe);
	char k2[3];
	strncpy(k2, k1, 3);     
	fseek(plikwe, licznik1 , SEEK_SET);  
	int j = strncmp(k1, k2, 3);
	int licznik2 = 0;
	int i = 0;
	unsigned long	ilosc = (long)xres * (long)yres;
	unsigned long licznik_konw = 0;
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
		licznik2++;
		i++;
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
