#include <stdio.h>
#include "game.h"
#include <conio.h>
int main(void) {


  while(1){
    data_load();
    info(); //Damit werden Menü und highscores gezeigt
    char transaktion;
    scanf(" %c",&transaktion);
    system("clear");

    switch(transaktion){

      case '1': //startet das Spiel
        game();

        break;
      case '2': //schreibt highscores
      	printf("\t\t\t--HIGHSCORES--\n");
        top3();
        printf("Um zum Men� zur�ckzukehren,dr�cken Sie ENTER!");
        getch();

        break;
      case 'q'://beendet das Programm
        goto there;

      default:
        printf("Bitte geben Sie eine der definierten Transaktionen ein.\n");
        break;
    }

  }

  there:
  return 0;
}
