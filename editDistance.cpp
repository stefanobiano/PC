#include <stdio.h>
#include <string>
#include <set>
#include<iostream>
#include <time.h>
using namespace std;


class EditDistance {
    
    private:

    	string firstString;
        string secondString;
    	int firstStringLength;
    	int secondStringLength;
	    int editMatrix[154][154];
    	int i, j;
    	
    public:

    	EditDistance(string firstStringP, string secondStringP) {
		firstString = firstStringP;
		secondString = secondStringP;
		firstStringLength = firstString.size();
		secondStringLength = secondString.size();
	}
	
	int min3(int a, int b, int c) {
		return (a < b ? std::min(a, c) : std::min(b, c));
	}

	int calculate() {

		int i, j;
		for (i = 0; i < firstStringLength + 1; i++) {
			for (j = 0; j < secondStringLength + 1; j++) {
				if (i == 0 || j == 0) {
				    editMatrix[i][j] = std::max(i, j);
				} else {
					editMatrix[i][j] = min3(
							editMatrix[i - 1][j] + 1,
							editMatrix[i][j - 1] + 1,
							editMatrix[i - 1][j - 1] + (firstString.at(i - 1) != secondString.at(j - 1) ? 1 : 0));
				}
			}
		}

		cout << " ";
		cout << "La distanza è " << editMatrix[firstStringLength][secondStringLength];
	    return 0;
	}

};

int main()
{
    EditDistance ed("gagcccgtttcggatattcgcctttcggccaaaaatatggaatttagatagtccttgtgtgcggcctgtcatggttagagccacttagctataggatacccctgccttgcattgcgcggctcctggtgggttcgtaagacgtccaaagagatgc", "gagcccgtttcggatattcgcctttcggccaaaaatatggaatttagatagtccttgtgtgcggcctgtcatggatagagccacttagctataggatacccctgccttgcattgcgcggctcctggtgggttcgtaagacgtccaaagagatgc");
    clock_t tStart = clock();
    ed.calculate();
    cout << "\n";
    printf("Time taken: %.5fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}