#ifndef MANAGERS
#define MANAGERS


// checking if element is in vector
bool is_exist (std::vector<int> v, int element);

// compearing pairs
bool is_same (std::pair<std::vector<int>, int> l, std::pair<std::vector<int>, int> r);

// overloaded checking if element is in vector (for another kind)
bool is_exist (std::vector<std::pair<std::vector<int>, int> > v, std::pair<std::vector<int>, int> element);

// getting process for managers simulations
unsigned short get_processes ();

// getting intervals for managers simulations
std::vector<int> get_intervals ( unsigned short t_num );

// print function for petter look
void p_print ( std::vector<std::vector<int> > pt_array );

// check if element fits to box
bool is_fit ( std::vector<int> box, int pack_value, int box_capacity );

// getting packs for simulations
std::vector<int> get_packs ( int max_size );

// print function for petter look
void boxes_print ( std::vector<std::vector<int> > boxes_array, unsigned short box_capacity );

// getting box for simulations
unsigned short get_boxes ( unsigned short box_capacity, std::vector<int> packs );

// sorting funcction for std::sort()
bool sort_translators( std::pair<std::vector<int>, int> l, std::pair<std::vector<int>, int> r);

// improved version of standart rand()
int good_rand( int up_boarder );

// find lingest in array
int get_longest (std::vector<std::vector<int> > pt_array);

// check if process is beasy (by it's counter)
bool is_busy (std::vector<int> process, int time );

// simulation function
unsigned short manage_time ( unsigned short p_num, std::vector<int> intervals );

// getting capacity for simulations
unsigned short get_capacity ();

// sort function for std::sort()
bool sort_func( std::vector<int> l, std::vector<int> r );


#endif /* end of include guard: MANAGERS */
