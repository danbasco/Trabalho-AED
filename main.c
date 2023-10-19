#include "libs/menu.h"
#include <stdio.h>
#include <locale.h>

int main() {

    setlocale(LC_ALL,"");
    tp_player player; //Jogador


    if (menu(&player)) {

    //Deck
        tp_pilha cartas_baralho, cartas_descarte;
        tp_listad *maojogador;
        maojogador = inicializa_listad();

        inicializa_pilha(&cartas_baralho);
        inicializa_pilha(&cartas_descarte);
        criar_cartas(&cartas_baralho);
        sacar_deck(&cartas_baralho, maojogador);

        tp_level *levels; //caminho do jogador;

        levels = inicializa_level();
        novolevel(&levels, 1, 0);
        
        //verificando o monstro
        //verificando todos os ataques possiveis do monstro (debug)
        //imprime_acoes_monstro(fila_monstro);

    }

    return 0;
}
