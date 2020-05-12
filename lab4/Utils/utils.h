#ifndef UTILS
#define UTILS

#include "../ProcessorSimulator/Processor.h"
#include "../TasksQueue/TasksQueue.h"

void time_tic ( size_t *t, std::vector<Processor> *ps );
void simulation ( size_t simulation_time, JobStream *stream, size_t processor_amount, TasksQueue *tasks_queue );
std::pair<unsigned, unsigned> good_rand ();

#endif /* end of include guard: UTILS */
