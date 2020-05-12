#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstdint>
#include <vector>
#include <ctime>
#include <chrono>
#include <limits.h>
#include <utility>
#include <cmath>

#include "Managers/managers.h"
#include "VertexFind/vertex.h"


#define MACHINE_AMOUNT 3


int main(int argc, char const *argv[]) {


    system("clear");

    std::cout << "\n========= First (Time manage) task =========" << '\n';

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


    std::cout << "\n========= Second (languages manage) task =========" << '\n';


    std::vector<int> languages;

    std::vector<std::pair<std::vector<int>, int> > translators;
    std::vector<std::pair<std::vector<int>, int> > res_translators;


    size_t translators_amount = 30;
    size_t max_price = 50;
    int res_price = 0;

    for (size_t i = 1; i < 11; i++)
    languages.push_back(i);

    for (size_t i = 0; i < translators_amount; i++){

        int known_languages_amount = good_rand(5);

        std::pair<std::vector<int>, int> translator = std::pair<std::vector<int>, int>(std::vector<int>(), good_rand(max_price));

        for (size_t j = 0; j < known_languages_amount; j++) {
            int language = good_rand(11);
            while (is_exist(translator.first, language)) {
                language = good_rand(11);
            }
            translator.first.push_back(language);
        }

        translators.push_back(translator);

    }

    std::sort(translators.begin(), translators.end(), sort_translators);


    /*

    if we have translator with language that we need,
    and he is not already in res_translators => add him to res

    */
    for (int language : languages)
    for (auto translator : translators)
    if (is_exist(translator.first, language))
    if (!is_exist(res_translators, translator)){
        res_translators.push_back(translator);
        res_price += translator.second;
        break; }


        /*
        // Uncoomment this to print
        for (auto translator : res_translators) {
        std::cout << "Price: " << translator.second << '\n';
        for (auto lang : translator.first)
        std::cout << lang << ' ';
        std::cout << '\n';

    }
    */

    std::cout << "Result price: " << res_price << '\n';

    std::cout << "\n========= Third (machine manage) task =========" << '\n';

    /*
    std::vector<unsigned> is a part,
    first  element of array - part index;
    second element of array - A machine time;
    third  element of array - B machine time;
    fourth element of array - C machine time;
    */

    std::vector<std::vector<int> > parts;

    size_t parts_amount = 10;

    for (int i = 0; i < parts_amount; i++){
        std::vector<int> part;
        part.push_back(i);
        for (size_t j = 0; j < MACHINE_AMOUNT; j++) {
            part.push_back(good_rand(20));
        }
        parts.push_back(part);
    }

    std::sort(parts.begin(), parts.end(), sort_func);

    std::cout << "PARTS ORDER: " << '\n';

    for (auto part : parts) {
        std::cout << part[0] << ' ';
        /*
        // Uncoomment this to print
        for (size_t i = 1; i < part.size(); i++) {
        s   td::cout << part[i] << ' ';
        }
        std::cout << '\n';
        */
    }

    std::cout << "\n========= Fourth (find vertex) task =========" << '\n';

    vertex();
}
