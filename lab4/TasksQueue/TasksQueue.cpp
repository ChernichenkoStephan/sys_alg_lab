#include <iostream>
#include <queue>

#include "TasksQueue.h"


TasksQueue::TasksQueue( size_t s ) {
    max_size = s;
}

// get top element
std::pair<unsigned, double> TasksQueue::pull_element() {
    std::pair<unsigned, double> res = queue.top();
    queue.pop();
    return res;
}

// returns true if queue is empty
bool TasksQueue::is_empty() {
    return queue.empty();
}

// returns number of elements in queue
size_t TasksQueue::size() {
    return queue.size();
}

// adds element to queue if queue is not loaded
bool TasksQueue::push_element( std::pair<unsigned, double> task ) {
    if (queue.size() < max_size) {
        queue.push(task);
        return true;
    }
    return false;
}

// removes first element from queue
void TasksQueue::remove_first() {
    queue.pop();
}
