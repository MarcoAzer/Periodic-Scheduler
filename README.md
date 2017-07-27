# Periodic-Scheduler

## Compile
`make`

## Execute
`./build/main`

## Description
Periodic Scheduler, implemented in C++11, runs tasks every x amount of time based on their interval. Each task returns one or more
decimal numbers which is stored to SQLite database file `TasksResults.db`. Each task write to table Task\<id\> where id is a unique task id.

## Note
`sqlite3.h` and `sqlite3.c` are cloned from https://sqlite.org/download.html
