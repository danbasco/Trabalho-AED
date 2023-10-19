#ifndef COMBATE_H
#define COMBATE_H
#include <stdio.h>
#include "player.h"
#include "monstro.h"
#include "caminho.h"


void usar_carta(tp_cartas cartas_jogador, tp_player *jogador, tp_monstro *monstro) {

  if (!checar_custo(jogador, cartas_jogador)) {
    printf("Mana insuficiente\n");
  } else {

    jogador->mana = jogador->mana - cartas_jogador.mana;
    switch (cartas_jogador.tipodacarta) {
    case 0:
      monstro->vida -= cartas_jogador.power;
      break;

    case 1:
      /* code */
      break;

    case 2:
      /* code */
      break;
    default:
      break;
    }
  }
}

void combate(tp_player *player, tp_level *level, tp_cartas *c, tp_pilha *baralho){
    
    tp_monstro monstro; //monstro E suas ações
    tp_fila fila_monstro;
    
    inicializa_fila(&fila_monstro);

    if(level->tipo == 0){
        
        criarmonstro(&monstro, level); //Criando o monstro
        criar_acoes_monstro(&fila_monstro);

        printar_monstro(monstro, &fila_monstro);

        while(player->vida > 0 && monstro.vida > 0){
            imprime_player(player, c);
            printf("Digite de 1 a 5 para escolher qual carta vai utilizar.\n\n");
            int i;
            scanf("%d", &i);
            
            usar_carta(c[i-1], player, &monstro);

        }
    }
}

#endif