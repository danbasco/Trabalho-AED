#include "libs/menu.h"
#include <stdio.h>
#include <locale.h>

int main() {

    setlocale(LC_ALL,"");
    tp_player player; //Jogador


    if (menu(&player)) {

    //Deck
        tp_pilha cartas_baralho;
        tp_cartas cartas_jogador[5];

        inicializa_pilha(&cartas_baralho);

        criar_cartas(&cartas_baralho);
        sacar_deck(&cartas_baralho, cartas_jogador);

        imprime_cartas(cartas_jogador);

        tp_level *levels; //caminho do jogador;

        levels = inicializa_level();
        novolevel(&levels, 1, 0);
        
        //verificando o monstro
        //verificando todos os ataques possiveis do monstro (debug)
        //imprime_acoes_monstro(fila_monstro);

    }

    return 0;
}
