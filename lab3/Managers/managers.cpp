#include <iostream>
#include <vector>

// #include "managers.h"

// checking if element is in array
bool is_exist (std::vector<int> v, int element) {
    for (int n : v)
    if (n == element)
    return true;
    return false;
}

// compearing function for our elements, return true if we have same element on both sides
bool is_same (std::pair<std::vector<int>, int> l, std::pair<std::vector<int>, int> r) {

    if (l.second != r.second || l.first.size() != r.first.size())
    return false;


    for (size_t i = 0; i < l.first.size(); i++)
    if (l.first[i] != r.first[i])
    return false;

    return true;
}

// overloaded func for checking if another type of element is in another type of array
bool is_exist (std::vector<std::pair<std::vector<int>, int> > v, std::pair<std::vector<int>, int> element) {
    if (v.empty())
    return false;

    for (auto e : v)
    if (is_same(e, element))
    return true;
    return false;
}


unsigned short get_processes () {
    return (unsigned short)( rand() % 9 + 1 );
}

std::vector<int> get_intervals ( unsigned short t_num ) {
    std::vector<int> res;
    for (size_t i = 0; i < t_num; i++) {
        res.push_back( rand() % 9 + 1 );
    }
    return res;
}

void p_print ( std::vector<std::vector<int> > pt_array ) {
    int index = 0;
    for ( std::vector<int> process : pt_array ) {
        printf("P%d:", index);
        for (int interval : process) {
            for (size_t i = 0; i < interval; i++) {
                printf("-");
            }
            printf("|");
        }
        index++;
        printf("\n");
    }
}

bool is_fit ( std::vector<int> box, int pack_value, int box_capacity ) {
    int box_value = 0;

    for (int p : box)
    box_value += p;

    return (box_capacity - box_value) > pack_value;
}

std::vector<int> get_packs ( int max_size ) {
    std::vector<int> res;
    int packs_amount = rand() % 50;
    for (size_t i = 0; i < packs_amount; i++) {
        res.push_back( rand() % max_size + 1 );
    }
    return res;
}

void boxes_print ( std::vector<std::vector<int> > boxes_array, unsigned short box_capacity ) {
    int index = 0;
    for ( std::vector<int> box : boxes_array ) {
        printf("Box%d: |", index);

        int left = box_capacity;
        for (int pack_value : box) {
            for (size_t i = 0; i < pack_value; i++) {
                printf("/");
                left--;
            }
            printf("|");
        }
        for (size_t i = 0; i < left; i++) {
            printf(":");
        }
        printf("|");

        index++;
        printf("\n");
    }
}

unsigned short get_boxes ( unsigned short box_capacity, std::vector<int> packs ) {

    std::vector<std::vector<int> > boxes_array;

    std::sort(packs.begin(), packs.end(), std::greater<int>());

    boxes_array.push_back(std::vector<int>());

    int current = 0;
    while (current < packs.size()) {
        bool found = false;
        if (packs[current] > box_capacity) { return -1; }
        for (size_t i = 0; i < boxes_array.size(); i++) {
            if (is_fit(boxes_array[i], packs[current], box_capacity)) {
                boxes_array[i].push_back(packs[current]);
                found = true;
                current++;
                break;
            }
        }
        if (!found) {
            boxes_array.push_back(std::vector<int>());
            boxes_array[(boxes_array.size() - 1)].push_back(packs[current]);
            current++;
        }
    }

    boxes_print ( boxes_array, box_capacity );

    return boxes_array.size();
}


// function for std::sort
bool sort_translators( std::pair<std::vector<int>, int> l, std::pair<std::vector<int>, int> r) {
    return l.second < r.second;
}


// rand on hight values works better, so we are using it here
int good_rand( int up_boarder ) {
    return ( rand() % up_boarder * 10000 ) / 10000 + 1;
}

int get_longest (std::vector<std::vector<int> > pt_array) {
    int longest_time = INT_MIN;
    for ( std::vector<int> process : pt_array ) {
        int process_t = 0;
        for (int interval : process) {
            process_t += interval;
        }
        if (process_t > longest_time)
        longest_time = process_t;
    }
    return longest_time;
}

bool is_busy (std::vector<int> process, int time ) {
    int process_t = 0;

    for (int t : process)
    process_t += t;

    return process_t > time;
}

unsigned short manage_time ( unsigned short p_num, std::vector<int> intervals ) {
    std::vector<std::vector<int> > pt_array;

    std::sort(intervals.begin(), intervals.end(), std::greater<int>());

    for (size_t i = 0; i < p_num; i++)
    pt_array.push_back(std::vector<int>());

    int tic = 0;
    int current = 0;
    while (current < intervals.size()) {
        for (size_t i = 0; i < pt_array.size(); i++) {
            if (!is_busy(pt_array[i], tic)) {
                pt_array[i].push_back(intervals[current]);
                current++;
            }
        }
        tic++;
    }

    p_print(pt_array);

    return get_longest(pt_array);
}

unsigned short get_capacity () {
    return (unsigned short)( rand() % 9 + 1 );
}

// function for srd::sort()
bool sort_func( std::vector<int> l, std::vector<int> r ) {

    if (l[1] < r[1]) {
        return true;
    } else if (l[1] == r[1]) {
        if (l[2] < r[2]) {
            return true;
        } else if (l[2] == r[2]) {
            return (l[3] < r[3]);
        }
    }
    return false;
}
