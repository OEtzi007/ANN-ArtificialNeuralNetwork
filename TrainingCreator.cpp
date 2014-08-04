/*
 * TrainingCreator.cpp
 *
 *  Created on: 03.08.2014
 *      Author: David
 */

#include "TrainingCreator.h"

#include <iostream>
#include <fstream>
#include <cassert>

TrainingCreator::TrainingCreator() {
	// TODO Auto-generated constructor stub
	topology.push_back(4);
	topology.push_back(10);
	topology.push_back(2);
	std::ofstream myfile;
	myfile.open("trainingData.txt");
	myfile << "topology:";
	for (unsigned i = 0; i < topology.size(); i++)
		myfile << " " << topology[i];
	myfile << std::endl;
	funcins();
	funcouts();
	for (unsigned i = 0; i < randomInputs.size(); i++) {
		myfile << "in:";
		for (unsigned j = 0; j < randomInputs[i].size(); j++)
			myfile << " " << randomInputs[i][j];
		myfile << std::endl << "out:";
		for (unsigned j = 0; j < outputs[i].size(); j++)
			myfile << " " << outputs[i][j];
		myfile << std::endl;
	}
	myfile.close();
}

TrainingCreator::~TrainingCreator() {
	// TODO Auto-generated destructor stub
}

double TrainingCreator::dxor(double one, double two) {
	return int(one + two + 2) % 4 - 1;
}

void TrainingCreator::funcouts() {
	assert(randomInputs[0].size() == 4);
	for (unsigned i = 0; i < randomInputs.size(); i++) {
		std::vector<double> output;
		double sum = 0;
		for (unsigned j = 0; j < randomInputs[i].size(); j++)
			sum += 1 + randomInputs[i][j];
		for (unsigned j = 0; j < 2; j++) {
			output.push_back(int(sum) % 3 - 1);
			sum = (sum - int(sum) % 3) / 3;
		}
		outputs.push_back(output);
	}
}

void TrainingCreator::funcins() {
	for (int i = 0; i < 1000000; i++) {
		std::vector<double> newelement;
		for (unsigned j = 0; j < topology[0]; j++)
			newelement.push_back(rand() % 3 - 1);
		double sum = 0;
		for (unsigned j = 0; j < topology[0]; j++)
			sum += newelement[j];
		if (sum >= topology[0]+1)
			--i;
		else
			randomInputs.push_back(newelement);
	}
	std::vector<double> newelement;
	for (unsigned j = 0; j < topology[0]; j++)
		newelement.push_back(1.0);
	randomInputs.push_back(newelement);
}
