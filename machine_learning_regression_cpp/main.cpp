#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include "LinearMetrics.h"
#include <experimental/filesystem>

int main() {

	// Constructor
	LinearMetrics dataset;

	// Loading data
	dataset.read_data("data\\insurance.csv");
	dataset.check();
	dataset.split_data();
	dataset.correlation();
	dataset.estimate();
	dataset.show();
	dataset.predict();
	dataset.rsquare_for_formula();
	dataset.gradient_descent();
	dataset.rsquare_for_gradient();
	return 0;

}