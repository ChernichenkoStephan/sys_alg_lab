#include <iostream>
// #include <ctime>
// #include <chrono>
// #include <limits.h>
// #include <utility>
#include <vector>

class Turing_Machine {

public:

    Turing_Machine( std::string t ) {
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
    void write_symbol( char c ) { tape[current_head_possition] = c; }

    // Read symbol
    void read_symbol() { current_symbol = tape[current_head_possition]; }

    // Move head ritght (increase index)
    void move_right() { current_head_possition++; }

    // Move head left (decrease index)
    void move_left() { current_head_possition--; }

    // ============================ Operation functions ============================

    void finish_state () {
        std::cout << tape << '\n';
    }

};


/*
    #01011110011110# =>
=>  #01011110011100#
*/
class Turing_Remover_Machine: Turing_Machine {

public:
    Turing_Remover_Machine ( std::string t ) : Turing_Machine(t) {}

    bool will_print = false;

    // ============================ Operation functions ============================

    void start_state () {
        move_right();
        first_state();
    }

    void first_state () {
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

    void second_state () {
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

};

/*
    #0101##### =>
    =>  #0101*#####
    =>  #0101*0####
    =>  #0101*01###
    =>  #0101*010##
    =>  #0101*0101#
=>  #1010*1010#
*/
class Turing_Inverse_And_Copy_Machine: Turing_Machine {

public:
    Turing_Inverse_And_Copy_Machine ( std::string t ) : Turing_Machine(t) {}

    bool will_print = false;

    // ============================ Operation functions ============================

    /*
    start position - go to the end and write '*'
    Preview:  #1010*######
               >>>>^
    */
    void start_state () {
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
    void first_state () {
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
    void second_state () {
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
    void third_state () {
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
    void fourth_state () {
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
    void fifth_state () {
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
    void sixth_state () {
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

};


int main(int argc, char const *argv[]) {

    Turing_Remover_Machine trm = Turing_Remover_Machine("#01011110011110#");
    trm.will_print = false;
    std::cout << "#01011110011110#" << '\n';
    trm.start_state();

    Turing_Inverse_And_Copy_Machine tiacm = Turing_Inverse_And_Copy_Machine("#1010#######");
    tiacm.will_print = false;
    std::cout << "#1010#######" << '\n';
    tiacm.start_state();

    return 0;
}
