/*
 * TrainingCreator.h
 *
 *  Created on: 03.08.2014
 *      Author: David
 */

//==============================
// include guard
#ifndef TRAININGCREATOR_H_
#define TRAININGCREATOR_H_
//==============================
// forward declared dependencies
//==============================
// included dependencies
#include <vector>
//==============================
// the actual class

class TrainingCreator {
public:
	TrainingCreator();
	virtual ~TrainingCreator();

	std::vector<std::vector<double> > randomInputs;
	std::vector<std::vector<double> > outputs;

	void funcouts();
	void funcins();
	double dxor(double one, double two);
	std::vector<unsigned> topology;
};

#endif /* TRAININGCREATOR_H_ */
