#include <iostream>
#include <vector>

#include "Processor.h"

    // setting default time for counter
    Processor::Processor ( unsigned i ) {
        time_left = 0;
        process_index = i;
    }

    // returns true if task is still in process
    bool Processor::is_busy () {
        return time_left != 0;
    }

    // taking task by adding time to our counter
    void Processor::take_task (std::pair<unsigned, unsigned> t) {
        time_left += t.second;
    }

    // function to connect our "time tic's" with process
    void Processor::time_tic_happend () {
        if ( time_left > 0 ) {
            time_left--;
        }
    }
