/*
 * Lab1 Part1
 * By jskyzero 2017/03/26
 * 
 * Part1 is about:
 * create/delete DataBase
 * reate/delete/update Table
 *
 */

-- CREATE DataBase 
CREATE DataBase Part1;

-- USE The Part1 DataBase and show some info
USE Part1;
SHOW Tables;
SHOW DataBases;

-- CREATE A student Table
CREATE Table student(
    sid CHAR(20),
    sname CHAR(20),
    gpa REAL,
    PRIMARY KEY (sid));

INSERT INTO student(sid, sname, gpa)
    VALUES(15331111, "student1", 2.5);

-- SHOW Now All The Table Data
SELECT * 
    FROM student;

-- ALTER Table Properties
ALTER Table student
    ADD gpa2 REAL;

-- SHOW Now All The Table Data
SELECT * 
    FROM student;

-- DELETE The student Table
DROP Table student;
SHOW Tables;

-- DELETE The Part1 DataBase
DROP DataBase Part1;
SHOW DataBases;
