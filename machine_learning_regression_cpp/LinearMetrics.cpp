#include "LinearMetrics.h"
#include <iostream>
#include <numeric>
#include <vector>

void LinearMetrics::correlation() {

	float z, q, s = 0, d = 0, siz = x.size(), b = 0, sq;

	// Dependent and independent variables means
	ybar = std::accumulate(y.begin(), y.end(), 0) / y.size();
	xbar = std::accumulate(x.begin(), x.end(), 0) / x.size();
	
	// Variance and Covariance
	for (int i = 0; i < y.size(); i++) {

		z = (x[i] - xbar);
		q = (y[i] - ybar);
		s += (z * q);
		d += (z * z);
		b += (q * q);

	}

	sq = sqrt(d * b);

	// Correlation coeff
	r = (s / sq);
	std::cout << "Correlation: " << r << std::endl;

}

void LinearMetrics::rsquare_for_formula() {

	float ytbar = std::accumulate(y_test.begin(), y_test.end(), 0) / y_test.size();
	float z = 0, s = 0;

	for (int i = 0; i < y_test.size(); i++) {

		z += ((yp[i] - y_test[i]) * (yp[i] - y_test[i]));
		s += ((y[i] - ytbar) * (y[i] - ytbar));

	}

	r2f = 1 - (z / s);
	std::cout << "R2: " << r2f << std::endl;

};

void LinearMetrics::rsquare_for_gradient() {

	float numg = 0, deng = 0;
	float y_t_bar = std::accumulate(y_test.begin(), y_test.end(), 0) / y_test.size();

	for (int i = 0; i < x_test.size(); i++) {

		float temp = (x_test[i] * slope) + intercept;
		numg += ((temp - y_test[i]) * (temp - y_test[i]));
		deng += ((y_test[i] - y_t_bar) * (y_test[i] - y_t_bar));

	}

	std::cout << "Gradient Coeff R2: " << 1 - (numg / deng) << std::endl;

};