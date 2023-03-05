#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>

struct highscores { // eine Struct zum Speichern von Highscores
  char name[20];
  int score;
  int grad;
};
struct highscores user[3]; // 3 highscores

void data_load() { // daten lesen
  FILE *rptr;
  rptr = fopen("highscores.txt", "r");
	int i;
  for (i = 0; i < 3; i++) {
    fscanf(rptr, "%d %s %d", &user[i].grad, user[i].name, &user[i].score);
    printf("\n");
  }
  fclose(rptr);
}

void data_update() {
  remove("highscores.txt");

  FILE *fptr;
  fptr = fopen("highscores.txt", "w+");
	int i;
  for (i = 0; i < 3; i++) {
    fprintf(fptr, "%d %s %d\n", user[i].grad, user[i].name, user[i].score);
  }
  fflush(fptr);
}

// je nach Punkten von Spielern wird hier ihr Rang gespeichert.
void speichern_highscore(char name[20], int *score, int *grad) {

  if (user[*grad - 1].score == 0 || *grad == 3) {

    strcpy(user[*grad - 1].name, name);
    user[*grad - 1].score = *score;

  } else {

    int i = *grad - 1;
    if (i == 0) {
      char altName[20];
      char altName2[20];
      int *altScore;
      altScore = &user[i].score;
      int *altScore2 = &user[i + 1].score;
      strcpy(altName, user[i].name);
      strcpy(altName2, user[i + 1].name);

      strcpy(user[i + 2].name, altName2);
      user[i + 2].score = *altScore2;

      user[i + 1].score = *altScore;
      strcpy(user[i + 1].name, altName);

      user[i].score = *score;
      strcpy(user[i].name, name);

    } else if (i == 1) {

      char altName[20];

      int *altScore;

      strcpy(altName, user[i].name);
      altScore = &user[i].score;

      strcpy(user[i + 1].name, altName);
      user[i + 1].score = *altScore;

      user[i].score = *score;
      strcpy(user[i].name, name);
    }
  }
}

int prufung_highscore(int score) {
  // es wird Ã¼berprÃ¼ft,ob ein Spieler eine neue Rekord bricht.
  int i;
  for (i = 0; i < 3; i++) {
    if (score > user[i].score) {
      return i + 1;
    }
  }
  return 0;
}

//**********************************************************
void game() {

  int rund = 1;
  int programm = 1;
  int score = 0;
  int zeit = 1;
  int *zahllist = (int *)malloc(rund * sizeof(int *));

  while (programm) {
  	system("clear");
    clock_t anfang, ende;

    zahllist = (int*)realloc(zahllist,rund*sizeof(int*));
    //realloc fÃ¼gt keine Anzahl von Elementen von Array hinzu,sondern definiert fÃ¼r Array die neue Breite
    int *zahlen = (int *)malloc(rund * sizeof(int *));

    // zufÃ¤llige Zahlen erstellen

    time_t random;
    srand((unsigned)time(&random));

    //for (int i = 0; i < rund; i++) {
      int num = rand();

      zahllist[rund-1] = num % 5 != 0 ? num % 5 : 1;
    //}

    // hier wird belibige Zahlen und Zeit zu Benutzern gezeigt.
    printf("Runde #%d :", rund);
    int i;
    for (i = 0; i < rund; i++) {
      printf(" %d", zahllist[i]);
    }

     printf(" -> Zahlen wird nach %d Sekunde ausgeblendet.\n", zeit);
    if(rund<5){
    printf("\nSie haben 3 Sekunden, um sich die Zahlen einzuprägen. Nach 3 Sekunden werden Sie Ihre Antwort eingeben.\n");
    sleep(3);

	}else{
		printf("\nSie haben %d Sekunden, um sich die Zahlen einzuprägen. Nach %d Sekunden werden Sie Ihre Antwort eingeben.\n",rund,rund);
		sleep(rund);
	}
	system("clear");
	printf("\nBitte geben Sie jetzt Ihre Antwort ein: \n");
    //// input
    for (i = 0; i < rund; i++) {

      scanf(" %d", &zahlen[i]);
    }
    for (i = 0; i < rund; i++) {

      if (zahlen[i] != zahllist[i]) {
        printf("Falsch!\n");
        free(zahllist);
        programm = 0;
        int grad = prufung_highscore(score);
        if (grad > 0) {

          char name[20];
          printf("Aber Sie haben Highscore, geben Sie Ihren Namen ein: ");
          scanf("%s", name);

          speichern_highscore(name, &score, &grad);
          data_update();
          printf("Um zum Menü zurückzukehren,drücken Sie ENTER!");
          getch();

          goto hierhin;
        } else {
        	printf("Um zum Menü zurückzukehren,drücken Sie ENTER!");
			getch();

          goto hierhin;
        }
      }
    }
    printf("Richtig!\n");
    rund++;
    zeit++;
    score++;
    // printf("\nsayÄ± : %d\n",zahllist[0]);

  hierhin:

    //free(zahllist);
    free(zahlen);
  }
}

void top3() { //
	int i;
  for (i = 0; i < 3; i++) {
    printf("%d. Name : %s Punkt : %d\n", i + 1, user[i].name, user[i].score);
  }
}

void info() { //
	system("clear");
  if (user[0].score == 0) {
    printf("TAU SAYS \t\t\tHighscore: nicht vorhanden\n1) "
           "Spielen\n2)Highscores\nq:Beenden\n");
  } else {
    printf("TAU SAYS \t\t\tHighscore: %s (%d Runde)\n1) "
           "Spielen\n2)Highscores\nq:Beenden\n",
           user[0].name, user[0].score);
  }
}
