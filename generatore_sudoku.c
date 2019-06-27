#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//GENERATORE SUDOKU


void azzera(int matrice[9][9]);
void stampa(int matrice[9][9]);
int antiriga(int i, int j, int matrice[9][9]);
int anticolonna(int i, int j, int matrice[9][9]);
int antiquadrato(int i, int j, int matrice[9][9]);
void genera(int matrice[9][9]);

main()
{
	int sudoku[9][9];
	int sc;
	
	while(1){
		system("cls");
		printf("Scegli un'opzione:\n1. Genera 3x3\n2. Esci\n\n-¯ ");
		scanf("%d",&sc);
		system("cls");
		switch(sc){
			case 1:
				azzera(sudoku);
				genera(sudoku);
				stampa(sudoku);
				break;
			
			case 2:
				exit(0);
				break;
			
			default:
				printf("Scelta non valida.");
				break;
		}
		printf("\n\n");
		system("pause");
	}
}

void azzera(int matrice[9][9]) //crea un 9x9 di zeri
{
	int i,j;
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			matrice[i][j]=0;
		}
	}
	return;
}

void stampa(int matrice[9][9]) //visualizza sudoku
{
	int i,j;
	printf("\n\t   Sudoku 3x3 generato:\n\n\tÚÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿\n");
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			if(j==0)
			{
				printf("\t³ ");
			}
			printf("%d ",matrice[i][j]);
			if((j+1)%3==0)
			{
				printf("³ ");
			}
		}
		if((i+1)%3==0 && i!=8)
		{
			printf("\n\tÃÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´\n");
			continue;
		}
		printf("\n");
	}
	printf("\tÀÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ\n");
	return;
}

int antiriga(int i, int j, int matrice[9][9]) //CONTROLLO ANTI-RIPETIZIONE RIGA
{
	int s;
	for(s=0; s<j; s++)
	{
		if(matrice[i][j] == matrice[i][s])
		{
			return 0;
		}
	}
	return 1;
}

int anticolonna(int i, int j, int matrice[9][9]) //CONTROLLO ANTI-RIPETIZIONE COLONNA
{
	int s;
	for(s=0; s<i; s++)
	{
		if(matrice[i][j] == matrice[s][j])
		{
			return 0;
		}
	}
	return 1;
}

int antiquadrato(int i, int j, int matrice[9][9]) //CONTROLLO ANTI-QUADRATO
{
	int s,c;
	if(i>=i-i%3 && i<3+i-i%3)
	{
		if(j>=j-j%3 && j<3+j-j%3)
		{
			for(s=i-i%3 ; s<3+i-i%3 ; s++)
			{
				for(c=j-j%3 ; c<3+j-j%3 ; c++)
				{		
					if(matrice[i][j]==matrice[s][c] && (s!=i && c!=j))
					{
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

void genera(int matrice[9][9]) //generazione del sudoku
{
	int i,j,c;
	int ripetizione=0;
	
	srand(time(NULL));
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			if(ripetizione>35) //CANCELLA RIGA DOPO TOT RIPETIZIONI
			{
				for(c=0;c<9;c++)
				{
					matrice[i][c]=0;
				}
				i--;
				ripetizione=0;
			}
			matrice[i][j]=(rand() % 9)+1; //GENERAZIONE VALORE
			
			if(antiriga(i,j,matrice)==0 || anticolonna(i,j,matrice)==0 || antiquadrato(i,j,matrice)==0) //CONTROLLO ANTI-RIPETIZIONE RIGA E COLONNA
			{
				ripetizione++;
				j--;
				continue;
			}			
			ripetizione=0;
		}
	}
	return;
}
