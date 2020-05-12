#ifndef JOB_STEAM
#define JOB_STEAM

class JobStream {

    unsigned index;
    unsigned intensity; // max value of task process time

public:

    JobStream( unsigned i );

    // returns gap between now and new task comming
    unsigned get_new_task_time();

    /*
    func returns structure (parir) - task
    In pair we have two elements, first - index, second - process time
    */
    std::pair<unsigned, unsigned> new_task();

};

#endif /* end of include guard: JOB_STEAM */
