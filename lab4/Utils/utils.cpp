#include <iostream>
#include <vector>
#include <forward_list>
#include <cmath>


#include "../TasksQueue/TasksQueue.h"
#include "../ProcessorSimulator/Processor.h"
#include "../JobStream/streamSimulator.h"

#include "utils.h"

std::pair<unsigned, unsigned> good_rand () {

    std::pair<unsigned, unsigned> res;
    double n1, n2;

    while (true) {
        double u1 = static_cast<double>(rand()) / RAND_MAX;
        double u2 = static_cast<double>(rand()) / RAND_MAX;
        double v1 = 2 * u1 - 1;
        double v2 = 2 * u2 - 1;
        double s = v1 * v1 + v2 * v2;
        if (s >= 1)
        continue;
        else {
            n1 = v1 * sqrt((-2 * log(s) / s));
            n2 = v2 * sqrt((-2 * log(s) / s));
            break;
        }
    }

    res.first = static_cast<double>(n1 * n1 * 100000);
    res.second = static_cast<double>(n2 * n2 * 100000);

    return res;
}


void time_tic ( size_t *t, std::vector<Processor> *ps ) {
    (*t)++;
    for (size_t i = 0; i < (*ps).size(); i++) {
        (*ps)[i].time_tic_happend();
    }
}

void simulation ( size_t simulation_time, JobStream *stream, size_t processor_amount, TasksQueue *tasks_queue ) {

    size_t tics = 0;
    size_t tasks_amount = 0;
    size_t denied_amount = 0; // amount of denied tasks
    size_t wait_time = 0; // tasks wait time
    size_t free_process_time = 0; // processor waiting time
    unsigned cumulative_tasks_time = 0; // sum of all tasks times
    std::vector<Processor> processors;

    // Processors initialization
    for (size_t i = 0; i < processor_amount; i++)
        processors.emplace_back(Processor(i));


    std::forward_list<unsigned> denied_tasks_list;

    unsigned next_task_time = stream->get_new_task_time();
    std::pair<unsigned, unsigned> nt;

    while (tics < simulation_time) {

        if (tics == next_task_time) {

            // counting amount of tasks by increasing in every enter
            tasks_amount++;

            // calculating next coming task time
            next_task_time = tics + stream->get_new_task_time();

            // getting new task
            nt = stream->new_task();

            // counting all tasks time
            cumulative_tasks_time += nt.second;

            // trying to add new task to queue, if its full deny
            if (!tasks_queue->push_element(nt)) {
                denied_tasks_list.emplace_front(nt.first);
                denied_amount++;
            }

        }

        // going through processes array to find free one or deny new task
        for (size_t i = 0; i < processor_amount; i++) {
            if (!processors[i].is_busy()) {
                // if there is a task in queue, take it, if no task increasing wait time
                if (!tasks_queue->is_empty()) {
                    processors[i].take_task(tasks_queue->pull_element());
                } else {
                    free_process_time++;
                    break;
                }
            }
        }

        // if queue is still not empty wait time increasing
        if (!tasks_queue->is_empty()) {
            wait_time++;
        }

        // time syncronization function
        time_tic(&tics, &processors);
    }

    std::cout << "Received tasks amount: " << tasks_amount << '\n';
    std::cout << "Tasks waiting time: " << wait_time << '\n';
    std::cout << "Processors avg waiting time: " << free_process_time / processor_amount << '\n';
    std::cout << "Denied tasks amount: " << denied_amount << '\n';
    std::cout << "Average tics in tasks: " << cumulative_tasks_time / tasks_amount << '\n';

}
