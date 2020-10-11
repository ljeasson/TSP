/*
 * Evaluate.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */


#include <Evaluate.h>
#include <Options.h>
#include <Utils.h>
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;

double Eval(Individual *individual, Options opts){
	double sum = 0;
	double c_max = 200000; double fx = 0;
	double xd = 0; double yd = 0; double dij = 0;	
	
	for(int i = 1; i <= individual->chromLength; i++){	
		// Find index of current city at chromosome[i] and chromosome[i-1]
		int index1; int index2;
		for (int j = 0; j < individual->chromLength; j++){
			if (opts.cities[j][0] == individual->chromosome[i]){
				index1 = j;
			}
			if (opts.cities[j][0] == individual->chromosome[i-1]){
				index2 = j;
			}
		}
		//cout << "Chromosome[i]: " << individual->chromosome[i] << endl;
		//cout << opts.cities[index1][0] << " " << opts.cities[index1][1] << " " << opts.cities[index1][2] << endl;
		//cout << "Chromosome[i-1]: " << individual->chromosome[i-1] << endl;
		//cout << opts.cities[index2][0] << " " << opts.cities[index2][1] << " " << opts.cities[index2][2] << endl;
		
		// Calculate Euclidean distance between cities
		xd = opts.cities[index1][1] - opts.cities[index2][1];
		yd = opts.cities[index1][2] - opts.cities[index2][2];
		dij = round( sqrt( pow(xd,2) + pow(yd,2) ) );
		fx += dij;
		//cout << "X dist: " << xd << endl;
		//cout << "Y dist: " << yd << endl;
		//cout << "Euc dist: " << dij << endl;
		//cout << "fx: " << fx << endl;
		//cout << endl;
		
		//sum += (individual->chromosome[i] == 1 ? 1: 0);
	}
	
	sum = c_max - fx;
	return sum;
}
