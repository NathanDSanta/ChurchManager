#ifndef PERSON_H
#define PERSON_H

class Person {
public:
  Person();
  Person(Person &&) = default;
  Person(const Person &) = default;
  Person &operator=(Person &&) = default;
  Person &operator=(const Person &) = default;
  ~Person();

private:
  
};

#endif // !PERSON_H
