#include <iostream>
#include <string>
#include "Database.h"
using namespace std;

int main (int argc, char *argv[]) {
  string dbName, select, type;
  cout << "DB: ";
  getline(cin, dbName);

  Database db(dbName);

  cout << "Query: ";
  getline(cin, select);

  while (select != "") {
    cout << "Query type: ";
    getline(cin, type);

    db.query(select, type);
    
    cout << "Query: ";
    getline(cin, select);

  } 

  db.query(select);

  return 0;
}
