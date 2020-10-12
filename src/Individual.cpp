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
		//chromosome[i] = Flip(0.5f);
	}
}


// Source: CS 776 Lecture 11 class slides
void Individual::SwapMutate(double pm){
	
	int randChromNum; int temp;
	for (int i = 0; i < chromLength; i++){
		if(Flip(pm)){
		
			// Change bit to random number in range 1 to chromLength
			randChromNum = rand() % ( chromLength - 1 + 1 ) + 1;
			temp = chromosome[i];
			chromosome[i] = randChromNum;
			
			// Find previous index in chromosome and assign original value
			for (int j = 0; j < chromLength; j++){
				if (j != i && chromosome[j] == randChromNum){
					chromosome[j] = temp;
				}
			}
			
			
		}
	}	
}


void Individual::Mutate(double pm){
	for(int i = 0; i < chromLength; i++){
		if(Flip(pm))
			chromosome[i] = 1 - chromosome[i];
	}

}
