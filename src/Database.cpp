#include "Database.h"
#include "Error.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

Database::Database(string dbName){
  try {
    if (!dbExists(dbName)) throw Error("Database " + dbName + " doesn't exist");

    int rc = sqlite3_open(dbName.data(), &db);
    if(rc){
      sqlite3_close(db);
      throw Error("Can't open database: %s/n" + std::string(sqlite3_errmsg(db)));
    }
  } catch (const Error& err) {
    std::cerr << err.getError() << endl;
  }
}

//prepare, step, column, finalize

vector<string> Database::query(string sentence, string type) const{
  int rt = 0;
  vector<string> ret;
  try {
    sqlite3_stmt* prQuery;

    rt = sqlite3_prepare_v2(db, sentence.data(), -1, &prQuery, 0);
    if (rt != SQLITE_OK) {
      throw Error("Failed to prepare statement: " + std::string(sqlite3_errmsg(db)));
    }

    while (sqlite3_step(prQuery) == SQLITE_ROW) {
      std::cout << "C1 => " << sqlite3_column_text(prQuery,0) << endl;
      std::cout << "C2 => " << sqlite3_column_text(prQuery,1) << endl;
      std::cout << "C3 => " << sqlite3_column_text(prQuery,2) << endl;
      std::cout << "C4 => " << sqlite3_column_int(prQuery,3) << endl;
      cout << endl;
    }

    sqlite3_finalize(prQuery);

  } catch (const Error& err) {
    std::cerr << err.getError() << endl; 
  }
  return ret;
}

bool Database::dbExists(const string& database) const{
  ifstream db(database.c_str());
  return db.good();
}


Database::~Database(){
  sqlite3_close(db);
}
