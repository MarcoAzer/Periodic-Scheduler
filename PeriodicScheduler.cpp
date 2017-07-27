#include <iostream>
#include <unistd.h>
#include <thread>

#include "PeriodicScheduler.hpp"
#include "Database.hpp"

const char* PeriodicScheduler::DATABASE_NAME = "TasksResults.db";

static void
writeToDB( const char* databaseName, std::vector< Task > myTasks ){
    Database db( databaseName );
    for( Task& t : myTasks ){
        char tableName[6];
        snprintf( tableName, 6, "Task%d", t.getId() );
        db.createTableIfNotExists( tableName );
        for( double& val : t.getResult() ){
            db.insertRawValue( tableName, val );
        }
    }
}

PeriodicScheduler::PeriodicScheduler(): 
    timer( 0 ),
    running( true )
{

}

unsigned int
PeriodicScheduler::addTask( std::vector< double >(*funcPtr)(), unsigned int interval ){
    Task task( funcPtr, interval );
    task.setArrivalTime( timer );

    unsigned int id = task.getId();
    
    tasks[id] = task;

    return id;
}

void
PeriodicScheduler::scheduleTask( unsigned int id ){
    tasks[id].schedule();
    tasks[id].setArrivalTime( timer );
}

void 
PeriodicScheduler::cancelTask( unsigned int id ){
    tasks[id].cancel();
}

void
PeriodicScheduler::editTask( unsigned int id, unsigned int newInterval ){
    tasks[id].setInterval( newInterval );
    tasks[id].setArrivalTime( timer );
}

void
PeriodicScheduler::start(){
    Status status;
    unsigned int interval;
    unsigned int arrivalTime;
    std::vector< Task > tasksResults;

    while( running ){
        tasksResults.clear();

        //std::cout << "Timer: " << timer << std::endl;
        for( std::unordered_map< unsigned int, Task >::iterator it = tasks.begin(); it != tasks.end(); it++ ){
            Task& t = it->second;
            status = t.getStatus();
            interval = t.getInterval();
            arrivalTime = t.getArrivalTime();

            if( timer != arrivalTime &&
                status == Status::Scheduled && 
                ( ( timer - arrivalTime ) % interval ) == 0 ){
                // Could be an overhead to spin a new thread for each task
                std::vector< double > result = t.run();
                t.setResult( result );
                tasksResults.push_back( t );
            }
        }
        
        if( !tasksResults.empty() ){
            // Write data to db
            std::thread th( writeToDB, DATABASE_NAME, tasksResults );
            th.detach();
        }

        timer += QUANTUM_TIME;
        usleep( QUANTUM_TIME * 1000000 );
    }
}



void
PeriodicScheduler::stop(){
    running = false;
}
