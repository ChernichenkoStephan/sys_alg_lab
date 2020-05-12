#ifndef PROCESSOR_SIM
#define PROCESSOR_SIM

class Processor {

    unsigned time_left;
    unsigned process_index;

public:

    // setting default time for counter
    Processor( unsigned i );

    // returns true if task is still in process
    bool is_busy();

    // taking task by adding time to our counter
    void take_task(std::pair<unsigned, unsigned> t);

    // function to connect our "time tic's" with process
    void time_tic_happend();

};

#endif /* end of include guard: PROCESSOR_SIM */
