#include <stdio.h>

#include <string>

#include "app-window.h"
#include "slint.h"
#include "slint_string.h"
#include "sqlite3.h"

auto ui = MainWindow::create();


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  int i;
  slint::SharedString text = "";
  for (i = 0; i < argc; i++) {
    text = (text + "\n" + std::string(azColName[i]) + " = " +
                 (argv[i] ? std::string(argv[i]) : "NULL"));
  }
  text = text + "\n";

  return 0;
}

int query(int argc, char *database, char *sentence) {
  std::string ret;
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  if (argc != 2) {
    ui->set_text("Usage: <program> DATABASE SQL-STATEMENT\n");
    return (1);
  }
  rc = sqlite3_open(database, &db);
  if (rc) {
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return (1);
  }
  rc = sqlite3_exec(db, sentence, callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  sqlite3_close(db);
  return 0;
}

int main(int argc, char **argv) {
  bool fullscreen = true;

  ui->on_fullscreen([&] {
    fullscreen = !fullscreen;
    ui->window().set_fullscreen(fullscreen);
  });

  ui->on_updatePerson([&] {
    ui->set_text("");
    int worked = query(2, "test.db",
                       "update users set name = 'Paul' where id = 'u1987173';");
    if (worked == 0) {
      ui->set_text(ui->get_text() + "Person Updated");
    }
  });

  ui->run();
  return 0;
}
