#ifndef player_h
#define player_h
#include "carta.h"
#include "caminho.h"
#include "maojogador.h"

#include <stdio.h>
#include <dirent.h>

#include "arte.h"

typedef struct {
  char nome[30];
  int vida, mana, escudo, level; // 200 de vida, 50 de mana, 0 de escudo

} tp_player;

void criarplayer(tp_player *jogador) {
  jogador->vida = 200;
  jogador->mana = 50;
  jogador->escudo = 0;
  jogador->level = 1;
  
}

int playerupdate(tp_player *jogador, char *nome){
  char direc[60] = ".\\data\\player\\";
  strcat(direc, nome);
  strcat(direc, ".dat");

  FILE *update = fopen(direc, "w+");
  if(!update)return 0;

  strcpy(jogador->nome, nome);
  fprintf(update, "%s\n", jogador->nome);
  fprintf(update, "%d %d %d %d\n", jogador->vida, jogador->mana, jogador->escudo, jogador->level);

  fclose(update);

  return 1;
}



int menu(tp_player *jogador) {

  asciiart();
  printf("#####################################################\n"
         "#                                                   #\n" 
         "#                                                   #\n" 
         "#                                                   #\n" 
         "#     1- Novo Jogo 2- Carregar Jogo 3- Encerrar     #\n" 
         "#                                                   #\n" 
         "#                                                   #\n" 
         "#                                                   #\n" 
         "#####################################################\n\n\n");

  int i;
  scanf("%d", &i);

  DIR *saves;
  struct dirent *dir;

  switch (i)
  {
  case 1:
  
  //VERIFICAR SE POSSUI MAIS DE 5 SAVES

    saves = opendir("./data/player/");

    char nome[30];

    printf("Qual será o nome do jogador?\n");
    scanf(" %26[^\n]s", nome);

    char direc[60] = ".\\data\\player\\";
    strcat(direc, nome);

    strcat(direc, ".dat");

    FILE *newgame = fopen(direc, "w");
    if(!newgame)return 0;
    fclose(newgame);

    criarplayer(jogador);

    if(!playerupdate(jogador, nome))printf("Ocorreu algum erro ao atualizar o jogador.\n");

    printf("Bem vindo, %s!\n", jogador->nome);

    return 1;
    break;
  
  case 2:
    
    saves = opendir("./data/player");
    if(!saves)printf("Ocorreu erro ao abrir o diretório dos saves\n");

    int pos = 0;

    printf("#### SAVES ####\n");
    while((dir = readdir(saves)) != NULL){
      if(dir->d_name[strlen(dir->d_name)-1] == 't' && dir->d_name[strlen(dir->d_name)-2] == 'a'){
        char *upname = dir->d_name;
        upname[-3] = '\0';
        printf("%d.: %s\n", pos+1, dir->d_name);
      pos++;
      }
      }



    break;
  default:
    return 0;
  }


}


void imprime_player(tp_player *jogador, tp_listad *carta) {
  printf("============================================\n");
  printf("Nome: %s\n", jogador->nome);
  printf("Vida: %d/200 \n", jogador->vida);
  printf("Mana: %d/50 \n", jogador->mana);
  printf("Escudo: %d/50 \n", jogador->escudo);
  printf("============================================\n\n");

  imprime_listad(carta);
}

int checar_custo(tp_player *jogador, tp_cartas e) {

  if (e.mana > jogador->mana) return 0;
  return 1;
}
#endif
