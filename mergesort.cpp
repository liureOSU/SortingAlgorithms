#include "mergesort.hpp"

/*----------------------------------------------------------------------
|	Name:	displayVectorRows
|	Input:	const vector<vector<int>>&
|	Output:	void
|	Desc:	Prints the values within input 2D vector.  Gives
|			all values of one row within a printed row.
\*--------------------------------------------------------------------*/
void SortAlgorithm::displayVectorRows(const std::vector<std::vector<int>>& vect) 
{
	for (int i = 0; i < vect.size(); i++) {
		for (int j = 0; j < vect[i].size(); j++) {
			std::cout << vect[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*----------------------------------------------------------------------
|	Name:	outputRows
|	Input:	vector<vector<int>> merge, vector<vector<int>> insert
|	Output:	void
|	Desc:	Prints values of both vector<vector<int>>'s to two output
|			files named 'merge.out' and 'insert.out'.
\*--------------------------------------------------------------------*/
void SortAlgorithm::outputRows(std::vector<std::vector<int>> vector, std::string filename)
{
	std::ofstream output;
	// Place into merge.out
	output.open(filename);
	for (int i = 0; i < vector.size(); i++) {
		for (int j = 0; j < vector.at(i).size(); j++) {
			output << vector.at(i).at(j) << " ";
		}
		output << "\n";
	}
	output.close();
}

/*----------------------------------------------------------------------
|	Name:	outputRows
|	Input:	string fileName
|	Output:	vector<vector<int>>
|	Desc:	Opens a .txt file with the given filename and outputs the
|			integers within into a 2D vector.  Vector is able to take
|			multiple rows within .txt into different vector<int>'s.
\*--------------------------------------------------------------------*/
std::vector<std::vector<int>> SortAlgorithm::readToVector(std::string fileName) 
{
	std::vector<std::vector<int>> vector;
	int nextInt;
	int size;
	std::string nString;
	std::istringstream iss;

	// Open file with user-defined fileName.
	std::ifstream input;
	input.open(fileName);
	if (input) {
		// New line obtained, read into nString then parse using iss into int n.
		while (std::getline(input, nString)) {
			std::vector<int> newRow;
			std::istringstream iss(nString);

			// First number obtained is parsed into dummy integer, size.  Not needed as we work w/vectors.
			bool firstInt = true;
			while (iss) {
				if (firstInt) {
					iss >> size;
					firstInt = false;
				} else {
					// Following numbers are pushed into newRow.
					iss >> nextInt;
					newRow.push_back(nextInt);
				}
			}
			newRow.pop_back();

			// After each row, push into 2D vector.
			vector.push_back(newRow);
		}
	}
	else {
		fileFound = false;
		std::cout << "File could not be opened." << std::endl;
	}
	return vector;
}

/*	Note:
	std::chrono method of measuring run speeds from:
	https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
*/

/*----------------------------------------------------------------------
|	Name:	multiRowMergeSort
|	Input:	vector<vector<int>>*
|	Output:	void
|	Desc:	Performs merge sort on integers within a 2D vector of ints.
|			Integers are passed by pointer, so the vector's elements
|			are permanently sorted.  Uses the mergeSort and merge private
|			member functions to perform sort.
\*--------------------------------------------------------------------*/
void SortAlgorithm::multiRowMergeSort(std::vector<std::vector<int>>* vector)
{
	std::vector<int>* currentRow;

	// Perform merge sort on all i rows within vector<vector<int>>.
	for (int i = 0; i < vector->size(); i++) {
		currentRow = &vector->at(i);
		mergeSort(currentRow, 0, currentRow->size() - 1);
	}
}


/*----------------------------------------------------------------------
|	Name:	merge
|	Input:	vector<int>* currentRow, int first, int split, int last
|	Output:	void
|	Desc:	Private member function.  Performs index swap on vector
|			positions (first ... last) using sub vectors until they are
|			resorted in vector<int> currentRow.
\*--------------------------------------------------------------------*/
void SortAlgorithm::merge(std::vector<int>* currentRow, int first, int split, int last) 
{
	std::vector<int> leftVector;
	std::vector<int> rightVector;
	int leftSize = split - first + 2;
	int rightSize = last - split + 1;

	// Add entries into leftVector.  Save room for sentinel.
	for (int i = 0; i < leftSize - 1; i++) {
		leftVector.push_back(currentRow->at(first + i));
	}

	// Add entries into rightVector.  Save room for sentinel.
	for (int i = 0; i < rightSize - 1; i++) {
		rightVector.push_back(currentRow->at(split + i + 1));
	}

	// Add sentinels.
	leftVector.push_back(INT_MAX);
	rightVector.push_back(INT_MAX);

	// Merge L and R in sorted order.
	int i = 0;
	int j = 0;

	for (int k = first; k <= last; ++k) {
		if (leftVector.at(i) <= rightVector.at(j)) {
			currentRow->at(k) = leftVector.at(i);
			++i;
		} else {
			currentRow->at(k) = rightVector.at(j);
			++j;
		}
	}
}

/*----------------------------------------------------------------------
|	Name:	mergeSort
|	Input:	vector<int>* unsortedRow, int start, int finish
|	Output:	void
|	Desc:	Recursive private member function.  Splits unsortedRow into
|			lg(n) vector<int>'s which are then merged afer base case into
|			a sorted row.
\*--------------------------------------------------------------------*/
void SortAlgorithm::mergeSort(std::vector<int>* unsortedRow, int start, int finish) 
{
	int split;
	if (start < finish) {
		split = (start + finish) / 2;
		mergeSort(unsortedRow, start, split);
		mergeSort(unsortedRow, split + 1, finish);
		merge(unsortedRow, start, split, finish);
	}
}