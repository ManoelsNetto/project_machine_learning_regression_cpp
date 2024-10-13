#pragma once
#include "LinearRegression.h"
#include <numeric>
#include <iostream>
#include <vector>

class LinearMetrics : public LinearRegression {

	protected:
		
		float r2f, r2g, r;

	public:

		// Constructor
		LinearMetrics() {

			r = 0;
			r2f = 0;
			r2g = 0;

		};

		// Correlation
		void correlation();
		void rsquare_for_formula();
		void rsquare_for_gradient();

};

