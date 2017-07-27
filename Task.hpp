#ifndef TASK_HPP
#define TASK_HPP

#include <vector>

enum Status{
    Scheduled,
    Cancelled
};

class Task{

    /*
     * Number of tasks created.
     * Also, used for task id
     */
    static unsigned int counter;

    /*
     * Unique id of task
     */
    unsigned int id;

    /*
     * Interval for task to run
     */
    unsigned int interval;

    /*
     * Function pointer to the task's job
     */
    std::vector< double >(*funcPtr)();

    /*
     * Results of one function call
     */
    std::vector< double > result;

    /*
     * Status of task, either, scheduled or cancelled
     */
    Status status;

    /*
     * This is used by the scheduler to store the time the task arrived to determine when to run the task.
     */
    unsigned int arrivalTime;

  public:

    Task() = default;

    /*
     * Constructor
     */
    Task( std::vector< double >(*funcPtr)(), unsigned int interval );

    /*
     * Get id of task
     * @return integer of task id
     */
    unsigned int getId() const;

    /*
     * Set the interval of the task to run
     * @param interval new interval for the task
     */
    void setInterval( unsigned int interval );

    /*
     * Get the current interval of the task
     * @return task's interval
     */
    unsigned int getInterval() const;

    /*
     * Set the arrival time of a task
     * @param arrivalTime the scheduler time of when the task arrived to the scheduler
     */
    void setArrivalTime( unsigned int arrivalTime );

    /*
     * Get the arrival time of a task
     * @return the time a task arrived to the scheduler
     */
    unsigned int getArrivalTime() const;

    /*
     * Set results of task
     * @param results new results
     */
    void setResult( std::vector< double >& result );

    /*
     * Get results of task
     * @return results of task
     */
    std::vector< double > getResult();

    /*
     * Change the status of the task to Scheduled
     */
    void schedule();

    /*
     * Change the status of the task to Cancelled
     */
    void cancel();

    /*
     * Get the current status of task
     * @return status of task
     */
    Status getStatus();

    /*
     * Compare two tasks
     * @param task right hand side of the operator
     * @return true if two tasks have the same name and function pointer, false otherwise
     */
    //bool operator==( Task& task );

    /*
     * Print task to output stream
     */
    friend std::ostream& operator<<(std::ostream& out, const Task& t);

    /*
     * Call the function of the task
     */
    std::vector< double > run();

};


#endif // TASK_HPP
