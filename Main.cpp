#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include "string.h"
#include "stdlib.h"

#include "PeriodicScheduler.hpp"

using namespace std;

vector< double >
Virtual_Memory(){
	struct sysinfo memInfo;
	sysinfo (&memInfo);

	long long totalVirtualMem = memInfo.totalram;
	totalVirtualMem += memInfo.totalswap;
	totalVirtualMem *= memInfo.mem_unit;
	//cout << "Total Virtual Memory: " << double( totalVirtualMem ) << endl;
    
	long long virtualMemUsed = memInfo.totalram - memInfo.freeram;
	virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
	virtualMemUsed *= memInfo.mem_unit;
	//cout << "Virtual Memory Used: " << double( virtualMemUsed ) << endl;

    vector< double > ret = { double( totalVirtualMem ), double( virtualMemUsed ) };
    return ret;
}

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

vector< double >
Physical_Memory(){
 	FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);

    //cout << "Physical Memory used by proc: " << double( result ) << endl;
	vector< double > ret = { double( result )};
    return ret;
}

int main(){
    PeriodicScheduler scheduler;

    unsigned int id1 = scheduler.addTask( Virtual_Memory, 1 );
    unsigned int id2 = scheduler.addTask( Physical_Memory, 1 );

    thread t( &PeriodicScheduler::start, &scheduler );

    usleep( 5 * 1000000 );

    scheduler.cancelTask( id1 );
    scheduler.cancelTask( id2 );

    usleep( 5 * 1000000 );

    scheduler.editTask( id1, 2 );
    scheduler.scheduleTask( id1 );

    scheduler.editTask( id2, 5 );
    scheduler.scheduleTask( id2 );

    usleep( 10 * 1000000 );
    scheduler.stop();

    t.join();
}

