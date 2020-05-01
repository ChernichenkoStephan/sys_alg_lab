#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits.h>


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

bool is_busy (std::vector<int> process, int time ) {
	int process_t = 0;

	for (int t : process)
		process_t += t;

	return process_t > time;
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


std::vector<int> get_packs ( int max_size ) {
	std::vector<int> res;
	int packs_amount = rand() % 50;
	for (size_t i = 0; i < packs_amount; i++) {
		res.push_back( rand() % max_size + 1 );
	}
	return res;
}

unsigned short get_capacity () {
	return (unsigned short)( rand() % 9 + 1 );
}

bool is_fit ( std::vector<int> box, int pack_value, int box_capacity ) {
	int box_value = 0;

	for (int p : box)
		box_value += p;

	return (box_capacity - box_value) > pack_value;
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


int main(int argc, char **argv) {

    system("clear");

	std::cout << "\n========= Time manage task =========" << '\n';

	unsigned short p_num = get_processes();

	std::vector<int> intervals = get_intervals(10);

	std::cout << "Num processes: " << p_num << "\nIntervals values: " << '\n';
	for(size_t i = 0; i < intervals.size(); i++)
		std::cout << "Interval"<< i << " time : " << intervals[i] << '\n';

	unsigned short time = manage_time(p_num, intervals);

	std::cout << "Work time: " << time << '\n';

	std::cout << "\n========= Box task =========" << '\n';

	unsigned short box_capacity = get_capacity();

	std::cout << "Box capacity: " << box_capacity << '\n';

	std::vector<int> packs = get_packs( box_capacity - 1 );

	std::cout << "Packs values: " << '\n';
	for(size_t i = 0; i < packs.size(); i++)
		std::cout << "Pack"<< i << " value : " << packs[i] << '\n';

	unsigned short boxes_amount = get_boxes(box_capacity, packs);

	std::cout << "Amount of boxes : " << boxes_amount << '\n';


    return 0;
}
