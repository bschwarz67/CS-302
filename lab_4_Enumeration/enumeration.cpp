//TODO tweak second level enumeration a bit, what about resetting bit strings?, 
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Enumeration {
    public:
        void enumerate();
        Enumeration(int w, int e, string format);


    private:
        void enumerateXs(int index);
        void enumerateEs(int index, int esLeft);
        int w;
        int e;
        string format;
        vector <string> matrix;
        vector <int> xIndexes;
        vector <int> eIndexes;

};


Enumeration::Enumeration(int w, int e, string format) {
    string line (w, '.');
    int i;
    for(i = 0; i < w; i++) {
        matrix.push_back(line);
    }
    for(i = 0; i < w; i++) {
        xIndexes.push_back(i);
    }
    for(i = 0; i < w * w; i++) {
        eIndexes.push_back(0);
    }
    this->w = w;
    this->e = e;
    this->format = format;
}

void Enumeration::enumerateEs(int index, int esLeft) {
    int i, j;
    unsigned long long lineNumber;
    if(esLeft == 0) {
        for(i = 0; i < eIndexes.size(); i++) {
            if(eIndexes[i] == 1) {
                if(matrix[i / this->w][i % this->w] != 'X') matrix[i / this->w][i % this->w] = 'E';
                else {
                    for(i = 0; i < matrix.size(); i++) {
                        for(j = 0; j < matrix[i].size(); j++) {
                            if(matrix[i][j] == 'E') matrix[i][j] = '.';
                        }
                    }
                    return;
                }
            }
        }
        

        if(format == "x") {
            for(i = 0; i < matrix.size(); i++) {
                for(j = 0; j < matrix.size(); j++) cout << matrix[i][j];
                cout << endl;
            }
            cout << endl;
        }
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


        for(i = 0; i < matrix.size(); i++) {
            for(j = 0; j < matrix[i].size(); j++) {
                if(matrix[i][j] == 'E') matrix[i][j] = '.';
            }
        }
        
        
    }
    else {
        if(esLeft > eIndexes.size() - index) return;
        eIndexes[index] = 1;
        enumerateEs(index + 1, esLeft - 1);
        eIndexes[index] = 0;
        enumerateEs(index + 1, esLeft);

    }
}

void Enumeration::enumerateXs(int index) {
    int temp, i, j;
    if(index == xIndexes.size()) {
        for(i = 0; i < xIndexes.size(); i++) matrix[i][xIndexes[i]] = 'X';
        //for(i = 0; i < matrix.size(); i++) cout << matrix[i] << endl;
        //cout << endl;
        enumerateEs(0, this->e);
        for(i = 0; i < matrix.size(); i++) {
            for(j = 0; j < matrix[i].size(); j++) {
                matrix[i][j] = '.';
            }
        }
    }
    else {
        for(i = index; i < xIndexes.size(); i++) {
            temp = xIndexes[index];
            xIndexes[index] = xIndexes[i];
            xIndexes[i] = temp;

            enumerateXs(index + 1);

            temp = xIndexes[index];
            xIndexes[index] = xIndexes[i];
            xIndexes[i] = temp;
        }
    }
}

void Enumeration::enumerate() {
    enumerateXs(0);
}



int main(int argc, char **argv) {
    int w = atoi(argv[1]);
    int e = atoi(argv[2]);
    string format = argv[3];
    Enumeration en = Enumeration(w, e, format);
    en.enumerate();

}

