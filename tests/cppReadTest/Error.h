#ifndef ERROR_H
#define ERROR_H
#include <string>
using namespace std;

class Error {
public:
  Error(const string err = "");
  Error(Error &&) = default;
  Error(const Error &) = default;
  Error &operator=(Error &&) = default;
  Error &operator=(const Error &) = default;
  string getError() const;

private :
  string sError;
};

#endif // !ERROR_H
