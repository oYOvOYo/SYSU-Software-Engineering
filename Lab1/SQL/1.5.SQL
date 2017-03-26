/*
 * Lab1 Part5
 * By jskyzero 2017/03/26
 * 
 * Part5 is about:
 * Create and Use View
 *
 */

-- CREATE DataBase 
CREATE DataBase Part5;
-- USE The Part5 DataBase and show some info
USE Part5;

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

-- CREATE View student and book
CREATE View student_borrow_book as 
SELECT s.sname, b.bname
    FROM student s, book b
    WHERE s.sid = b.user_id AND b.price > 500;

-- CREATE View student and book
CREATE View student_borrow_book_with as 
SELECT s.sname, b.bname
    FROM student s, book b
    WHERE s.sid = b.user_id AND b.price > 500 WITH CHECK OPTION;

SELECT * FROM student_borrow_book;
SELECT * FROM student_borrow_book_with;

INSERT INTO book(bid, bname, user_id, price)
    VALUES(00003001, "DBMS 3rd", 15331114, 400);

SELECT * FROM student_borrow_book;
SELECT * FROM student_borrow_book_with;

--WILL ERROR Can not modify more than one base table through a join view 'part5.student_borrow_book'
INSERT INTO student_borrow_book(sname, bname)
    VALUES("New student", "New book");
INSERT INTO student_borrow_book_with(sname, bname)
    VALUES("New student", "New book");

CREATE View student_view as 
SELECT s.sid, s.gpa
    FROM student s
    WHERE s.gpa > 3;

CREATE View student_view_with as 
SELECT s.sid, s.gpa
    FROM student s
    WHERE s.gpa > 3 WITH CHECK OPTION;

SELECT * FROM student_view;
SELECT * FROM student_view_with;

INSERT INTO student_view VALUES("New student1", "2.5");
INSERT INTO student_view_with VALUES("New student2", "2.5");

SELECT * FROM student_view;
SELECT * FROM student_view_with;
SELECT * FROM student;

INSERT INTO student_view VALUES("New student3", "3.5");
INSERT INTO student_view_with VALUES("New student4", "3.5");

SELECT * FROM student_view;
SELECT * FROM student_view_with;
SELECT * FROM student;

-- DELETE Table
DROP Table student;
DROP Table book;
-- DELETE The Part5 DataBase
DROP DataBase Part5;
