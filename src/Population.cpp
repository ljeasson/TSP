/*
 * Population.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include "Population.h"
#include <assert.h>
#include <Evaluate.h>
#include <Utils.h>
#include <iostream>

using namespace std;
Options global_opts;

Population::Population(Options opts) {
	options = opts;
	global_opts = opts;
	avg = min = max = sumFitness = -1;
	assert(options.popSize <= MAXPOP);
	for (int i = 0; i < options.popSize; i++){
		members[i] = new Individual(options.chromLength);
		members[i]->Init();
	}
}

Population::~Population() {
	// TODO Auto-generated destructor stub
}

void Population::Init(){
	Evaluate();
}

void Population::Evaluate(){
	for (int i = 0; i < options.popSize; i++){
		members[i]->fitness = Eval(members[i], global_opts);
	}
}

void Population::Statistics(){
	sumFitness = 0;
	min = members[0]->fitness;
	max = members[0]->fitness;
	for(int i = 0; i < options.popSize; i++){
		sumFitness += members[i]->fitness;
		if(min > members[i]->fitness)
			min = members[i]->fitness;
		if(max < members[i]->fitness)
			max = members[i]->fitness;
	}
	avg = sumFitness/options.popSize;
	//tourLength = members[0]->tourLength;
}

void Population::Report(unsigned long int gen){
	char printbuf[1024];
	sprintf(printbuf, "%4i \t %f \t %f \t %f\n ", (int)gen, min, avg, max);
	WriteBufToFile(std::string(printbuf), options.outfile);
	std::cout << printbuf;
}

void Population::Generation(Population *child){
	
	// For all members in parent population
	// Get 2 parents and produce 2 children using crossover and mutation
	Individual *p1, *p2, *c1, *c2;
	for(int i = 0; i < options.popSize; i += 2){
		p1 = members[i]; p2 = members[i+1];
		c1 = child->members[i]; c2 = child->members[i+1];
		PMXAndSwapMutate(p1, p2, c1, c2);
	}
	
	// Competition between parent and child population
	for (int i = 0; i < options.popSize; i++){
	
		// If parent fitness at index is greater, assign to child fitness at index
		// otherwise, leave as is
		if (members[i]->fitness > child->members[i]->fitness){
			child->members[i]->fitness = members[i]->fitness;			
		}
	}
}

void Population::PMXAndSwapMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2){
	
	// Copy parents to children
	for(int i = 0; i < options.chromLength; i++){ 
		c1->chromosome[i] = p1->chromosome[i];
		c2->chromosome[i] = p2->chromosome[i];
	}
	// If prob of Xover, then cross/exchange bits
	if(Flip(options.px)){ 
		//PMXOnePoint(p1, p2, c1, c2);
	}
	// Swap mutate each child
	c1->SwapMutate(options.pm);
	c2->SwapMutate(options.pm);	
}

// TODO
void Population::PMXOnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2){ //not debugged
	int t1 = IntInRange(0, options.chromLength);
	
	cout << "IntInRange: " << t1 << endl;
	cout << "p1: ";
	for(int i = 0; i < options.chromLength; i++){
		cout << p1->chromosome[i] << " ";
	}
	cout << endl << "p2: ";
	for(int i = 0; i < options.chromLength; i++){
		cout << p2->chromosome[i] << " ";
	}
	cout << endl << endl;
	
	for(int i = t1; i < options.chromLength; i++){
		c1->chromosome[i] = p2->chromosome[i];
		c2->chromosome[i] = p1->chromosome[i];
	}
	
	cout << "c1: ";
	for(int i = 0; i < options.chromLength; i++){
		cout << c1->chromosome[i] << " ";
	}
	cout << endl << "c2: ";
	for(int i = 0; i < options.chromLength; i++){
		cout << c2->chromosome[i] << " ";
	}
	cout << endl << endl << endl;
}





int Population::ProportionalSelector(){
	int i = -1;
	float sum = 0;
	float limit = RandomFraction() * sumFitness;
	do {
		i = i + 1;
		sum += members[i]->fitness;
	} while (sum < limit && i < options.popSize-1 );

	return i;
}

void Population::XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2){

	for(int i = 0; i < options.chromLength; i++){ //First copy
		c1->chromosome[i] = p1->chromosome[i];
		c2->chromosome[i] = p2->chromosome[i];
	}
	if(Flip(options.px)){ // if prob, then cross/exchange bits
		OnePoint(p1, p2, c1, c2);
	}

	c1->Mutate(options.pm);
	c2->Mutate(options.pm);
}

void Population::OnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2){ //not debugged
	int t1 = IntInRange(0, options.chromLength);
	for(int i = t1; i < options.chromLength; i++){
		c1->chromosome[i] = p2->chromosome[i];
		c2->chromosome[i] = p1->chromosome[i];
	}
}

void Population::TwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2){ //not debugged
	int t1 = IntInRange(0, options.chromLength);
	int t2 = IntInRange(0, options.chromLength);
	int xp1 = std::min(t1, t2);
	int xp2 = std::max(t1, t2);
	for(int i = xp1; i < xp2; i++){
		c1->chromosome[i] = p2->chromosome[i];
		c2->chromosome[i] = p1->chromosome[i];
	}
}
