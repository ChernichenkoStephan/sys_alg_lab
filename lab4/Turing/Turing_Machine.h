#ifndef TURING_MACHINE
#define TURING_MACHINE

class Turing_Machine {

public:

    Turing_Machine( std::string t );

protected:

    // Tape
    std::string tape;
    // Heads index
    int start_head_index;
    // Current head possition
    int current_head_possition;
    // Read symbol
    char current_symbol;

    // ============================ Controll functions  ============================

    // Write symbol to line
    void write_symbol( char c );

    // Read symbol
    void read_symbol();

    // Move head ritght (increase index)
    void move_right();

    // Move head left (decrease index)
    void move_left();

    // ============================ Operation functions ============================

    void finish_state ();

};

#endif /* end of include guard: TURING_MACHINE */
