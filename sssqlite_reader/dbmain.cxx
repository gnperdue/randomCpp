#include "db/DBWorker.h"
#include <iostream>


int main(int argc, char * argv[])
{
    DBWorker worker;

    int segment = worker.get_segment_prediction(117200, 12, 167, 1);
    std::cout << segment << std::endl;

	std::vector<double> probs = 
		worker.get_segment_probabilities(117200, 12, 167, 1);
	for (int i = 0; i < 11; ++i) {
		std::cout << "segment " << i << "; p = " << probs[i] << std::endl;
	}

    return 0;
}

