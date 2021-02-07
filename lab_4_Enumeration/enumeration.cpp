#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

/* class based around an algorithm that generates every possible WxW matrix configuration where there 
is only 1 X in each row and column, and there E Es, and the rest of the indexes are '.' */
class Enumeration {
    public:
        void enumerate(); //wrapper function for the two level enumeration
        Enumeration(int w, int e, string format);


    private:
        void generateXs(int index); //generates X positions w/ recursion
        void generateEs(int index, int esLeft); //generates E positions w/ recursion
        void Print(); //to print each finishes matrix
        int w; //holds number of rows/cols/Xs in each matrix for class
        int e; //holds number of Es for class
        string format;  //holds how to print the results, 'x' = as matrices where each row of a
                        //matrix is on its own line and each matrix is separated by a space from another
                        //'h' = as numbers where each row computes a hexidecimal number, where
                        //the if the ith index in the row is X or E, the ith bit in the hexidecimal
                        //number is set to 1 and the rest of the bits are 0. 
                        //1 number per line, where each set of numbers is separated
                        //by a space
                        
        vector <string> matrix; //holds the current state of the matrix being generated
        vector <int> xIndexes;  //vector that represents X positions in the matrix, where 
                                //the number represents the column in the matrix and the 
                                //index where the number is represents the row.
};

/* assign class data based on the arguments */
Enumeration::Enumeration(int w, int e, string format) {

    /* generate initial w*w matrix of '.' */
    string line (w, '.');
    int i;
    for(i = 0; i < w; i++) {
        matrix.push_back(line);
    }

    /* enumerate initial xIndexes vector */
    for(i = 0; i < w; i++) {
        xIndexes.push_back(i);
    }
    
    this->w = w;
    this->e = e;
    this->format = format;
}

void Enumeration::Print() {
    int i, j;
    unsigned long long lineNumber; //holds hexidecimal number
    /* print matrices as W lines of W characters held in the matrix followed by a blank line */
    if(format == "x") {
            for(i = 0; i < matrix.size(); i++) {
                for(j = 0; j < matrix.size(); j++) cout << matrix[i][j];
                cout << endl;
            }
            cout << endl;
    }
    /* print each line of the matrix as a hexidecimal number where if the ith index of the line is X, E 
    then the ith bit of the hexidecimal number (lineNumber) is set to 1 and the rest of the bits are 0.
    one number on each line, where each 'matrix' is separated by a space */
    else {
        for(i = 0; i < matrix.size(); i++) {
            lineNumber = 0;
            for(j = 0; j < matrix[i].size(); j++) {
                if(matrix[i][j] == 'E' || matrix[i][j] == 'X') lineNumber |= (1ULL << j);
            }
            printf("%llx\n", lineNumber);
        }
        printf("\n");
    }

}

/* enumerate every possible matrix where there are e Es and 1 X in each row and column
with the rest of the indexes being '.' using n choose k enumeration on previously 
generated matrices containing Xs */
void Enumeration::generateEs(int index, int esLeft) {
    int i, j;
    /* base case, we have no more Es left to place in the matrix, we print the matrix */
    if(esLeft == 0) {
        Print();    
    }
    /* if where reach a point where there are more Es to enumerate than indexes left we return */
    else if((esLeft > ((w * w) - index))) return;
    /* in all other cases call the recursive function to continue the enumeration at the next index,
    both after changing to E at the current index if it doesnt have an X, and not changing to E.
    */
    else { 
        if(matrix[index / this->w][index % this->w] != 'X') {
            matrix[index / this->w][index % this->w] = 'E';
            generateEs(index + 1, esLeft - 1);
            matrix[index / this->w][index % this->w] = '.';
        }
        generateEs(index + 1, esLeft);
    }
}

/* enumerate every matrix where each row and each column contains exactly 1 X using 
recursive permutation algorithm, then call recursvie function to puts the Es in to the matrix */
void Enumeration::generateXs(int index) {
    int temp, i, j;
    /* if we reached the end of xIndexes, put Xs into the matrix where for every ith number in 
    xIndexes an X goes into the ith row of the matrix at the xIndexes[i] column */
    if(index == xIndexes.size()) {
        for(i = 0; i < xIndexes.size(); i++) matrix[i][xIndexes[i]] = 'X';
        generateEs(0, this->e);
        for(i = 0; i < matrix.size(); i++) {
            for(j = 0; j < matrix[i].size(); j++) {
                matrix[i][j] = '.';
            }
        }
    }
    /* if we havent reached the end of the vector, switch the number at index with every number
    from the one at index to the end of xIndexes to generate all generate all permutations
    of xIndexes */
    else {
        for(i = index; i < xIndexes.size(); i++) {
            temp = xIndexes[index];
            xIndexes[index] = xIndexes[i];
            xIndexes[i] = temp;

            generateXs(index + 1);

            temp = xIndexes[index];
            xIndexes[index] = xIndexes[i];
            xIndexes[i] = temp;
        }
    }
}

/* wrapper function for two level enumeration that can be called publicly */
void Enumeration::enumerate() {
    generateXs(0);
}



int main(int argc, char **argv) {

    /* take in command line arguments representing w, e, format to pass to the class */
    int w = atoi(argv[1]);
    int e = atoi(argv[2]);
    string format = argv[3];
    Enumeration en = Enumeration(w, e, format);

    /* perform enumeration of every matrix that can be validly generated accoring to class data */
    en.enumerate();
}