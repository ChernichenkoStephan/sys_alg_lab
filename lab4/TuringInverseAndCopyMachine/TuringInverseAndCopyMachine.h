#ifndef TURING_INVERSE_AND_COPY_MACHINE
#define TURING_INVERSE_AND_COPY_MACHINE

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
    void start_state ();

    /*
    Move back, then step back and perform second state
    Preview:  #1010*######
              >^<<<<
    */
    void first_state ();

    /*
    Marking old symbols, checking if we finished and performing append states
    Preview:  #b010*######
               ^
    */
    void second_state ();

    /*
    Marking old symbols, and append states
    Preview:  #ba10*10####
               >>>>>>^
    */
    void third_state ();

    /*
    Marking old symbols, and append states
    Preview:  #b010*1#####
              >>>>>>^
    */
    void fourth_state ();

    /*
    Going to start position
    Preview:  #baba*1010#####
              ^<<<<<<<<<
    */
    void fifth_state ();

    /*
    Replacing 'a' and 'b', and inverting the copy
    Preview:  #baba*1010##### =>
           => #0101*0101#####
              >>>>>>>>>>^
    */
    void sixth_state ();

};

#endif /* end of include guard: TURING_INVERSE_AND_COPY_MACHINE */
