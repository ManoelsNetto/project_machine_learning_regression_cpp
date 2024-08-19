#pragma once
#include "LoadCSV.h"
#include <numeric>

class LinearRegression : public LoadCSV
{

protected:

	float b1, b0, xbar, ybar;
	float slope, intercept;

public:

	// Constructor
	LinearRegression();
	void estimate();
	void show();
	void predict();
	void gradient_descent(float learning_rate = 0.00019, int max_iterations = 4500);
	

};

