#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "sqlite3.h"

class Database{
    static const int BUFFER_SIZE = 128;
    sqlite3* db;
    char* errMsg;
    int rc;
    char sql[BUFFER_SIZE];

    int executeSQL( int(*callback)( void*, int, char**, char** ) = NULL );

  public:
    Database( const char* dbName );
    ~Database();
    int createTableIfNotExists( const char* tableName );
    int insertRawValue( const char* tableName, double value );
};

#endif // DATABASE_HPP
