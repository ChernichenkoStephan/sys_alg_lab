#include <iostream>

#include "Turing_Machine.h"

Turing_Machine::Turing_Machine( std::string t ) {
    /*
    ###01011110011101###
    >>>^
    */
    start_head_index = 0;
    while (t[start_head_index] == '#') {
        start_head_index++;
    }
    current_head_possition = start_head_index;
    tape = t;
}


// ============================ Controll functions  ============================

// Write symbol to line
void Turing_Machine::write_symbol( char c ) { tape[current_head_possition] = c; }

// Read symbol
void Turing_Machine::read_symbol() { current_symbol = tape[current_head_possition]; }

// Move head ritght (increase index)
void Turing_Machine::move_right() { current_head_possition++; }

// Move head left (decrease index)
void Turing_Machine::move_left() { current_head_possition--; }

// ============================ Operation functions ============================

void Turing_Machine::finish_state () {
    std::cout << tape << '\n';
}
