#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

clock_t start, stop;
double czas;

void scramble()
{
	int prim;
	int liczba_odp_notacji[20];
	char ruch;
	char notacje[6] = { 'R', 'U', 'L', 'D', 'F', 'B' };
	srand(time(NULL));
	printf("Scramble: ");
	for (int i = 0; i < 20; i++)
	{
	LOSOWANIE:
		liczba_odp_notacji[i] = rand() % 6;	//losowanie liczby 0-5 odpowiadajacej notacji w tablicy 'notacje'
		if (i > 1)	//ten warunek daje pominiecie kolejnego ifa dla i=0
		{
			if (liczba_odp_notacji[i] == liczba_odp_notacji[i - 1])
				goto LOSOWANIE;
			ruch = notacje[liczba_odp_notacji[i]];	//ruch w postaci literki - element z tablicy 'notacje' o indeksie rownym wartosci przechowywanej w tablicy 'liczba_odp_notacji' o indeksie i
			prim = rand() % 3;	//losowanie 0 lub 2
			printf("%c", ruch);	//jesli 0 to ruch normalny jesli 1 to ruch przeciwny, jesli 2 to ruch podwojny
			if (prim == 0)
				printf(" ");
			else
				if (prim == 1)
					printf("\' ");
				else
					printf("2 ");
		}
	}
	printf("\n");
}

void display_times(double* tab, int rozmiar)
{
	printf("Time list: \n");
	for (int i = 0; i < rozmiar; i++)
	{
		printf("%.3f \n", tab[i]);
	}
	printf("\n");
}

int main(void)
{
	int klawisz;
	int ilosc = 1;
	double* tabela;
	tabela = (double*)malloc(ilosc * sizeof(double));
	printf("Speedcubing timer \n \n");
	printf("Select the cube (press the right button) \n \n ======================\n");
	printf("<1> 3x3x3 OH not\n");
	printf("<2> 2x2x2 not\n");
	printf("<3> 3x3x3 \n");
	printf("<4> 4x4x4 not\n");

START:
	FILE *timelist;
	errno_t err;
	err = fopen_s(&timelist, "timelist.txt", "w+t");
	scramble();
	printf("\n Press Spacebar to start the timer. \n Then press it again to stop the timer \n Press ESC to close the app");
	klawisz = _getch();
	if (tabela == NULL)
	{
		printf("Oops, there is an error. Please close the app and run it again");
		return 0;
	}
	if (klawisz == 27)
	{
		free(tabela);
		return 0;
	}
	if (klawisz == 32)
	{
		start = clock();
		system("cls");
		printf("SOLVE");
		klawisz = _getch();
		if (klawisz)
		{
			stop = clock();
			system("cls");
			czas = (double)(stop - start) / CLOCKS_PER_SEC;
			tabela = (double*)realloc(tabela, (ilosc + 1) * sizeof(double));
			printf("Your time:" "%.3f" "s \n", czas);
			int fputc(int _czas, FILE * _timelist);
			tabela[ilosc - 1] = czas;
			display_times(tabela, ilosc); ilosc++;
			goto START;
		}
	}
	else
	{
		printf("WRONG BUTTON!! \n");
		goto START;
	}
	free(tabela);
	err = fclose(timelist);
	return 0;
}
