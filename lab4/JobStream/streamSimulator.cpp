#include <iostream>

#include "streamSimulator.h"
#include "../Utils/utils.h"

JobStream::JobStream ( unsigned i ) {
    index = 0;
    intensity = i;
}

// returns gap between now and new task comming
unsigned JobStream::get_new_task_time () {
    return good_rand().first % (100 / intensity) + 1;
}

/*
func returns structure (parir) - task
In pair we have two elements, first - index, second - process time
*/
std::pair<unsigned, unsigned> JobStream::new_task () {
    std::pair<unsigned, unsigned> task;
    std::pair<unsigned, unsigned> rand_values = good_rand();
    task.first = index;
    task.second = rand_values.second % 10;
    index++;
    return task;
}
