#ifndef PERIODICSCHEDULER_HPP
#define PERIODICSCHEDULER_HPP

#include <unordered_map>

#include "Task.hpp"

class PeriodicScheduler{
    /*
     * Quantum time in seconds
     * How often we check tasks to run.
     */
    static const int QUANTUM_TIME = 1;

    /*
     * Database name
     */
    static const char* DATABASE_NAME;

    /*
     * Scheduled tasks
     */
    std::unordered_map< unsigned int, Task > tasks;    

    /*
     * Current time of scheduler clock
     */
    unsigned int timer;

    /*
     * Status of scheduler
     * True if running, false otherwise.
     */
    bool running;

  public:

    /*
     * Constructor
     */
    PeriodicScheduler(); 

    /*
     * Create a new copy of task and add it to the scheduler's list of tasks.
     * New copy to allow tasks to run even if it goes out of scope in main program.
     */
    unsigned int addTask( std::vector< double >(*funcPtr)(), unsigned int interval );

    /*
     * Schedule a task that is already in the scheduler's list to run
     * @param task look for matching task in local list
     */
    void scheduleTask( unsigned int id );

    /*
     * Cancels a task so it doesn't run in the future but stays in the scheduler's list of tasks
     * @param task look for matching task in local list
     */
    void cancelTask( unsigned int id );

    /*
     * Edit interval of task 
     * @param task look for matching task in local list
     * @param newInterval new interval of task
     */
    void editTask( unsigned int id, unsigned int newInterval );

    /*
     * Start the timer of the scheduler.
     * Cycle through the list of tasks and run the ready ones by creating a thread for each.
     * @param background if true, run tasks as daemons; detach threads, otherwise, join threads
     */
    void start();

    /*
     * Write results in database
     */
    //static void writeToDB( std::vector< Task >& myTasks );

    /*
     * Change the status of the scheduler to stop running
     */
    void stop();

};

#endif //PERIODICSCHEDULER_HPP
