#ifndef COMBATE_H
#define COMBATE_H
#include <stdio.h>
#include "player.h"
#include "monstro.h"
#include "caminho.h"
#include "maojogador.h"

void usar_carta(tp_cartas cartas_jogador, tp_player *jogador, tp_monstro *monstro) {
  /*
  if (!checar_custo(jogador, cartas_jogador)) {
    printf("Mana insuficiente.\n");
  } else {
*/
    jogador->mana = jogador->mana - cartas_jogador.mana;
    switch (cartas_jogador.tipodacarta) { //SWITCH CASE
    case 0:
      monstro->vida -= cartas_jogador.power;
      break;

    case 1:
      jogador->escudo += cartas_jogador.power;
      break;

    case 2:
      jogador->vida += cartas_jogador.power;
      break;
    default:
      printf("Ocorreu algum erro ao executar o programa.\n tente novamente\n");
      break;
    }


  }
//}


//mecânica do combate
void initcombate(tp_player *player, tp_level *level, tp_listad *c, tp_pilha *baralho, tp_pilha *descarte){
    
    tp_monstro monstro; //monstro E suas ações
    tp_fila fila_monstro;
    tp_cartas carta_jogar;

    inicializa_fila(&fila_monstro);

    if(level->tipo == 0){//SE O LEVEL FOR DE COMBATE -> INICIAR LUTA
        
        criarmonstro(&monstro, level); //Criando o monstro
        criar_acoes_monstro(&fila_monstro);

        while(player->vida > 0 && monstro.vida > 0){ //SE O PLAYER OU O MONSTRO MORRER, A LUTA ACABA
            printar_monstro(monstro, &fila_monstro);
            imprime_player(player, c);
            printf("Digite de 1 a 5 para escolher qual carta vai utilizar.\n\n");
            int i;
            scanf("%d", &i);
            
            carta_jogar = busca_listade(c, i-1);
            printf("Carta Escolhida: %s\n", carta_jogar.nome);
            usar_carta(carta_jogar, player, &monstro); //uso da carta
        
        //ataque monstro




        //descarte da carta (não está funcionando corretamente)
            push(descarte, carta_jogar);
            remove_listad(c, i-1);
            pop(baralho, &carta_jogar);
            insere_listad_no_fim(c, carta_jogar);
            }
            
    }
}

#endif