/*
 * Lab1 Part6
 * By jskyzero 2017/03/26
 * 
 * Part6 is about:
 * USE Index
 *
 */

-- CREATE DataBase 
CREATE DataBase Part6;
-- USE The Part6 DataBase and show some info
USE Part6;

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

-- A lot of INSERT
INSERT INTO student(sid, sname, gpa)
    VALUES
    (15331111, "student1", 2.0),
    (15331112, "student2", 2.6),
    (15331113, "student3", 3.7),
    (15331114, "student4", 4.0),
    (15331115, "student5", 2.5);
-- Also INSERT
INSERT INTO book(bid, bname, user_id, price)
    VALUES
    (00001000, "DBMS 1rd", NULL, 500),
    (00001001, "DBMS 1rd", 15331111, 500),
    (00001002, "DBMS 1rd", 15331113, 500),
    (00002000, "DBMS 2rd", 15331113, 600),
    (00002001, "DBMS 2rd", 15331112, 600),
    (00002002, "DBMS 2rd", 15331113, 600),
    (00003000, "DBMS 3rd", 15331115, 400);

CREATE Index user_id_index ON book(user_id);
SHOW Index FROM book; \G

-- DELETE Table
DROP Table student;
DROP Table book;
-- DELETE The Part6 DataBase
DROP DataBase Part6;
