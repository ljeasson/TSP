/*
 * Evaluate.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */


#include <Evaluate.h>
#include <math.h>
#include <iostream>

using namespace std;

double Eval(Individual *individual, int** cities){
	double sum = 0;
	double c_max = 0; double fx = 0;
	double xd = 0; double yd = 0; double dij = 0;
	
	for(int i = 1; i <= individual->chromLength; i++){
		xd = cities[i][1] - cities[i-1][1];
		yd = cities[i][2] - cities[i-1][2];
		dij = round( sqrt( pow(xd,2) + pow(yd,2) ) );
		fx += dij;
		//sum += (individual->chromosome[i] == 1 ? 1: 0);
	}
	
	sum = c_max - fx;
	return sum;
}
