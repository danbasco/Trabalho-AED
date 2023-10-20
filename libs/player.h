#ifndef player_h
#define player_h
#include "carta.h"
#include "caminho.h"
#include "maojogador.h"
#include <stdio.h>

typedef struct {
  char nome[50];
  int vida, mana, escudo, level; // 200 de vida, 50 de mana, 0 de escudo

} tp_player;

void criarplayer(tp_player *jogador) {
  jogador->vida = 200;
  jogador->mana = 50;
  jogador->escudo = 0;
  jogador->level = 1;
  
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
