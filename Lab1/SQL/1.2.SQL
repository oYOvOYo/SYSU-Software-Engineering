/*
 * Lab1 Part2
 * By jskyzero 2017/03/26
 * 
 * Part2 is about:
 * Quert Table use basic SQL methods
 *
 */

-- CREATE DataBase 
CREATE DataBase Part2;
-- USE The Part2 DataBase and show some info
USE Part2;

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
    VALUES(15331111, "student1", 2.5);
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

-- SHOW name and gpa who gpa > 3
SELECT s.sname, s.gpa 
    FROM student s
    WHERE s.gpa > 3;

-- Select use group
SELECT COUNT(s.sid) as total_num, s.gpa
    FROM student s
    GROUP BY s.gpa;

--  LINK Between student and student
SELECT  s1.sname, s2.sname
    FROM student s1, student s2
    WHERE s1.gpa = s2.gpa and s1.sid != s2.sid;

-- LINK Between student and book
SELECT s.sname, b.bname
    FROM student s, book b
    WHERE s.sid = b.user_id;

-- DELETE Table
DROP Table student;
DROP Table book;
-- DELETE The Part2 DataBase
DROP DataBase Part2;
