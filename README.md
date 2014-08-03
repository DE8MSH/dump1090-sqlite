dump1090-sqlite README
===

Intro
---

This sqlite version based on dump1090 by Lee Smallbone, that uses mysql a database service. See http://lee.smallbone.com/2014/03/ads-b_via_dvb-t.

If option --sql is used dump1090 writes data into a database named basestation.sqb. You can find basestation.sqb on several sites in internet. Some of them containing data like type of plane, registration etc. If you're a Planeplotter user you know what I'm talking about.

Why sqlite? IMHO I think that sqlite is not so bloated like mysql server. And I think it's better in usage. And you don't have to convert basestation.sqb into mysql db. That's a big advantage if you're planning to select plane data like type of plane etc.

Installation
---
* cd ~
* sudo apt-get install sqlite3 libsqlite3-dev -y
* git clone https://github.com/DE8MSH/dump1090-sqlite.git
* cd dump1090-sqlite
* wget basestation.sqb from anywhere
* cat create_tables.sql | sqlite3 basestation.sqb 
* make
* ./dump1090 --sql

RPi?
---
Yes. Raspian.

Other soc?
---
Maybe

Usefull tools
---
* SQLiteStudio http://sqlitestudio.pl
* https://www.youtube.com/watch?v=9uUN6o4YydE
* https://www.youtube.com/watch?v=IdzlO3YwoO4

