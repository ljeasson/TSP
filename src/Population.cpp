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

#include <unistd.h>

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
	sprintf(printbuf, "%4i \t %f \t %f \t %f \t \n ", (int)gen, min, avg, max);
	WriteBufToFile(std::string(printbuf), options.outfile);
	std::cout << printbuf;
}

void Population::Generation(Population *child){
	
	// For all members in parent population
	// Get 2 parents and produce 2 children using crossover and mutation
	int pi1, pi2, range1, range2;
	Individual *p1, *p2, *c1, *c2;
	for(int i = 0; i < options.popSize; i += 2){
		pi1 = IntInRange(0,options.popSize-1); 
		pi2 = IntInRange(0,options.popSize-1);
		
		p1 = members[pi1]; p2 = members[pi2];
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
		PMXOnePoint(p1, p2, c1, c2);
	}
	// Swap mutate each child
	c1->SwapMutate(options.pm);
	c2->SwapMutate(options.pm);	
}

void Population::PMXOnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2){ //not debugged
	int t1 = IntInRange(0, options.chromLength);
		
	// Perform Crossover
	for(int i = t1; i < options.chromLength; i++){
		c1->chromosome[i] = p2->chromosome[i];
		c2->chromosome[i] = p1->chromosome[i];
	}
	
	// Loop through part of chromosome that did not participate in crossover
	for (int i = 0; i < t1; i++){
		// Loop through part of chromosome that DID participate in crossover
		for(int j = t1; j < options.chromLength; j++){
			// If an element in non-crossover is found in crossover
			// i.e a duplicate, replace it with corresponding element 
			// from other chromosome
			
			// Check child1 for duplicates and replace
			if (c1->chromosome[i] == c1->chromosome[j])
				c1->chromosome[i] = c2->chromosome[j];
			// Check child2 for duplicates replace
			if (c2->chromosome[i] == c2->chromosome[j])
				c2->chromosome[i] = c1->chromosome[j];
		}
	}
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
