/*
 * GA.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include "GA.h"
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include <string.h>
#include <stdio.h>

using namespace std;


GA::GA(int argc, char *argv[], int randomSeed) {
	ReadTSPFile(argc, argv);
	SetupOptions(argc, argv, randomSeed);
	srandom(options.randomSeed);	
}

GA::~GA() {
	// TODO Auto-generated destructor stub
}

void GA::ReadTSPFile(int argc, char *argv[]){
	string line;
	int index = 0;
		
	// FUTURE:  Modify file reading so that you don't need to delete 
	// 	    header and EOF
	ifstream infile(argv[1]);
	if (infile.is_open()){
		while (getline(infile,line)){
			
			istringstream iss(line);
			vector<double> tokens;
			while ( getline( iss, line, ' ' )) {
				tokens.push_back(atof(line.c_str()));
			}
				
			options.cities[index][0] = tokens.at(0);
			options.cities[index][1] = tokens.at(1);
			options.cities[index][2] = tokens.at(2);
			
			index++;
		}
		infile.close();
	}
	else cout << "Unable to open file"; 
	
	options.chromLength = index; //10;
}


void GA::SetupOptions(int argc, char *argv[], int randomSeed){
	
	options.randomSeed = randomSeed;
	options.popSize = atoi(argv[2]); //30;
	options.maxgens = options.popSize * 1.5; //60;
	
	options.px = 0.00f; //0.95f; //0.7f;
	options.pm = 0.05f; //0.00f; //0.001f;
	
	options.infile = std::string ("infile");
	options.outfile = std::string("outfile");
	
}

void GA::Init(){
	parent = new Population(options);
	child  = new Population(options);
	parent->Init(); // evaluates, stats, and reports on initial population
	parent->Statistics();
	parent->Report(0);
	
}

void GA::Run(){

	for(unsigned long int i = 1; i < options.maxgens; i++){
		parent->Generation(child);
		child->Evaluate();
		child->Statistics();
		child->Report(i);

		Population *tmp = parent;
		parent = child;
		child = tmp;
	}

}

