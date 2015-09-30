/**
 * Utilities - definition of utility functions
 * @author juanvallejo
 */

#include "utilities.h"

// declare data containers
std::vector<Measurement> all_data;
std::vector<Measurement> outlier_data;
std::vector<Measurement> inlier_data;

// statistical analysis
Statistics statistics;

bool read_inputFile(std::string& filename) {

	std::ifstream file(filename);
	
	if(!file) {
		return false;
	}

	return true;
}

// read file data, calculates amount of measurements and mean
bool parse_inputFile(std::string& filename) {

	// used to calculate mean
	int totalValueSum = 0;

	// initialize statistic counters
	statistics.totalMeasurements 	= 0.0;

	std::ifstream file(filename);
	std::string line;


	while(std::getline(file, line)) {
		std::vector<std::string> data = str_split(line, ',');
		std::string::size_type sz;

		Measurement measurement;
		measurement.index = std::stoi(data.at(0), &sz);
		measurement.value = std::stoi(data.at(1), &sz);

		statistics.totalMeasurements += 1.0;
		totalValueSum += measurement.index;

		all_data.push_back(measurement);
	}

	// calculate mean
	statistics.mean = totalValueSum / statistics.totalMeasurements;

	return true;
}

std::vector<std::string> str_split(std::string& string, const char delim) {

	std::vector<std::string> result;

	std::stringstream stream(string);
	std::string word;

	while(std::getline(stream, word, delim)) {
		result.push_back(word);
	}

	return result;
}

double calc_variance() {

	if(statistics.totalMeasurements == 0 || !statistics.totalMeasurements) {
		return 0.0;
	}

	double squared_meanDifferenceSum = 0.0;

	for(std::vector<Measurement>::iterator measurement = all_data.begin(); measurement != all_data.end(); ++measurement) {
		squared_meanDifferenceSum += std::pow(measurement->value - statistics.mean, 2);
	}

	return squared_meanDifferenceSum / statistics.totalMeasurements;
}

double stddev() {
	return std::sqrt(calc_variance());
}

bool calc_outliers_inliers() {

	if(statistics.totalMeasurements == 0 || !statistics.totalMeasurements) {
		return false;
	}

	// initialize statistical values
	statistics.totalMeasurements_withinOneStandardDeviation 	= 0;
	statistics.totalMeasurements_outsideOneStandardDeviation 	= 0;

	// save stddev to statistics
	statistics.stddev = stddev();

	double topThreshold = statistics.mean + statistics.stddev;
	double bottomThreshold = statistics.mean - statistics.stddev;

	for(std::vector<Measurement>::iterator measurement = all_data.begin(); measurement != all_data.end(); ++measurement) {
		if(measurement->value > bottomThreshold && measurement->value < topThreshold) {
			statistics.totalMeasurements_withinOneStandardDeviation++;
			inlier_data.push_back(*measurement);
		} else {
			statistics.totalMeasurements_outsideOneStandardDeviation++;
			outlier_data.push_back(*measurement);
		}
	}

	return true;
}
