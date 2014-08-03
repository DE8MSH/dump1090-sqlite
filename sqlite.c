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

/* DF 4/20 (Surveillance (roll call) Altitude has: altitude, icao, flight status, DR, UM) */
/* TODO flight status, DR, UM */
/*
if (mm->msgtype == 4 || mm->msgtype == 20){

sql = sqlite3_mprintf( "INSERT INTO flights (modes, alt, df, msgs) VALUES ('%06X', '%d', '%d', '%ld')",mm->addr, a->altitude, mm->msgtype, a->messages);
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "msgtype 4/20 == OK\n");
   }
}
*/

    /* DF 5/21 (Surveillance (roll call) IDENT Reply, has: alt, icao, flight status, DR, UM, squawk) */
/*  
  if (mm->msgtype == 5 || mm->msgtype == 21) {
sql = sqlite3_mprintf( "INSERT INTO flights (modes, alt, squawk, df, msgs) VALUES ('%06X', '%d', '%d', '%d', '%ld')",mm->addr, mm->altitude, mm->modeA, mm->msgtype, a->messages);
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "msgtype 5/21 == OK\n");
   }
}
*/
 /* DF 11 */
/*
if (mm->msgtype == 11) {

sql = sqlite3_mprintf( "INSERT INTO flights (modes, df, msgs) VALUES ('%06X', '%d', '%ld')",mm->addr, mm->msgtype, a->messages);
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "msgtype 11 == OK\n");
   }
}
*/
    /* DF17 *with or without position data */
/*  
  if (mm->msgtype == 17) {
sql = sqlite3_mprintf( "INSERT INTO flights (df, flight, airline, modes, alt, vr, lat, lon, speed, heading, msgs) VALUES ('%d', '%s', '%3s', '%06X', '%d', '%d', '%1.5f', '%1.5f', '%d', '%d', '%ld')",mm->msgtype, a->flight, a->flight, mm->addr, mm->altitude, mm->vert_rate, a->lat, a->lon, a->speed, a->track, a->messages);
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
  if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "msgtype 17 == OK\n");
   }
}
*/
/////////////////////////
}
sqlite3_close(db);
}

