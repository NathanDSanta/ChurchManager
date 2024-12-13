#include "Error.h"

Error::Error(const string err){
  sError = err;
}

string Error::getError() const{
  return sError;
}
