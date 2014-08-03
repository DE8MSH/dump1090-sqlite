#include "dump1090.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void modesFeedSQL(struct modesMessage *mm, struct aircraft *a) {
// code here
sqlite3 *db;
char *zErrMsg = 0;
int rc;
char *sql;
rc = sqlite3_open("basestation.sqb", &db);

if( rc ){
   fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   exit(0);
}
else
{
char msgFlights[1000], *p = msgFlights;

///////////////////////////////////////////////////
/// INSERT into sqlite db
///////////////////////////////////////////////////

/* we flill a live 'flights' table - update old data */
/* DF 0 (Short Air to Air, ACAS has: altitude, icao) */
if (mm->msgtype == 0) {
	sql = sqlite3_mprintf( "INSERT INTO flights (modes, alt, df, msgs) VALUES ('%06X', '%d', '%d', '%ld') ",mm->addr, mm->altitude, mm->msgtype, a->messages);
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "msgtype 0 == OK\n");
   }
}
		}
sqlite3_close(db);
}

