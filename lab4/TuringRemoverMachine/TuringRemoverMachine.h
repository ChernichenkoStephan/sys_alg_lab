#ifndef TURING_REMOVER_MACHINE
#define TURING_REMOVER_MACHINE

/*
    #01011110011110# =>
=>  #01011110011100#
*/


class Turing_Remover_Machine: Turing_Machine {

public:
    Turing_Remover_Machine ( std::string t ) : Turing_Machine(t) {}

    bool will_print = false;

    // ============================ Operation functions ============================

    void start_state ();

    void first_state ();

    void second_state ();

};

#endif /* end of include guard: TURING_REMOVER_MACHINE */
