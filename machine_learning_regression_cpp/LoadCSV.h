#pragma once
#include <vector>
#include <string>

class LoadCSV
{

protected:
	
	// Vectors
	std::vector<std::pair<std::string, std::vector< float>>> data;
	std::vector<float> x, y, yp, y_gra, x_test, y_test;

	// File name - CSV
	std::string file_name;

	// Others variables
	float x_factor, y_factor;
	int n;

public:

	// Method to import the data
	void read_data(std::string file);
	void check();
	void data_normalization(int normal_level = 7, int type = 0);
	void split_data(int debug = 0);


};

