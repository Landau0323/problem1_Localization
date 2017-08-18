//
// Created by 研究用 on 2017/08/15.
//

#ifndef PROBLEM1_LOCALIZATION_PLANE_H
#define PROBLEM1_LOCALIZATION_PLANE_H

#include <string>
#include <limits>
#include <vector>
#include <climits>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


class Plane {
private:
    vector<vector<char>> map;   //map of plane. this is given.
    vector<vector<double>> probability; //probability distribution on plane
    int number_G,number_R;  //number of green/red cells

public:
    Plane(int);
    void input_map();
    void move();
    void measure();
    void show_prob();
};

#endif //PROBLEM1_LOCALIZATION_PLANE_H
