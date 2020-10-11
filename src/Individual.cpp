/*
 * Individual.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include <Individual.h>
#include <Utils.h>
#include <algorithm>
#include <iostream>
using namespace std;

Individual::Individual(int len) {
	// TODO Auto-generated constructor stub
	chromLength = len;
	fitness = -1;
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}

void Individual::Init(){
	// Initialize chromosome with randomly generated integers
	// in range 0 to chromLength
	int shuffle_cities[chromLength];
	int element = 1;
	for (int i = 0; i < chromLength; i++){
		shuffle_cities[i] = element;
		element++;
	}
	random_shuffle(&shuffle_cities[0], &shuffle_cities[chromLength]);
	
	for(int i = 0; i < chromLength; i++){
		chromosome[i] = shuffle_cities[i];
		//cout << chromosome[i] << " ";
		//chromosome[i] = Flip(0.5f);
	}
	//cout << endl << endl;
}

void Individual::Mutate(double pm){
	for(int i = 0; i < chromLength; i++){
		if(Flip(pm))
			chromosome[i] = 1 - chromosome[i];
	}

}

// TODO
void Individual::SwapMutate(double pm){
	for(int i = 0; i < chromLength; i++){
		
	}
}
