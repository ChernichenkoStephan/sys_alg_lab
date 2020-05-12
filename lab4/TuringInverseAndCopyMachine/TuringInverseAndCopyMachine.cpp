#include <iostream>

#include "../Turing/Turing_Machine.h"
#include "TuringInverseAndCopyMachine.h"

/*
#0101##### =>
=>  #0101*#####
=>  #0101*0####
=>  #0101*01###
=>  #0101*010##
=>  #0101*0101#
=>  #1010*1010#
*/

// Turing_Inverse_And_Copy_Machine ( std::string t ) : Turing_Machine(t) {}


// ============================ Operation functions ============================

/*
start position - go to the end and write '*'
Preview:  #1010*######
>>>>^
*/
void Turing_Inverse_And_Copy_Machine::start_state () {
    read_symbol();
    if (will_print) { std::cout << "start_state, s: " << current_symbol << '\n'; }
    switch (current_symbol) {
        case '#':
        write_symbol('*');
        move_left();
        first_state();
        break;

        default:
        move_right();
        start_state();
        break;
    }
}

/*
Move back, then step back and perform second state
Preview:  #1010*######
>^<<<<
*/
void Turing_Inverse_And_Copy_Machine::first_state () {
    read_symbol();
    if (will_print) { std::cout << "first_state, s: " << current_symbol << '\n'; }
    switch (current_symbol) {
        case '#':
        move_right();
        second_state();
        break;

        case 'a':
        move_right();
        second_state();
        break;

        case 'b':
        move_right();
        second_state();
        break;

        default:
        move_left();
        first_state();
        break;
    }
}

/*
Marking old symbols, checking if we finished and performing append states
Preview:  #b010*######
^
*/
void Turing_Inverse_And_Copy_Machine::second_state () {
    read_symbol();
    if (will_print) { std::cout << "second_state, s: " << current_symbol << " tape: " << tape << '\n'; }
    switch (current_symbol) {
        case '0':
        write_symbol('a');
        third_state();
        break;

        case '1':
        write_symbol('b');
        fourth_state();
        break;

        default:
        fifth_state();
        break;
    }
}

/*
Marking old symbols, and append states
Preview:  #ba10*10####
>>>>>>^
*/
void Turing_Inverse_And_Copy_Machine::third_state () {
    read_symbol();
    if (will_print) { std::cout << "third_state, s: " << current_symbol << '\n'; }
    switch (current_symbol) {
        case '#':
        write_symbol('0');
        first_state();
        break;

        default:
        move_right();
        third_state();
        break;
    }
}

/*
Marking old symbols, and append states
Preview:  #b010*1#####
>>>>>>^
*/
void Turing_Inverse_And_Copy_Machine::fourth_state () {
    read_symbol();
    if (will_print) { std::cout << "fourth_state, s: " << current_symbol << '\n'; }
    switch (current_symbol) {
        case '#':
        write_symbol('1');
        first_state();
        break;

        default:
        move_right();
        fourth_state();
        break;
    }
}

/*
Going to start position
Preview:  #baba*1010#####
^<<<<<<<<<
*/
void Turing_Inverse_And_Copy_Machine::fifth_state () {
    read_symbol();
    if (will_print) { std::cout << "fifth_state, s: " << current_symbol << '\n'; }
    switch (current_symbol) {
        case '#':
        move_right();
        sixth_state();
        break;

        default:
        move_left();
        fifth_state();
        break;
    }
}

/*
Replacing 'a' and 'b', and inverting the copy
Preview:  #baba*1010##### =>
=> #0101*0101#####
>>>>>>>>>>^
*/
void Turing_Inverse_And_Copy_Machine::sixth_state () {
    read_symbol();
    if (will_print) { std::cout << "sixth_state, s: " << current_symbol << '\n'; }
    switch (current_symbol) {
        case '#':
        finish_state();
        break;

        case 'a':
        write_symbol('1');
        move_right();
        sixth_state();
        break;

        case 'b':
        write_symbol('0');
        move_right();
        sixth_state();
        break;

        case '1':
        write_symbol('0');
        move_right();
        sixth_state();
        break;

        case '0':
        write_symbol('1');
        move_right();
        sixth_state();
        break;

        default:
        move_right();
        sixth_state();
        break;
    }
}
