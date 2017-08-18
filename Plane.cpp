//
// Created by 研究用 on 2017/08/15.
//

#include "Plane.h"
#include "Parameters.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

//constructor
Plane::Plane(int N) {
    map.resize(N);
    for(int i=0;i<N;i++) map[i].resize(N);
    probability.resize(N);
    for(int i=0;i<N;i++){
        probability[i].resize(N);
        for(int j=0;j<N;j++) probability[i][j]=1.0/(N*N);   //initialize probability distribution uniformly
    }
}

//input map
void Plane::input_map() {
    number_G=number_R=0;

    cout<<"Input color at each cell (R or G; "<< map.size() <<"*"<<map.size()<<"):";
    for(int i=0;i<map.size();i++){
        for(int j=0;j<map.size();j++){
            cin>>map[i][j];
            if(map[i][j]=='G') number_G++;
            else if (map[i][j]=='R') number_R++;
        }
    }
}

//movement
void Plane::move() {
    cout<<"Input movement order stay:0 0, right: 0 1, left: 0 -1, down: 1 0, up: -1 0:";
    int i_input,j_input;
    cin>>i_input>>j_input;

    //when no movement is ordered, do nothing
    if(i_input==0 && j_input==0) return;

    //preserve probability in temporal matrix, and make it zero
    vector<vector<double>> prob_temp(map.size());
    for(int i=0;i<map.size();i++){
        prob_temp[i].resize(map.size());
        for(int j=0;j<map.size();j++){
            prob_temp[i][j]=probability[i][j];
            probability[i][j]=0;
        }
    }

    double temp_gain;
    for(int i=0;i<map.size();i++){
        for(int j=0;j<map.size();j++){
             //when right move is ordered
            if(i_input==0 && j_input==1) {
                //at the left boarder
                if(j==0) temp_gain=prob_temp[i][map.size()-1];
                else temp_gain=prob_temp[i][j-1];
            }
                //when left move is ordered
            else if(i_input==0 && j_input==-1) {
                //at the right boarder
                if(j == map.size()-1) temp_gain=prob_temp[i][map.size()-1];
                else temp_gain=prob_temp[i][j+1];

            }
                //when down move is ordered
            else if(i_input==1 && j_input==0) {
                //at the upper boarder
                if(i == 0) temp_gain=prob_temp[map.size()-1][j];
                else temp_gain=prob_temp[i-1][j];
            }
                //when up move is ordered
            else if(i_input==-1 && j_input==0) {
                //at the bottom boarder
                if(i == map.size()-1) temp_gain=prob_temp[0][j];
                else temp_gain=prob_temp[i+1][j];
            }

            probability[i][j]=prob_temp[i][j]+prob_move*(temp_gain-prob_temp[i][j]);
        }
    }
}

//measurement
void Plane::measure() {
    char input_color;
    cout<<"Input measured color (R or G):";
    cin>>input_color;

    double total_prob=0;
    double temp_prob=0;
    for(int i=0;i<map.size();i++){
        for(int j=0;j<map.size();j++){
            if(input_color==map[i][j] && input_color=='R'){
                temp_prob=prob_sensor/number_R;
            }
            else if(input_color==map[i][j] && input_color=='G'){
                temp_prob=prob_sensor/number_G;
            }
            else if(input_color!=map[i][j] && input_color=='G'){
                temp_prob=(1.0-prob_sensor)/number_G;
            }
            else if(input_color!=map[i][j] && input_color=='R'){
                temp_prob=(1.0-prob_sensor)/number_R;
            }

            probability[i][j]*=temp_prob;
            total_prob+=probability[i][j];
        }
    }

    //normalize in the end
    for(int i=0;i<map.size();i++){
        for(int j=0;j<map.size();j++) probability[i][j]/=total_prob;
    }

}

void Plane::show_prob() {
    for(int i=0;i<map.size();i++){
        for(int j=0;j<map.size();j++) cout<< probability[i][j]<<" ";
        cout<<endl;
    }
}
