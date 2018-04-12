/*----------------------------------------------------------------------
|	Class:	SortAlgorithm
|	Author: Reed Liu
|	Desc:	Contains member functions which:
|			1.	Allow .txt input files of form
|
|						[S01 S02 S03 S04 ... S0m]
|						[	 	   ...   	    ]
|						[Sn1 Sn2 Sn3 Sn4 ... Snm]
|
|			with Snm integers (non-square ok) to be placed into a [nxm]
|			2D vector<vector< int >>.
|
|			2.	Allows merge sort to be done on a 2D vector of the above
|				format.
|
|			3.	Outputs the results of merge sort into two
|				file 'merge.out'.
\*--------------------------------------------------------------------*/

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <chrono>

class SortAlgorithm
{
public:
	std::vector<std::vector<int>> readToVector(std::string);
	void multiRowMergeSort(std::vector<std::vector<int>>*);
	void displayVectorRows(const std::vector<std::vector<int>>&);
	void outputRows(std::vector<std::vector<int>>, std::string);
	bool fileFound = true;

private:
	void mergeSort(std::vector<int>*, int, int);
	void merge(std::vector<int>*, int, int, int);
};

