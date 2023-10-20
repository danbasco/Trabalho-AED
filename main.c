#include "libs/menu.h"
#include <stdio.h>
#include <locale.h>
#include "libs/maojogador.h"
#include "libs/combate.h"


int connectDB(sqlite3 **db){
    int rc;
    rc = sqlite3_open("./data/bongasDB.db", db);

    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Não foi possível abrir a database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return 0;
    }
    return 1;
}

void closeDB(sqlite3 *db){
  sqlite3_close(db);
}

int main() {

    setlocale(LC_ALL,"");
    tp_player player; //Jogador

//LOAD DATA
    sqlite3 *db;
    if (menu(&player)) {
        if(!connectDB(&db))return 0;

    //Deck
        tp_pilha cartas_baralho, cartas_descarte;
        tp_listad *maojogador;
        maojogador = inicializa_listad();

        inicializa_pilha(&cartas_baralho);
        inicializa_pilha(&cartas_descarte);
        criar_cartas(&cartas_baralho, db);



        //imprime_pilha(cartas_baralho);
    //PRIMEIRO LEVEL
        tp_level *levels; //caminho do jogador;

        levels = inicializa_level();
        novolevel(&levels, 1, 0);


    //INICIANDO COMBATE
        initcombate(&player, levels, maojogador, &cartas_baralho, &cartas_descarte);

    }
    closeDB(db);
    return 0;
}
