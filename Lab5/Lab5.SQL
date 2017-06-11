/*
 * Lab5 Lab5.SQL
 * By jskyzero 2017/06/11
 * 
 * This is a simple SQL use datebase in MySQL to store somo info about picture
 * Because in origin Universal Windows Playform, I use SQLite3, So this is a very simple version
 *
 */

 -- CREATE DataBase 
CREATE DataBase MoePicture;
-- USE The MoePicture DataBase and show some info
USE MoePicture;

set foreign_key_checks=0;

-- CREATE A cache table
CREATE Table cache(
    -- request is store a url, in comman case it will not hava 100 more char
    request     CHAR( 100 ) PRIMARY KEY NOT NULL, 
    -- respose is store a XML string from server, in commen case it will be 100000 char 
    response    TEXT);

-- CREATE　other　table
CREATE Table Users(
    uid     CHAR( 20 ) PRIMARY KEY NOT NULL,
    name    CHAR( 30 ))
    ENGINE=InnoDB;
CREATE Table Pictures(
    pid     CHAR( 20 ) PRIMARY KEY NOT NULL,
    info    TEXT)
    ENGINE=InnoDB;
CREATE Table Tags(
    tag     CHAR( 20 ) PRIMARY KEY NOT NULL);
CREATE Table Likes(
    uid     CHAR( 20 ) NOT NULL,
    pid     CHAR( 20 ) NOT NULL,
    PRIMARY KEY (uid, pid),
    FOREIGN KEY(uid) REFERENCES Users(uid),
    FOREIGN KEY(pid) REFERENCES Pictures(pid))
    ENGINE=InnoDB;
CREATE Table Has(
    pid     CHAR( 20 ),
    tag     CHAR( 20 ),
    PRIMARY KEY (pid, tag),
    FOREIGN KEY(pid) REFERENCES Pictures(pid),
    FOREIGN KEY(tag) REFERENCES Tags(tag));

-- Index
CREATE Index cache_request_index ON cache(request);
CREATE Index Users_uid_request_index ON Users(uid);
CREATE Index Pictures_pid_index ON Pictures(pid);
CREATE Index Tags_tag_index ON Tags(tag);

-- INSERT SOME DATA
INSERT INTO cache(request, response)
    VALUES
    ("https://yande.re/post.xml?limit=100&page=1", 
     "for page 1 bla bla some long long ling message"),
    ("https://yande.re/post.xml?limit=100&page=2", 
     "for page 2 bla bla some long long ling message");

INSERT INTO Users(uid, name)
    VALUES(84832, "jskyzero");
INSERT INTO Pictures(pid, info)
    VALUES
    (12345, "this is pic 12345"),
    (12346, "this is pic 12346"),
    (12347, "this is pic 12347");
INSERT INTO Tags(tag)
    VALUES
    ("wallpaper"),
    ("car"),
    ("anime");
INSERT INTO Likes(uid, pid)
    VALUES
    (84832, 12345),
    (84832, 12346);
INSERT INTO Has(pid, tag)
    VALUES
    (12345, "wallpaper"),
    (12346, "wallpaper"),
    (12347, "car"),
    (12345, "anime");

-- SELECT 
SELECT * 
    FROM cache;
SELECT * 
    FROM Users;
SELECT * 
    FROM Pictures;
SELECT * 
    FROM Tags;
SELECT * 
    FROM Likes;
SELECT * 
    FROM Has;

-- SELECT the request
SELECT c.response
    FROM cache c
    WHERE c.request = "https://yande.re/post.xml?limit=100&page=1";

-- DELETE Table
DROP Table cache;
DROP Table Users;
DROP Table Pictures;
DROP Table Tags;
DROP Table Likes;
DROP Table Has;

-- DELETE The MoePicture DataBase
DROP DataBase MoePicture;