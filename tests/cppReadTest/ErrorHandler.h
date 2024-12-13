#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H


#include "Error.h"
class ErrorHandler {
public:
  ErrorHandler() {};
  ErrorHandler(ErrorHandler &&) = default;
  ErrorHandler(const ErrorHandler &) = default;
  ErrorHandler &operator=(ErrorHandler &&) = default;
  ErrorHandler &operator=(const ErrorHandler &) = default;

  void showError() const;

private:
  Error err;
  
};
#endif // !ERRORHANDLER_H
