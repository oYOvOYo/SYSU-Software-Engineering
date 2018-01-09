/*
 * Lab1 Part3
 * By jskyzero 2017/03/26
 * 
 * Part3 is about:
 * Quert Table use SQL and SQL
 *
 */

-- CREATE DataBase 
CREATE DataBase Part3;
-- USE The Part3 DataBase and show some info
USE Part3;

-- CREATE A student Table
CREATE Table student(
    sid CHAR(20),
    sname CHAR(20),
    gpa REAL,
    PRIMARY KEY (sid));

CREATE Table book(
    bid CHAR(20),
    bname CHAR(20),
    user_id CHAR(20),
    price REAL,
    PRIMARY KEY (bid));

INSERT INTO student(sid, sname, gpa)
    VALUES(15331111, "student1", 2.0);
INSERT INTO student(sid, sname, gpa)
    VALUES(15331112, "student2", 2.6);
INSERT INTO student(sid, sname, gpa)
    VALUES(15331113, "student3", 3.7);
INSERT INTO student(sid, sname, gpa)
    VALUES(15331114, "student4", 4.0);
INSERT INTO student(sid, sname, gpa)
    VALUES(15331115, "student5", 2.5);

INSERT INTO book(bid, bname, user_id, price)
    VALUES(00001000, "DBMS 1rd", NULL, 500);
INSERT INTO book(bid, bname, user_id, price)
    VALUES(00001001, "DBMS 1rd", 15331111, 500);
INSERT INTO book(bid, bname, user_id, price)
    VALUES(00001002, "DBMS 1rd", 15331113, 500);
INSERT INTO book(bid, bname, user_id, price)
    VALUES(00002000, "DBMS 2rd", 15331113, 600);
INSERT INTO book(bid, bname, user_id, price)
    VALUES(00002001, "DBMS 2rd", 15331112, 600);
INSERT INTO book(bid, bname, user_id, price)
    VALUES(00002002, "DBMS 2rd", 15331113, 600);
INSERT INTO book(bid, bname, user_id, price)
    VALUES(00003000, "DBMS 3rd", 15331115, 400);

--  SELECT IN SELECT
SELECT s1.sname, s1.gpa
    FROM student s1
    WHERE s1.sid IN ( SELECT s2.sid
                      FROM student s2
                      WHERE s2.gpa > 3 );

-- SELECT UNION SELECT
SELECT s1.sname, s1.gpa
    FROM student s1
    WHERE s1.gpa > 3
UNION
SELECT s2.sname, s2.gpa
    FROM student s2
    WHERE s2.gpa < 2.5;

-- USE EXISTS
SELECT s.sname as who_hava_borrow_book
FROM student s 
WHERE EXISTS ( SELECT * 
               FROM book b
               WHERE b.user_id = s.sid );


-- DELETE Table
DROP Table student;
DROP Table book;
-- DELETE The Part3 DataBase
DROP DataBase Part3;
