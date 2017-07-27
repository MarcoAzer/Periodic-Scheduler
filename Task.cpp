#include <iostream>
#include "Task.hpp"

unsigned int Task::counter = 0;

Task::Task( std::vector< double >(*funcPtr)(), unsigned int interval ): 
    interval( interval ),
    funcPtr( funcPtr ),
    status( Scheduled ),
    arrivalTime( 0 )
{
    id = counter;
    counter++;
}

unsigned int
Task::getId() const {
    return id;
}

void
Task::setInterval( unsigned int interval ){
    this->interval = interval;
}

unsigned int
Task::getInterval() const{
    return interval;
}

void
Task::setArrivalTime( unsigned int arrivalTime ){
    this->arrivalTime = arrivalTime;
}

unsigned int
Task::getArrivalTime() const {
    return arrivalTime;
}

void 
Task::setResult( std::vector< double >& result ){
    this->result = result;
}

std::vector< double > 
Task::getResult(){
    return result;
}

std::vector< double >
Task::run(){
    return funcPtr();
}

void
Task::schedule(){
    status = Scheduled;
}

void
Task::cancel(){
    status = Cancelled;
}

Status
Task::getStatus(){
    return status;
}

std::ostream&
operator<<( std::ostream& out, const Task& t ){
    return out << t.id << " Interval: " << t.interval << ", Arrival Time: " << t.arrivalTime << std::endl;
}
