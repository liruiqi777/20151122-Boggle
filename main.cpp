/*
 * main.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: Ruiqi (Sally) Li
 *
 *
 *  Created by Eric Chown on 9/26/12.
 *  Copyright (c) 2012 Eric Chown. All rights reserved.
 * 	Modified, with permission, by Stephen Majercik on 10/11/14
 */




#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Boggle.h"

using namespace std;

int main(int argc, const char * argv[]) {

    cout << "Welcome to Boggle!" << endl << endl;


    // construct the boggle class
    Boggle boggleBoard = Boggle();

    // print the puzzle in the console
    cout << endl;
    boggleBoard.print();

    // human and computer play in turns
    boggleBoard.humanPlay();
    boggleBoard.computerPlay();

    return EXIT_SUCCESS;
}



