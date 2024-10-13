#include "LinearRegression.h"
#include <numeric>
#include <iostream>
#include <vector>

LinearRegression::LinearRegression() 
	: b1{ 0 }, b0{ 0 }, xbar{ 0 }, ybar{ 0 }, intercept{ 0 }, slope{ 0 } {
};

void LinearRegression::estimate() {

	// Variables
	float xDeviation, yDeviation, covSum = 0, varSum = 0;

	// Dependent and independent variables means
	ybar = std::accumulate(y.begin(), y.end(), 0) / y.size();
	xbar = std::accumulate(x.begin(), x.end(), 0) / x.size();

	// Loop
	for (int i = 0; i < x.size(); i++) {

		xDeviation = (x[i] - xbar);
		yDeviation = (y[i] - ybar);
		covSum += xDeviation * yDeviation;
		varSum += xDeviation * xDeviation;

	};

	// Coeffs
	b1 = covSum / varSum;
	b0 = ybar - (b1 * xbar);

};

void LinearRegression::show() {

	std::cout << "=== Linear Regression ===" << std::endl;
	std::cout << "Intercept: " << b0 << std::endl;
	std::cout << "Slope: " << b1 << std::endl;
	

};

void LinearRegression::predict() {

	for (int i = 0; i < y_test.size(); i++) {

		float z;

		z = b0 + (b1 * x_test[i]);

		yp.push_back(z);

	}

};

// Learning algorithm
void LinearRegression::gradient_descent(bool plot, float learning_rate, int max_iterations) {

	// Variables
	float c = 0.0f; // intercept
	float m = 0.0f; // slope
	int n = x.size(); // number of data points
	float alpha = learning_rate; // learning rate
	
	for (int iter = 0; iter < max_iterations; iter++) {

		float intercept_gradient = 0.0f;
		float slope_gradient = 0.0f;
		float total_error = 0.0f;

		// Calculate gradients
		for (int i = 0; i < n; i++) {

			float pred = c + (m * x[i]);
			float error = pred - y[i];

			total_error += error * error; // sum of squared errors
			intercept_gradient += error;
			slope_gradient += error * x[i];

		}

		// Update parameters
		c -= alpha * (intercept_gradient / n);
		m -= alpha * (slope_gradient / n);

		// Print the error to monitor convergence
		if (plot && (iter % 100 == 0)) {

			std::cout << "Iteration: " << iter << "; Error: " << total_error / n << std::endl;

		}

	}

	std::cout << "=== Gradient Descent ===" << std::endl;
	std::cout << "Intercept: " << c << "\nSlope: " << m << std::endl;

	slope = m;
	intercept = c;

};