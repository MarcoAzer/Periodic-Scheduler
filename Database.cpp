#include <iostream>
#include "Database.hpp"

Database::Database( const char* dbName ){
    rc = sqlite3_open( dbName, &db );
    if( rc != SQLITE_OK ){
        std::cerr << "Error with database: " << errMsg << std::endl;
    }
}

Database::~Database(){
    // Assuming no errors in creating db
    // TODO: add check
    sqlite3_close( db );
}

int
Database::executeSQL( int(*callback)( void*, int, char**, char** ) ){
    rc = sqlite3_exec( db, sql, callback, 0, &errMsg );
    if( rc != SQLITE_OK ){
        std::cerr << "Error with database: " << errMsg << std::endl;
        return rc;
    }

    return 0; // Success
}
 
int
Database::createTableIfNotExists( const char* tableName ){
    snprintf( sql, BUFFER_SIZE, "CREATE TABLE IF NOT EXISTS %s (RAW double)", tableName );
    return executeSQL();
}

int
Database::insertRawValue( const char* tableName, double value ){
    snprintf( sql, BUFFER_SIZE, "INSERT INTO %s (RAW) VALUES (%f)", tableName, value );
    return executeSQL();
}
