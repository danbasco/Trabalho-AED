#include "libs/menu.h"
#include <stdio.h>
#include <locale.h>

int main() {

    setlocale(LC_ALL, "Portuguese");

    tp_player player; //Jogador


    if (menu(&player)) {
        
        tp_monstro monstro; //monstro E suas ações
        tp_fila fila_monstro;

        inicializa_fila(&fila_monstro);

    //Deck
        tp_pilha cartas_baralho;
        tp_cartas cartas_jogador[5];

        inicializa_pilha(&cartas_baralho);

        criar_cartas(&cartas_baralho);
        sacar_deck(&cartas_baralho, cartas_jogador);

        imprime_player(player, cartas_jogador);

        tp_level *levels; //caminho do jogador;

        levels = inicializa_level();


        novolevel(&levels, 1, 0);
        criarmonstro(&monstro, levels); //Criando o monstro

        criar_acoes_monstro(&fila_monstro);
        
        //verificando o monstro
        printar_monstro(monstro, &fila_monstro);
        //verificando todos os ataques possiveis do monstro (debug)
        //imprime_acoes_monstro(fila_monstro);
        checar_custo(&player, cartas_jogador[3]);

    }

    return 0;
}
