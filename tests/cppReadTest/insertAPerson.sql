INSERT INTO Person (
  id,
  name,
  surname,
  gender,
  birthdate, 
  address,
  phone,
  isMember,
  memberDate,
  familyId
) VALUES ( 
  '1234',
  'Viorel',
  'Santa',
  'M',
  '1967-06-19',
  'Porqueres',
  627379298,
  1,
  '2020-01-01',
  'SantVio'
);

select p.familyId, f.surname, count(*) as 'integranti'
from person p join family f on p.familyId = f.id
where (strftime('%Y', date('now')) - strftime('%Y', birthdate) > 13)
group by p.familyId, f.surname;
