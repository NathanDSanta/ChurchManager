#include "ErrorHandler.h"
#include <iostream>

void ErrorHandler::showError() const{
  std::cerr << err.getError();
}

