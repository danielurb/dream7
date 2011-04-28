/////////////////////////////////////////////////
// Program kompresuj¥cy pliki graficzne        //
// o formacie *.mtv                            //
/////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(void)
{
	FILE *plikwe, *plikwy;		// wsazniki do plikow
	char tab[9], k1[3], k2[3];  // tablice znakow
	char znak, koniec;
	char *t1, *t2;           	// wskazniki string'ow
	int j, x, y, h;
	int licznik1, ikonwersji;   //licznik pierwszych znakow
	unsigned long i, ilosc, licznik_konw;	//licznik
												//powtarzajacych sie znakow
  int licznik2;

	ikonwersji = 8;
	licznik_konw = 0;

	if((plikwe = fopen("images/fisheye.mtv","r+b"))==NULL)  //otwarcie pliku wej.
	{
		printf("Blad otwarcia pliku wejsciowego !\n");
		return 1;
	}

	if((plikwy = fopen("fisheye.k","w+b"))==NULL)  //otwarcie pliku wyj.
	{
		printf("Blad otwarcia pliku wyjsciowego !\n");
		return 1;
	}

	for(i=0; i<5; i++)
	{
		tab[i] = getc(plikwe);
		if((isdigit(tab[i]))==0)   //sprawdza czy znak jest cyfra
		{
			tab[i]=0;
			break;
		}
	}
	x = atoi(tab);  // x - rozdzielczosc

	for( i=0; i<5; i++)
	{
		tab[i] = getc(plikwe);
		if((isdigit(tab[i]))==0)  //sprawdza czy znak jest cyfra
		{
			tab[i]=0;
			break;
		}
	}
	y = atoi(tab); // y - rozdzielczosc

	fseek(plikwe, 0, SEEK_SET);
	licznik1 = 0;
	while(znak != 10)
	{
		fread(&znak, 1, 1, plikwe);
		fwrite(&znak, 1, 1, plikwy);
		licznik1 = licznik1 + 1;		//licznik pierwszych znakow
	}
//////////////////////////////////////////////////////////////////////////////
	fseek(plikwy, licznik1+ikonwersji, SEEK_SET);	//ust. na zapis pikseli
	fread(k1, 1, 3, plikwe);				// odczytanie pierwszego piksela
	strncpy(k2, k1, 3);                     //i skopiowanie go
	fseek(plikwe, licznik1 , SEEK_SET);     //powt¢rne ustaw. na tym pikselu
	j = strncmp(k1, k2, 3);					//por¢wnanie pikseli (true)
	licznik2 = 0;
	i = 0;
	ilosc = (long)x * (long)y;				//ilo˜† pikseli
	while(i <= ilosc)
	{
		if(i!=ilosc)
		{
			fread(k1, 1, 3, plikwe);
			j = strncmp(k1, k2, 3);
		}
		if(j != 0 || i == (ilosc))  // warunek sprawdzenia tych samych
		{                           //pikseli i zapisu ostatnich pikseli(a)
			fwrite(k2, 1, 3, plikwy);
			if(licznik2 == 0)
			licznik2++;
			fwrite(&licznik2, sizeof(licznik2), 1, plikwy);
			licznik2 = 0;
			strncpy(k2, k1, 3);
			licznik_konw++;         //liczba r¢¾nych pikseli
		}
		licznik2 = licznik2 + 1;	//zliczanie tych samych pikseli
		i = i + 1;
	}

snprintf(tab, 10, "%ld", licznik_konw);

fseek(plikwy, licznik1, SEEK_SET);
for(i=0; i<9; i++)
{
	if(tab[i] != 0)
	{
		fwrite(&tab[i], 1, 1, plikwy); //zapis do pliku wyj. ilo˜† konwersji
	}
	else break;
}
fclose(plikwe);
fclose(plikwy);
return 0;
}
