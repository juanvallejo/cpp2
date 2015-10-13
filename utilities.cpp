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

// determine if the default input file exists
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

	// read file line by line, split each line by comma
	// convert each comma separated value to integer
	while(std::getline(file, line)) {
		std::vector<std::string> data = str_split(line, ',');
		std::string::size_type sz;

		Measurement measurement;
		measurement.index = std::stoi(data.at(0), &sz);
		measurement.value = std::stoi(data.at(1), &sz);

		statistics.totalMeasurements += 1.0;
		totalValueSum += measurement.value;

		all_data.push_back(measurement);
	}

	// calculate mean
	statistics.mean = totalValueSum / statistics.totalMeasurements;

	return true;
}

// receives a string and a delimiter to split the string by.
// if the string is able to be split, each value is returned
// enclosed in a vector of strings
std::vector<std::string> str_split(std::string& string, const char delim) {

	std::vector<std::string> result;

	std::stringstream stream(string);
	std::string word;

	while(std::getline(stream, word, delim)) {
		result.push_back(word);
	}

	return result;
}

// assumes statistics.totalMeasurements has been calculated
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

// returns the square root of calc_variance()
double stddev() {
	return std::sqrt(calc_variance());
}

// determine which numbers on the list of all_data are outside one standard of deviation
// and which ones fall within
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

bool sort_data_byValue(const Measurement& a, const Measurement& b) {
	return a.value < b.value;
}

void sort_data() {
	std::sort(all_data.begin(), all_data.end(), sort_data_byValue);
}

// print statistics to OUTPUT_FILE
void print_statistics() {

	std::ofstream file(OUTPUT_FILE);

	// output total measurement count to file stream
	file << "Total measurements: " << static_cast<unsigned int>(statistics.totalMeasurements) << std::endl;

	// output mean to file stream
	file << "Mean: ";
	file.precision(3);
	file.width(18);
	file << statistics.mean << std::endl;

	// output standard deviation to file stream
	file << "Standard Deviation: ";
	file.precision(6); 
	file << statistics.stddev << std::endl;

	// output standard deviation outlier amount
	file << "Number witihin 1 standard deviation: " << statistics.totalMeasurements_withinOneStandardDeviation << std::endl;

	for(std::vector<Measurement>::iterator inlier = inlier_data.begin(); inlier != inlier_data.end(); inlier++) {
		file << inlier->index << " , " << inlier->value << std::endl;
	}

	file << "Number outside 1 standard deviation: " << statistics.totalMeasurements_outsideOneStandardDeviation << std::endl;

	for(std::vector<Measurement>::iterator outlier = outlier_data.begin(); outlier != outlier_data.end(); outlier++) {
		file << outlier->index << " , " << outlier->value << std::endl;
	}

}
