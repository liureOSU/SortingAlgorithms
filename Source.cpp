#include "mergesort.hpp"

int main()
{
	SortAlgorithm instance;

	std::vector<std::vector<int>> test2Vect = instance.readToVector("data.txt");

	if (instance.fileFound == true) {
		std::cout << "Displaying original vector before merge sorting." << std::endl;
		instance.displayVectorRows(test2Vect);

		std::cout << "Displaying merge-sorted vector." << std::endl;
		instance.multiRowMergeSort(&test2Vect);
		instance.displayVectorRows(test2Vect);

		std::cout << "Results have been placed into merge.out" << std::endl;
		instance.outputRows(test2Vect, "merge.out");
	}
	else {
		std::cout << "File could not be opened! Check that 'data.txt' is in the same directory." << std::endl;
	}
}

