#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <string>
#include <vector>
using namespace std;

class Database {
public:
  Database(string name = "");
  Database(Database &&) = default;
  Database(const Database &) = default;
  Database &operator=(Database &&) = default;
  Database &operator=(const Database &) = default;
  ~Database();

  vector<string> query(string sentence, string type = "SELECT") const;


private:
  sqlite3 *db;

  bool dbExists(const string& database) const;
};

#endif // !DATABASE_H
