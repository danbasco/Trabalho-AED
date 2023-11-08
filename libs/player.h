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

void carregarjogador(tp_player *jogador, FILE *arquivo){
  char nome[30];

  fscanf(arquivo, " %[^\n]s", nome);
  strcpy(jogador->nome, nome);

  fscanf(arquivo, "%d %d %d %d", &jogador->vida, &jogador->mana, &jogador->escudo, &jogador->level);

}

int start(tp_player *jogador){
  asciiart();
  menu(jogador);
}


int menu(tp_player *jogador) {


  printf("#####################################################################\n"
         "#                                                                   #\n" 
         "#                                                                   #\n" 
         "#                                                                   #\n" 
         "#     1- Novo Jogo 2- Carregar Jogo 3- Deletar Jogo 4- Encerrar     #\n" 
         "#                                                                   #\n" 
         "#                                                                   #\n" 
         "#                                                                   #\n" 
         "#####################################################################\n\n\n");

  int i, k, pos = 0;

  char names_save[5][30];
  char direc[60] = ".\\data\\player\\";

  scanf("%d", &i);

  DIR *saves;
  struct dirent *dir;

  switch (i)
  {
  case 1:
  
  //VERIFICAR SE POSSUI MAIS DE 5 SAVES
    pos = 0;
    saves = opendir("./data/player/");
    while((dir = readdir(saves)) != NULL){
      if(dir->d_name[strlen(dir->d_name)-1] == 't' && dir->d_name[strlen(dir->d_name)-2] == 'a')pos++;
    }
    if(pos==5){
      printf("Limite Máximo de 5 saves atingido!\n\n\n");
      menu(jogador);
      return 1;
    }
    closedir(saves);

    char nome[30];

    printf("Qual será o nome do jogador?\n");
    scanf(" %26[^\n]s", nome);


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

    pos = 0;
    printf("######### SAVES #########\n");
    k = 0;
    while((dir = readdir(saves)) != NULL){
      
      if(pos == 5)break;

      if(dir->d_name[strlen(dir->d_name)-1] == 't' && dir->d_name[strlen(dir->d_name)-2] == 'a'){

        strcpy(names_save[k], dir->d_name);

        printf("%d.: ", pos+1);
        for(int i=0; i<strlen(dir->d_name)-4; i++)printf("%c", dir->d_name[i]);
        printf("\n\n");
        pos++;
        k++;
        }


    }
    closedir(saves);

    printf("Digite qual save deseja carregar [1/5]\n");
    int load;

    scanf("%d", &load);
    strcat(direc, names_save[load-1]);

    printf("%s\n", direc);

    FILE *carregargame = fopen(direc, "r");;

    if(!carregargame)printf("Ocorreu erro ao abrir o diretório dos saves\n");
    
    carregarjogador(jogador, carregargame);
    printf("Bem vindo, %s!\n", jogador->nome);
    return 1;


  case 3:
     
    saves = opendir("./data/player");
    if(!saves)printf("Ocorreu erro ao abrir o diretório dos saves\n");

    pos = 0;
    printf("#### SAVES ####\n");

    k = 0; 
    while((dir = readdir(saves)) != NULL){
      
      if(pos == 5)break;

      if(dir->d_name[strlen(dir->d_name)-1] == 't' && dir->d_name[strlen(dir->d_name)-2] == 'a'){

        strcpy(names_save[k], dir->d_name);

        printf("%d.: ", pos+1);
        for(int i=0; i<strlen(dir->d_name)-4; i++)printf("%c", dir->d_name[i]);
        printf("\n\n");
        pos++;
        k++;
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
