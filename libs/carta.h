#ifndef CARTA_H
#define CARTA_H
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int connectDB(sqlite3 **db, int *rc){

  *rc = sqlite3_open("./data/cartas.db", db);

  if (*rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return 0;
  }
  return 1;
}

int closeDB(sqlite3 *db){
  sqlite3_close(db);
}


#define MAX 100

typedef struct {
  char nome[30];
  int tipodacarta; // tipo de carta por num (0==ataque , 1==defesa, especial ==
                   // 2)
  int power, mana, level;
} tp_cartas;


// LIB DE PILHA

typedef struct {
  tp_cartas item[MAX];
  int topo;
} tp_pilha;

void inicializa_pilha(tp_pilha *p) { p->topo = -1; }

int pilha_vazia(tp_pilha *p) {
  if (p->topo == -1)
    return 1;
  return 0;
}

int pilha_cheia(tp_pilha *p) {
  if (p->topo == MAX - 1)
    return 1;
  return 0;
}

int push(tp_pilha *p, tp_cartas f) {
  if (pilha_cheia(p))
    return 0;
  p->topo++;
  p->item[p->topo] = f;
  return 1;
}
int pop(tp_pilha *p, tp_cartas *e) {
  if (pilha_vazia(p))
    return 0;
  *e = p->item[p->topo];
  p->topo--;
  return 1;
}

int top(tp_pilha *p, tp_cartas *e) {
  if (pilha_vazia(p))
    return 0;
  *e = p->item[p->topo];
  return 1;
}

int altura_pilha(tp_pilha *p) { return p->topo + 1; }


// cartas do deck

int criar_cartas(tp_pilha *pilha){
 
  sqlite3 *db;
  sqlite3_stmt *stmt;
  int rc;
 //sqlite
  if(!connectDB(&db, &rc))return 0;
  
  tp_cartas cartas[12];


  sqlite3_prepare_v2(db, "SELECT Nome, tipodacarta, power, level, mana FROM cartas", -1, &stmt, 0);
  // cartas de ataque
  int i = 0;
  const unsigned char* name;
  while(sqlite3_step(stmt) != SQLITE_DONE){

    name = sqlite3_column_text(stmt, 0);
    strcpy(cartas[i].nome, name);
    cartas[i].tipodacarta = sqlite3_column_int(stmt, 1);
    cartas[i].power = sqlite3_column_int(stmt, 2);
    cartas[i].level = sqlite3_column_int(stmt, 3);
    cartas[i].mana = sqlite3_column_int(stmt, 4);
    i++;
  }

  // Função preencher pilha:
  srand(time(NULL));
  for (int i = 0; i < 10; i++) { // shuffle array
    int random = rand() % 11;
    push(pilha, cartas[random]);
  }
  closeDB(db);
  return 1;
}

#endif