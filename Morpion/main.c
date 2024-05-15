//
//  main.c
//  Morpion
//
//  Created by abdirahman mohamed on 13.05.2024.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>

//les prototype
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);
void secomdPlayerMove();


//variables globales
char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';
const char PLAYER2 = '#';


int main(int argc, const char * argv[]) {
    char winner = ' ';
    char response = ' ';
    int modeDeJou;
    
    //Demande à l'utilisateur de chosire le mode du jeu et faire une boucle qui redemande si choix invalide.
    printf("Choose.1 (to play with computer) or 2. (two players):?\n");
    scanf("%d", &modeDeJou);
    while (modeDeJou > 2){
        if(modeDeJou == 1){
            printf(":::::Mode With Computer:::::\n");
        }
        else if (modeDeJou == 2){
            printf(":::::Mode 2 Players:::::\n");
        }
        printf("*****INVALIDE NOMBRE*****\n");
        scanf("%d", &modeDeJou);
    }
    
    
   
    do {//play again->cette boucle permet de rejouer le jeu
        winner = ' ';
        response = ' ';
        resetBoard();// reset the board
    
        //tanque winner == ' ' et que  la valeur retourner par checkFreeSpaces() et different de 0! (le jeu continue)
        while (winner == ' ' && checkFreeSpaces() != 0){
           
            printBoard();
            
            playerMove();
            winner = checkWinner();// vérivier le winner-->(^_^)
            if(winner != ' ' || checkFreeSpaces() == 0)//s'il y'a un winner ou egalité--> sortire de la boucle
            {
                break;
            }
            
            if (modeDeJou == 2){//if second chise
                secomdPlayerMove();
                winner = checkWinner();// vérivier le winner-->(^_^)
                if(winner != ' ' || checkFreeSpaces() == 0)//s'il y'a un winner ou egalité--> sortire de la boucle
                {
                    break;
                }
            }
            if (modeDeJou == 1){//si premier choix
                computerMove();
                winner = checkWinner();
                if (winner != ' ' || checkFreeSpaces() == 0){
                    break;
                }
            }
        }
        printBoard();
        printWinner(winner);
        
        
        printf("Voulez vous rejouer?((Y/N)?: ");
        scanf("%s", &response);
        response = toupper(response);
        
        
        } while (response == 'Y');
        printf(":::::::::::GOOD BAY::::::::::\n");
    
    
  
   
    return 0;
}


// vider les cases
void resetBoard()
{//boucler dans toutes les case et insialiser les a ' '-->space vide
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

//-------------------------------------------------------------

//Afficher l'écrent
void printBoard()
{
    printf("\t 1    2    3\n");
    printf("\n\t  %c | %c | %c", board[0][0], board[0][1], board[0][2]);
    printf("\n\t ---|---|---\n");
    printf("\t  %c | %c | %c", board[1][0], board[1][1], board[1][2]);
    printf("\n\t ---|---|---\n");
    printf("\t  %c | %c | %c\n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
    
}
//---------------------------------------------------------------------------------

//vérifier les cases vides et retourner le nombre de case dispo, (0 = accune case n'est dispo!
int checkFreeSpaces()
{
    int freeSpace = 9;
    int i, j;
    
    for(i = 0; i < 3;i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(board[i][j] != ' ')
            {
                freeSpace--;
            }
        }
    }
    
    return freeSpace;
}

//----------------------------------------------------------------

void playerMove()
{
    int x;
    int y;
    
    
    do {// demander l'utilisateur
        
        
        
        printf("Enter row (X) (1-3): ");
        scanf("%d", &x);
        x--;
        printf("Enter Collumn (X) (1-3): ");
        scanf("%d", &y);
        y--;
        
        if(board[x][y] != ' '){  //si la case est prise
            printf("Invalide Mouve\n");
            //playerMove();
        }
        else{
            board[x][y] = PLAYER;
            printBoard();
            break;
        }
 
    } while ((board[x][y] != ' ' && checkFreeSpaces() != 0)); // tanque qu'il ya de la place
  
}

//--------------------------------------------------------------------

char checkWinner()
{//Détécter la gagnant.
    
    // ----------rows ckeck---------
    for(int i = 0; i<3; i++){
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            return board[i][0];
        }
    }
    // ----------collumns ckecks-------------
    for(int i = 0; i<3; i++){
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return board[0][i];
            break;
        }
    }
    
    // -----------diagonale checks--------------
    for(int i = 0; i<3; i++){
        if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
            return board[0][0];
        }
    }
    for(int i = 0; i<3; i++){
        if(board[2][0] == board[1][1] && board[2][0] == board[0][2]){
            return board[2][0];
        }
    }
    return ' ';
    
}

//----------------------------------------------------

void computerMove()
{
    //crée deux nombre aléatoire
    srand((unsigned)time(NULL));
    int x;
    int y;
    
    if(checkFreeSpaces() >0){
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        
        board[x][y] = COMPUTER;
    }
    else{
        printWinner(' ');
        }
}

//----------------------------------------------------------
// Afficher le gangant.
void printWinner(char the_winnwr){
    switch (the_winnwr) {
        case PLAYER:
            printf("[X]:::::::: YOU WIN ::::::::[X]\n");
            break;
        case COMPUTER:
            printf("[O]:::::::: COMPUTERWIN ::::::::[O]\n");
            break;
        case PLAYER2:
            printf("[#]:::::::: PLAYER 2 WINS ::::::::[#]\n");
            break;
        default:
            printf("[==]******EGUALITER******[==]\n");
            break;
    }
}

void secomdPlayerMove(){
    int x;
    int y;

    do {
        printf("PLAYER-2 (#) Entrer un row(1-3)");
        scanf("%d", &x);
        x--;
        printf("PLAYER-2 (#) Entrer une collumn(1-3)");
        scanf("%d", &y);
        y--;
        
        if(board[x][y] != ' '){
            printf("Invalide move!\n");
        }
        else{
            board[x][y] = PLAYER2;
            printBoard();
            break;
        }
    } while (board[x][y] != ' ' && checkFreeSpaces() != 0);
    
}

