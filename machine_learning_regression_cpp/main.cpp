#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include "LoadCSV.h"
#include <experimental/filesystem>

int main() {

	// Constructor
	LoadCSV dataset;

	// Loading data
	dataset.read_data("data\\dataset.csv");
	dataset.check();
	dataset.data_normalization();
	dataset.split_data();

	std::cout << "Current path " << std::experimental::filesystem::current_path() << std::endl;
	
	return 0;

}