#ifndef TASKS_QUEUE_SIM
#define TASKS_QUEUE_SIM

#include <queue>

class TasksQueue {

    std::priority_queue<std::pair<unsigned, unsigned> > queue;
    size_t max_size;

public:

    TasksQueue ( size_t s );

    // get top element
    std::pair<unsigned, double> pull_element ();

    // returns true if queue is empty
    bool is_empty ();

    // returns number of elements in queue
    size_t size ();

    // adds element to queue if queue is not loaded
    bool push_element ( std::pair<unsigned, double> task );

    // removes first element from queue
    void remove_first ();


};

#endif /* end of include guard: TASKS_QUEUE_SIM */
