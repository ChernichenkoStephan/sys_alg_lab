#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <forward_list>

#include "Turing/Turing_Machine.h"
#include "TuringRemoverMachine/TuringRemoverMachine.h"
#include "TuringInverseAndCopyMachine/TuringInverseAndCopyMachine.h"
#include "ProcessorSimulator/Processor.h"
#include "TasksQueue/TasksQueue.h"
#include "JobStream/streamSimulator.h"
#include "Utils/utils.h"



int main(int argc, char const *argv[]) {

    system("clear");

    size_t simulation_time = 100;

    /*

    First simulation:
    Intensity = 10
    Process amount = 1

    */

    JobStream stream = JobStream (10);
    size_t processor_amount = 1;
    TasksQueue tasks_queue = TasksQueue(3);

    std::cout << "----------------- First simulation (one Processor) -----------------" << '\n';

    simulation( simulation_time, &stream, processor_amount, &tasks_queue );

    /*

    Second simulation:
    Intensity = 30
    Process amount = 1

    */

    std::cout << "\n--------- Second simulation (one Processor, hard intensity) ---------" << '\n';

    stream = JobStream (30);
    tasks_queue = TasksQueue(3);

    simulation( simulation_time , &stream, processor_amount, &tasks_queue );

    /*

    Third simulation:
    Intensity = 30
    Process amount = 2

    */

    std::cout << "\n--------- Third simulation (two Processors, hard intensity) ---------" << '\n';

    stream = JobStream (30);
    tasks_queue = TasksQueue(3);
    processor_amount = 2;

    simulation( simulation_time , &stream, processor_amount, &tasks_queue );


    std::cout << "\n--------- Fourth simulation (four Processors, hard intensity) ---------" << '\n';

    stream = JobStream (30);
    tasks_queue = TasksQueue(3);
    processor_amount = 4;

    simulation( simulation_time , &stream, processor_amount, &tasks_queue );




    std::cout << "\n--------- Task 2 Turing Remover Machine ---------" << '\n';

    Turing_Remover_Machine trm = Turing_Remover_Machine("#01011110011110#");
    trm.will_print = false;
    std::cout << "#01011110011110#" << '\n';
    trm.start_state();

    std::cout << "\n--------- Task 3 Turing Inverse And Copy Machine ---------" << '\n';

    Turing_Inverse_And_Copy_Machine tiacm = Turing_Inverse_And_Copy_Machine("#1010#######");
    tiacm.will_print = false;
    std::cout << "#1010#######" << '\n';
    tiacm.start_state();

    return 0;
}
