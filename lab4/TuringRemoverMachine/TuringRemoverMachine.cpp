#include <iostream>

#include "../Turing/Turing_Machine.h"
#include "TuringRemoverMachine.h"
// Turing_Remover_Machine ( std::string t ) : Turing_Machine(t) {}

void Turing_Remover_Machine::start_state () {
    move_right();
    first_state();
}

void Turing_Remover_Machine::first_state () {
    read_symbol();
    if (will_print) { std::cout << "first_state, s: " << current_symbol << '\n'; }
    if (current_symbol == '#') {
        move_left();
        second_state();
    } else {
        move_right();
        first_state();
    }
}

void Turing_Remover_Machine::second_state () {
    read_symbol();
    if (will_print) { std::cout << "second_state, s: " << current_symbol << '\n'; }
    if (current_symbol == '1') {
        write_symbol('0');
        finish_state();
    } else {
        move_left();
        second_state();
    }
}
