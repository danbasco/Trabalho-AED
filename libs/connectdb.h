#ifndef CONNECTDB_H
#define CONNECTDB_H
#include <stdio.h>
#include <sqlite3.h>


// DATABASE

int connectDB(sqlite3 **db, int *rc){

  *rc = sqlite3_open("./data/cartas.db", db);

  if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return 0;
  }
  return 1;
}

int callback(void *, int, char **, char **);






#endif