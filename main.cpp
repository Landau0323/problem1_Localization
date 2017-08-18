#include <iostream>
#include "Plane.h"

using namespace std;

///////////////////////////////////////////
//This is a localization program of bot on plane.
//Each cell on the plane is colored with green or red.
//The bot can observe the color of the cell, and can move in the four direction.
//By using Baysian filter, the bot tries to locate itself after a few movement/measurement.
//The plane is cyclic.
//
//Please use the test cases below for testing this code.
///////////////////////////////////////////

int main() {

    int N;  //size of map
    cout<<"Input size of map:";
    cin>>N;
    Plane* pP=new Plane(N); //generate instance

    pP->input_map();    //input map
    //example: G G G G R R G G G

    cout<<"Input number of measurement/movement:";
    cin>>N;
    for(int i=0;i<N;i++){
        pP->move();
        pP->show_prob();
        pP->measure();
        pP->show_prob();
    }

    return 0;
}

///////////////////////////////////////////
//test case 1:
//size of map: 3
//color at each cell: G G G
//                    G R G
//                    G G G
//number of measurement/movement: 1
//movement order: 0 0
//measured color R
//->result: it is likely that the bot is at the center cell.

//test case 2:
//size of map: 3
//color at each cell: G G G
//                    G R R
//                    G G G
//number of measurement/movement: 1
//movement order: 0 0
//measured color R
//->result: it is likely that the bot is at one of the two red cells.

//test case 3:
//size of map: 3
//color at each cell: G G G
//                    G R R
//                    G G G
//number of measurement/movement: 2
//movement order: 0 0, 0 1
//measured color R R
//->result: it is likely that the bot is at the red cell in the right.

///////////////////////////////////////////
