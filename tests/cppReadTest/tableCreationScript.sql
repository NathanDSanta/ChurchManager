CREATE TABLE IF NOT EXISTS person(
id VARCHAR(20) PRIMARY KEY,
name TEXT NOT NULL UNIQUE,
surname TEXT NOT NULL,
gender CHAR(1) CHECK(gender='M' or gender='F'),
birthdate VARCHAR(10) CHECK(birthdate like '____-__-__' and birthdate REGEXP '^[0-9]{4}-[0-9]{2}-[0-9]{2}$'),
address TEXT,
phone INT UNIQUE,
isMember BOOLEAN DEFAULT 0,
memberDate VARCHAR(10) CHECK(birthdate like '____-__-__' and birthdate REGEXP '^[0-9]{4}-[0-9]{2}-[0-9]{2}$'),
familyId VARCHAR(20)
);

CREATE TABLE IF NOT EXISTS family(
  id VARCHAR(20) PRIMARY KEY,
  surname TEXT NOT NULL,
  kidsunder13 INT DEFAULT 0,
  fatherId VARCHAR(20) NOT NULL
);
