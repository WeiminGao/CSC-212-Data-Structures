// Provided by:   ____________Weimin Gao__________
// Email Address: _________g1w2m1@gamil.com________
// FILE: Source.cpp
#include <iostream>
#include <assert.h>
#include "stats.h"

using namespace std;
namespace main_savitch_2C 
{ 
	statistician::statistician(){
		count = 0;
		total = 0;
	};
	void statistician::next (double r) {
		if (count == 0) { tinyest = r; largest = r; }
		count++;
		total += r;
		if (tinyest > r) tinyest = r;
		if (largest < r) largest = r;
	};

	double statistician::sum() const {
		return total;
	};

	int statistician::length() const {
		return count;
	};

	void statistician::reset() {
		count = 0; total = 0;
	};

	double statistician::mean() const {
		assert(length() > 0);
		double average;
		average = total / count;
		return average;
	};

	double statistician::minimum() const {
		assert(length() > 0);
		return tinyest;
	};
	double statistician::maximum() const {
		assert(length() > 0);
		return largest;
	};


	statistician operator +(const statistician& s1, const statistician& s2) {
		statistician s3;
		if (s1.count == 0) {
			s3.count = s2.count;
			s3.total = s2.total;
			s3.tinyest = s2.tinyest;
			s3.largest = s2.largest;
		}
		else if (s2.count == 0) {
			s3.count = s1.count;
			s3.total = s1.total;
			s3.tinyest = s1.tinyest;
			s3.largest = s1.largest;
		}
		else {
			s3.count = s1.count + s2.count;
			s3.total = s1.total + s2.total;
			if (s1.tinyest < s2.tinyest) s3.tinyest = s1.tinyest;
			else s3.tinyest = s2.tinyest;
			if (s1.largest > s2.largest) s3.largest = s1.largest;
			else s3.largest = s2.largest;
		}
		return s3;
	};

	statistician operator *(double scale, const statistician& s1) {
		statistician s2;
		double temp;
        
	    s2.count = s1.count;
		s2.total = scale * s1.total;
		s2.tinyest = scale * s1.tinyest;
		s2.largest = scale * s1.largest;
		if (scale < 0) 
			if (s2.tinyest > s2.largest) {
				temp = s2.tinyest;
				s2.tinyest = s2.largest;
				s2.largest = temp;
			}
		return s2;
	};

	bool operator ==(const statistician& s1, const statistician& s2) {
		bool det;
		if (s1.length() == 0 && s2.length() == 0) det = true;
		else if ((s1.length() == s2.length()) && (s1.sum() == s2.sum())
			&& (s1.maximum() == s2.maximum()) && (s1.minimum() == s2.minimum())
			&& (s1.mean() == s2.mean()))
			det = true;
		else
			det = false;
		return det;
			
	};
};
