/*
 * Lab1 Part4
 * By jskyzero 2017/03/26
 * 
 * Part4 is about:
 * Update Table data
 *
 */

-- CREATE DataBase 
CREATE DataBase Part4;
-- USE The Part4 DataBase and show some info
USE Part4;

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
    VALUES(15331111, "student1", 2.0);
INSERT INTO student(sid, sname, gpa)
    VALUES(15331112, "student2", 2.6);
INSERT INTO student(sid, sname, gpa)
    VALUES(15331113, "student3", 3.7);
INSERT INTO student(sid, sname, gpa)
    VALUES(15331114, "student4", 4.0);
INSERT INTO student(sid, sname, gpa)
    VALUES(15331115, "student5", 2.5);
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

-- SHOW Now All The Table Data
SELECT * 
    FROM student;

-- DELETE 
DELETE FROM student
    WHERE gpa < 2.5;

-- SHOW Now All The Table Data
SELECT * 
    FROM student;

-- Use Update
Update student s
    set s.gpa = s.gpa + 1
    WHERE s.gpa  < 3;

-- SHOW Now All The Table Data
SELECT * 
    FROM student;

-- DELETE Table
DROP Table student;
DROP Table book;
-- DELETE The Part4 DataBase
DROP DataBase Part4;
