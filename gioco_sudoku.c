#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void azzera(int matrice[9][9]);
int antiriga(int i, int j, int matrice[9][9]);
int anticolonna(int i, int j, int matrice[9][9]);
int antiquadrato(int i, int j, int matrice[9][9]);
void genera(int matrice[9][9]);
void crea_puzzle(int q, int stampo_[9][9], int sudoku_[9][9]);
void schema(int sudoku[9][9]);
void salva(int sudoku[9][9]);
void cotrolla(int sudoku[9][9]);
void gioca(int q, int sudoku_[9][9], int def[9][9]);
int carica(int *q, int sudoku_[9][9]);
void riprendi(int q, int sudoku_[9][9]);

main()
{
	int sudoku[9][9], stampo[9][9];
	int sc;
	
	while(1){
		int quantita=0;
		system("cls");
		printf("Sudoku 3x3:\n1. Nuova partita\n2. Carica partita salvata\n3. Esci dal gioco\n\n-¯ ");
		scanf("%d",&sc);
		system("cls");
		switch(sc){
			case 1:
				azzera(stampo);  //azzera(stampo,sudoku);
				azzera(sudoku);
				genera(stampo);
				do{
					system("cls");
					printf("Inserisci la quantit… di valori da avere:\n(min:16 / max:32)-¯ ");
					scanf("%d",&quantita);
				}while(quantita<16 || quantita>32);
				crea_puzzle(quantita,stampo,sudoku);
				gioca(quantita,sudoku,sudoku);
				break;
			
			case 2:
				if(carica(&quantita,sudoku))
				{
					riprendi(quantita,sudoku);
				}
				break;
				
			case 3:
				exit(0);
				break;
			
			default:
				printf("Scelta non valida.\n\n");
				system("pause");
				break;
		}
	}
}

void azzera(int matrice[9][9])  //crea un 9x9 di zeri
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

void genera(int matrice[9][9]) //Genera sudoku
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
			
			if(antiriga(i,j,matrice)==0 || anticolonna(i,j,matrice)==0 || antiquadrato(i,j,matrice)==0) //CONTROLLO ANTI-RIPETIZIONE RIGA E COLONNA E ANTI-QUADRATO
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

void crea_puzzle(int q, int stampo_[9][9], int sudoku_[9][9]) //CREA PUZZLE
{
	int i,x,y;
	
	srand(time(NULL));
	for(i=0; i<q; i++)
	{
		x=(rand() % 9)+1; //coordinata X
		y=(rand() % 9)+1; //coordinata Y
		if(sudoku_[x][y]!=0)
		{
			i--;
			continue;
		}
		sudoku_[x][y]=stampo_[x][y];
	}
	return;
}

void schema(int sudoku[9][9]) //formazione del gioco
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

void salva(int sudoku[9][9]) //salva partita
{
	FILE *save;
	int i,j;
	save=fopen("salvataggio.txt","w");
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			fprintf(save,"%d\n",sudoku[i][j]);
		}
	}
	fclose(save);
	return;
}

void controlla(int sudoku[9][9])
{
	int i,j;
	system("cls");
	printf("Controllo del sudoku in corso...");
	for(i=0; i<9; i++)
	{
		for(j=0; j<9; j++)
		{
			if(antiriga(i,j,sudoku)==0 || anticolonna(i,j,sudoku)==0 || antiquadrato(i,j,sudoku)==0) //CONTROLLO ANTI-RIPETIZIONE RIGA E COLONNA
			{
				printf("\nSudoku non valido:\n\n");
				schema(sudoku);
				printf("\n\n");
				system("pause");
				return;
			}
		}
	}
	printf("\nComplimenti, è corretto!\n\n");
	system("pause");
	return;
}

void gioca(int q, int sudoku_[9][9], int def[9][9]) //gioca
{
	int i,x,y;
	
	for(i=0; i+q<81; i++)
	{
		system("cls");
		printf("Per tornare al men— metti 9-9, la partita si salver… in automatico.\nSudoku 3x3 - completamento %d/81 ~ %.2f%%:\nX:riga - Y:colonna\n\n",(i+q),(float)(i+q)*100/81);
		schema(sudoku_);
		printf("\n\n");
		do{
			printf("Posizione(X-Y)-¯ ");
			scanf("%d-%d",&x,&y);
		}while((x<0 || x>9) || (y<0 || y>9));
		
		if(x==9 && y==9) //torna al menù
		{
			salva(sudoku_);
			printf("\nPartita salvata su 'salvataggio.txt'.\n");
			system("pause");
			return;
		}
		else if(x==9 || y==9) //scelta non valida
		{
			printf("\nSe vuoi tornare indietro metti 9-9, non uno solo.\n");
			i--;
			system("pause");
		}
		else
		{
			if(def[y][x]!=0)
			{
				printf("\nNon puoi rimpiazzare un valore dato dal gioco!\n");
				system("pause");
				i--;
				continue;
			}
			do{
				printf("Valore-¯ ");
				scanf("%d",&sudoku_[y][x]);
			}while(sudoku_[y][x]<1 || sudoku_[y][x]>9);
			printf("\nValore aggiunto correttamente in: %d-%d\n",x,y);
			system("pause");
		}
	}
	controlla(sudoku_);
	return;
}

int carica(int *q, int sudoku_[9][9]) //carica partita
{
	FILE *load;
	int i,j,x;
	
	load=fopen("salvataggio.txt","r");
	if(load==NULL)
	{
		printf("\nNon ci sono partite salvate... Devi iniziarne una nuova.\n\n");
		system("pause");
		return 0;
	}
	else
	{
		for(i=0, j=0, x=0; !feof(load); j++)
		{
			if(j==9)
			{
				i++;
				j=0;
			}
			fscanf(load,"%d",&sudoku_[i][j]);
			if(sudoku_[i][j]!=0)
			{
				x++;
			}
		}
		*q=x;
		printf("\nParita caricata con successo!\n\n");
		system("pause");
	}
	fclose(load);
	return 1;
}

void riprendi(int q, int sudoku_[9][9]) //gioca la partita vecchia
{
	int i,x,y;
	for(i=0; i+q<81; i++)
	{
		system("cls");
		printf("Per tornare al men— metti 9-9, la partita si salver… in automatico.\nSudoku 3x3 - completamento %d/81 ~ %.2f%%:\nX:riga - Y:colonna\n\n",(i+q),(float)(i+q)*100/81);
		schema(sudoku_);
		printf("\n\n");
		do{
			printf("Posizione(X-Y)-¯ ");
			scanf("%d-%d",&x,&y);
		}while((x<0 || x>9) || (y<0 || y>9));
		
		if(x==9 && y==9) //torna al menù
		{
			salva(sudoku_);
			printf("\nPartita salvata su 'salvataggio.txt'.\n");
			system("pause");
			return;
		}
		else if(x==9 || y==9) //scelta non valida
		{
			printf("\nSe vuoi tornare indietro metti 9-9, non uno solo.\n");
			system("pause");
			i--;
		}
		else
		{
			do{
				printf("Valore-¯ ");
				scanf("%d",&sudoku_[y][x]);
			}while(sudoku_[y][x]<1 || sudoku_[y][x]>9);
			printf("\nValore aggiunto correttamente in: %d-%d\n",x,y);
			system("pause");
		}
	}
	controlla(sudoku_);
	return;
}
