#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//RISOLUTORE SUDOKU

void azzera(int matrice[9][9]);
void stampa(int matrice[9][9]);
void schema(int sudoku[9][9]);
void assegna(int q, int sudoku_[9][9], int copia_[9][9]);
int antiriga(int i, int j, int matrice[9][9]);
int anticolonna(int i, int j, int matrice[9][9]);
int antiquadrato(int i, int j, int matrice[9][9]);
void risolvi(int sudoku_[9][9],int copia_[9][9]);

main()
{
	int sudoku[9][9], copia[9][9];
	int sc,quantita;
	
	while(1){
		system("cls");
		printf("Scegli un'opzione:\n1. Risolvi 3x3\n2. Esci\n\n-¯ ");
		scanf("%d",&sc);
		system("cls");
		switch(sc){
			case 1:
				azzera(sudoku);
				azzera(copia);
				do{
					system("cls");
					printf("Inserisci la quantit… di valori da avere:\n-¯ ");
					scanf("%d",&quantita);
				}while(quantita<7 || quantita>40);
				assegna(quantita,sudoku,copia);
				system("cls");
				printf("\nAttendi, calcolo in corso...");
				risolvi(sudoku,copia);
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

void stampa(int matrice[9][9]) //visualizza soluzione sudoku
{
	int i,j;
	system("cls");
	printf("\n\tSoluzione del Sudoku:\n\n\tÚÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿\n");
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

void schema(int sudoku[9][9]) //visualizza lo schema
{
	int i,j;
	printf("\t    0 1 2   3 4 5   6 7 8\n");
	printf("\t  ÚÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄÂÄÄÄÄÄÄÄ¿\n");
	for(i=0;i<9;i++)
	{
		printf("\t%d ",i);
		for(j=0;j<9;j++)
		{
			if(j==0)
			{
				printf("³ ");
			}
			printf("%d ",sudoku[i][j]);
			if((j+1)%3==0)
			{
				printf("³ ");
			}
		}
		if((i+1)%3==0 && i!=8)
		{
			printf("\n\t  ÃÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄÅÄÄÄÄÄÄÄ´\n");
			continue;
		}
		printf("\n");
	}
	printf("\t  ÀÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÁÄÄÄÄÄÄÄÙ\n");
	return;
}

void assegna(int q, int sudoku_[9][9], int copia_[9][9])
{
	int i,x,y;
	
	for(i=0; i<q; i++)
	{
		system("cls");
		printf("Inserisci i valori noti: %d/%d\nX:riga - Y:colonna\n\n",i,q);
		schema(sudoku_);
		printf("\n\n");
		do{
			printf("Posizione(X-Y)-¯ ");
			scanf("%d-%d",&x,&y);
		}while((x<0 || x>8) || (y<0 || y>8));
		do{
			printf("Valore-¯ ");
			scanf("%d",&sudoku_[y][x]);
		}while(sudoku_[y][x]<1 || sudoku_[y][x]>9);
		if(copia_[y][x]!=0)
		{
			i--;
		}
		copia_[y][x]=sudoku_[y][x];
	}
	return;
}

int antiriga(int i, int j, int matrice[9][9]) //CONTROLLO ANTI-RIPETIZIONE RIGA
{
	int s;
	for(s=0; s<9; s++)
	{
		if(matrice[i][j] == matrice[i][s] && (s!=j))
		{
			return 0;
		}
	}
	return 1;
}

int anticolonna(int i, int j, int matrice[9][9]) //CONTROLLO ANTI-RIPETIZIONE COLONNA
{
	int s;
	for(s=0; s<9; s++)
	{
		if(matrice[i][j] == matrice[s][j] && (s!=i))
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

void risolvi(int sudoku_[9][9],int copia_[9][9]) //risolutore del sudoku
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
					sudoku_[i][c]=copia_[i][c];
				}
				i--;
				ripetizione=0;
			}
			if(sudoku_[i][j]!=0)
			{
				continue;
			}
			sudoku_[i][j]=(rand() % 9)+1; //GENERAZIONE VALORE
			
			if(antiriga(i,j,sudoku_)==0 || anticolonna(i,j,sudoku_)==0 || antiquadrato(i,j,sudoku_)==0) //CONTROLLO ANTI-RIPETIZIONE RIGA E COLONNA E ANTI-QUADRATO
			{
				ripetizione++;
				sudoku_[i][j--]=0;
				continue;
			}
			ripetizione=0;
		}
	}
	return;
}
