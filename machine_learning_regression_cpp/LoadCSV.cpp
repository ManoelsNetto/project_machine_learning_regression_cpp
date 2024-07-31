#include "LoadCSV.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

// Method to import the data
void LoadCSV::read_data(std::string file) {

	// Variables
	std::string line, colname;

	// Filename
	file_name = file;
	std::cout << "Filename: " << file << std::endl;

	// Fstream
	std::fstream fo;

	// File open
	fo.open(file_name.c_str(), std::ios::in); // std::ios::in is a flag used to specify that a file stream should be opened for reading

	// Reading file
	if (fo.good()) {
		
		// get one line
		getline(fo, line);

		// String stream
		std::stringstream s{ line };

		// Columns names
		while (std::getline(s, colname, ',')) {

			data.push_back({ colname, std::vector<float> {} });

		}

		int temp1;

		// Reading line data
		while (std::getline(fo, line)) {

			// Column index
			int col{ 0 };

			// Stream
			std::stringstream s1(line);

			while (s1 >> temp1) {

				// Load the data to vector
				data.at(col).second.push_back(temp1);

				col++;

				if (s1.peek() == ',') {

					s1.ignore();

				}

			}

		}

		for (int i = 0; i < data[0].second.size(); i++) {

			x.push_back(data[0].second.at(i));
			y.push_back(data[1].second.at(i));

		}

	}
	else {

		std::cout << "File error." << std::endl;

	}

	// Close stream
	fo.close();

}

// Method to check if data is OK
void LoadCSV::check() {

	int i = 0;

	while (i < data[0].second.size()) {

		if (x.at(i) != data[0].second.at(i)) {

			std::cout << "X data are distinct in the datasets at position " << i << std::endl;
			break;

		}

		i++;
	
	}

	i = 0;

	while (i < data[1].second.size()) {

		if (y.at(i) != data[1].second.at(i)) {

			std::cout << "Y data are distinct in the datasets at position " << i << std::endl;
			break;

		}

		i++;

	}

}

// Method to normalize the dataset
void LoadCSV::data_normalization(int normal_level, int type) {

	// Control variables
	long double x_sum = 0, y_sum = 0;

	// x and y sum
	for (int i = 0; i < x.size(); i++) {

		x_sum += x[i];
		y_sum += y[i];

	}

	// Normalization factors
	x_factor = x_sum / (normal_level * x.size());
	y_factor = y_sum / (normal_level * y.size());

	// Normalization
	for (int i = 0; i < x.size(); i++) {

		x[i] /= x_factor;
		y[i] /= y_factor;

	}


}

// Method to split the data into test and train datasets.
void LoadCSV::split_data(int debug) {

	// Split factor (70/30)
	int total = 0.3 * x.size();

	// Seed Random Number Generator
	std::srand(time(0));
	
	if (debug) {

		std::cout << "Indexes" << std::endl;

	};

	for (int i = 0; i < total; i++) {

		// Length of x and y
		int x_mod = x.size();
		int y_mod = y.size();
		
		// Split data indexes
		int temp = rand();
		int x_index = temp % x_mod;
		int y_index = temp % y_mod;

		if (debug) {

			std::cout << x_index << std::endl;

		};

		// Load data test
		x_test.push_back(x[x_index]);
		y_test.push_back(y[y_index]);

		// Remove tha data from the train dataset
		x.erase(x.begin() + x_index);
		y.erase(y.begin() + y_index);

	}

	if (debug) {

		std::cout << "X_test" << std::endl;

		for (int i = 0; i < x_test.size(); i++) {

			std::cout << x_test[i] << std::endl;

		}

	}

	std::cout << std::endl;

}