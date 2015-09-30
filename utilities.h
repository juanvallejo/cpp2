#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * Project3 - reads a file "testData.txt" consisting of 
 * measurement numbers and values. Calculates mean, variance,
 * and standard deviation for each value.
 *
 * Notes: Only iterators are used to access content in vectors.
 *
 * @author juanvallejo
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

const std::string INPUT_FILE = "TestData.txt";

/**
 * Holds each measurement index-value pair
 */
struct Measurement {

	int index;
	int value;

	void clear() {
		index = -1;
		value = -1;
	}

};

/**
 * Holds statistical data gathered from input values
 */
struct Statistics {

	double mean;
	double stddev;
	double totalMeasurements;

	int totalMeasurements_withinOneStandardDeviation;
	int totalMeasurements_outsideOneStandardDeviation;

	void clear() {
		mean 											= 0;
		stddev 											= 0.0;
		totalMeasurements 								= 0.0;
		totalMeasurements_withinOneStandardDeviation 	= 0;
		totalMeasurements_outsideOneStandardDeviation 	= 0;
	}

};

// vector holding all Measurements
extern std::vector<Measurement> all_data;

// vector holding all Measurements outside of one standard deviation
extern std::vector<Measurement> outlier_data;

// data that lies within one standard deviation
extern std::vector<Measurement> inlier_data;

/**
 * Checks to see if input file exists, calls read_inputFile
 */
bool read_inputFile(std::string& filename);

/**
 * Parses an input stream
 */
bool parse_inputFile(std::string& filename);

/**
 * split a string by the specified delimeter and return a vector
 */
std::vector<std::string> str_split(std::string& string, const char delim);

/**
 * calculate the variance of the dataset
 */
double calc_variance(void);

/**
 * Returns the standard deviation of the current data based on a calculated standard deviation
 * Depends on calc_variance(void)
 */
double stddev(void);

/**
 * Extracts data from the global dataset that lies within one measurement of the data's
 * standard deviation
 * Requires stddev
 */
bool calc_outliers_inliers(void);

/**
 * Prints formatted output to stdout
 */
void print_statistics(void);

/**
 * Sort vector of Measurements
 */
bool sort_data_byValue(const Measurement& a, const Measurement& b);
void sort_data(void);

#endif