#include <stdio.h>

#include <string>

#include "app-window.h"
#include "sqlite3.h"
#include "xlnt/xlnt.hpp"

auto ui = MainWindow::create();

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;
  for (i = 0; i < argc; i++) {
    ui->set_text( ui->get_text() + "\n" + std::string(azColName[i]) + " = " + (argv[i] ? std::string(argv[i]) : "NULL"));
  }
  ui->set_text( ui->get_text() + "\n");
  return 0;
}

int query(int argc, std::string database, std::string sentence) {
  std::string ret;
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;


  if (argc != 2) {
    ui->set_text("Usage: <program> DATABASE SQL-STATEMENT\n");
    return (1);
  }
  rc = sqlite3_open(database.data(), &db);
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return (1);
  }
  rc = sqlite3_exec(db, sentence.data(), callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
  return 0;
}

int main(int argc, char **argv) {
  bool fullscreen = true;
  bool darkmode = false;
  ui->window().set_fullscreen(fullscreen);
  ui->set_DarkMode(darkmode);

  ui->on_switchDarkMode([&]{
    darkmode = !darkmode; 
    ui->set_DarkMode(darkmode);
  });

  ui->on_fullScreen([&] {
    fullscreen = !fullscreen;
    ui->window().set_fullscreen(fullscreen);
  });


  ui->on_selectAll([&]{
    std::string database = "test.db";
    std::string qry = "select * from users;";
    ui->set_text("");
    int works = query(2, database, qry);
  });

  ui->on_updatePerson([&]{
    std::string database = "test.db";
    std::string qry = "update users set name = 'Paul' where id = 'u1987173';";
    ui->set_text("");
    int worked = query(2, database, qry);
    if (worked == 0) {
      ui->set_text(ui->get_text() + "Person Updated");
    }
   });

  ui->run();
  return 0;
}
