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
  switch (i)
  {
  case 1:
    
    char nome[30];

    printf("Qual será o nome do jogador?\n");
    scanf(" %26[^\n]s", nome);
    printf("nome - %s\n", nome);

    char dir[60] = "./data/player/";
    strcpy(dir, nome);
    strcpy(dir, ".dat");
    
    FILE *newgame = fopen(dir, "w");
    if(!newgame){
      printf("erro ao criar arquivo")
    }

    criarplayer(jogador);

    return 1;
    break;
  
  case 2:
    





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
