/**
 * project3 - calls functions defined in the 'utilities' header file to read
 * from a default file 'TestData.txt', parse data from it, and perform a
 * statistical analysis on the data, including a standard deviation of the set,
 * the average, and the count.
 *
 * Results are printed to OUTPUT_FILE
 *
 * @author juanvallejo
 */

#include "utilities.h"

int main(int argc, char** argv) {

	std::string filename(INPUT_FILE);

	if(read_inputFile(filename)) {

		if(parse_inputFile(filename)) {
			
			sort_data();

			if(calc_outliers_inliers()) {
				print_statistics();
			} else {
				std::cerr << "ERR no data found to calculate outlier statistics, is the dataset empty?" << std::endl;
			}

		} else {
			std::cerr << "ERR unable to parse / analysize '" <<  filename << "'" << std::endl;
		}

	} else {
		std::cerr << "ERR File '" <<  filename << "' missing" << std::endl;
	}

	return 0;
}