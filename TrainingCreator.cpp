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
	topology.push_back(8);
	topology.push_back(12);
	topology.push_back(5);
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
	assert(randomInputs[0].size() == 8);
	for (unsigned i = 0; i < randomInputs.size(); i++) {
		std::vector<double> output;
		double carry = -1;
		for (unsigned j = 0; j < 4; j++) {
			output.push_back(
					dxor(carry,
							dxor(randomInputs[i][j], randomInputs[i][4 + j])));
			carry = carry + randomInputs[i][j] + randomInputs[i][j + 4] >= 1 ?
					1 : -1;
		}
		output.push_back(carry);
		outputs.push_back(output);
	}
}

void TrainingCreator::funcins() {
	for (int i = 0; i < 100000; i++) {
		std::vector<double> newelement;
		for (unsigned j = 0; j < topology[0]; j++)
			newelement.push_back(rand() % 2 == 0 ? 1 : -1);
		double sum = 0;
		for (unsigned j = 0; j < topology[0]; j++)
			sum += newelement[j];
		if (sum >= topology[0])
			--i;
		else
			randomInputs.push_back(newelement);
	}
	std::vector<double> newelement;
	for (unsigned j = 0; j < topology[0]; j++)
		newelement.push_back(1.0);
	randomInputs.push_back(newelement);
}
