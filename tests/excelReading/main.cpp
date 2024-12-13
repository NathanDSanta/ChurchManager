#include "xlnt/xlnt.hpp"
#include <iostream>

using namespace std;

int main (int argc, char *argv[]) {
  xlnt::workbook wb;
  wb.load("example.xlsx");

  auto ws = wb.active_sheet();
  
  for (auto row : ws.rows(false)) {
    for (auto cell : row) {
      cout << cell.to_string() << " ";
    }  
    cout << endl;
  }

  return 0;
}
