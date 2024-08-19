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
	dataset.estimate();
	dataset.show();
	dataset.gradient_descent();
	
	return 0;

}