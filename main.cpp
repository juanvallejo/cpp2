/**
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
				std::cout << "ERR no data found to calculate outlier statistics, is the dataset empty?" << std::endl;
			}

		} else {
			std::cout << "ERR unable to parse / analysize '" <<  filename << "'" << std::endl;
		}

	} else {
		std::cout << "ERR File '" <<  filename << "' missing" << std::endl;
	}

	return 0;
}