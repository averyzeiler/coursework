/*
    Name: Avery Zeiler
    Student Number: 400305001
    MacID: zeilera
    Date: March 10, 2022
*/

#include <iostream>
#include <math.h>
using namespace std;

// Define classes here 
class Stats {
    public:
        Stats(int array[], int len);
        virtual ~Stats();
        double getMean();
        double getStDev();
        virtual void computeStats();
        virtual void printStats(); 
    protected:
        int *x;
        int arraylen;
        int max_value;
    private:
        double mean, stdev;
};

Stats::Stats(int array[], int len) {
    //create deep copy of array
    arraylen = len;
    x = new int[len];
    max_value = 0;
    for (int i = 0; i < arraylen; i++) {
        x[i] = array[i];       //copy all elements of array
        if (x[i] > max_value) {
            max_value = x[i];      //store maximum value
        }
    }
    mean = 0.0;
    stdev = 0.0;
}

Stats::~Stats() {
    delete [] x;
}

void Stats::computeStats() {
    //compute mean
    for (int i = 0; i < arraylen; i++) {
        mean += x[i];
    }
    mean /= arraylen;
    //compute standard deviation
    for (int i = 0; i < arraylen; i++) {
        stdev += pow(x[i]-mean, 2);
    }
    stdev = sqrt(stdev/arraylen);
}

void Stats::printStats() {
    //print mean
    cout << "mean = " << mean;
    //print standard deviation
    cout << ", stdev = " << stdev << endl;
}

double Stats::getMean() {
    return mean;
}

double Stats::getStDev() {
    return stdev;
}

class OneVarStats : public Stats {
    public:
        OneVarStats(int array[], int len) : Stats {array, len} {
            //send input array to Stats
            //initialize histogram array
            histLength = 1 + max_value;
            hist = new int[histLength];
            for (int i = 0; i < histLength; i++) {
                hist[i] = 0;
            }
        }
        virtual ~OneVarStats();
        void computeStats();
        void printStats();
    private:
        int histLength;
        int *hist;
};

class TwoVarStats : public Stats {
    public:
        TwoVarStats(int array[], int array2[], int len) : Stats {array, len} {
            //send array1 to stats
            //store a copy of array2
            array2_copy = new int[arraylen];
            for (int i = 0; i < arraylen; i++) {
                array2_copy[i] = array2[i];
            }
            corr = 0.0;
        }
        virtual ~TwoVarStats();
        void computeStats();
        void printStats();
    private:
        double corr;
        int *array2_copy;
};

OneVarStats::~OneVarStats() {
    //Stats::~Stats();
    delete [] hist;
}

TwoVarStats::~TwoVarStats() {
    //Stats::~Stats();
    delete [] array2_copy;
}

void OneVarStats::computeStats() {
    //compute mean + standard deviation
    Stats::computeStats();
    //compute histogram
    for (int i = 0; i < arraylen; i++) {
        hist[x[i]]++;       //increments frequency of element
    }
}

void OneVarStats::printStats() {
    //print mean + standard deviation
    Stats::printStats();
    //print histogram array
    for (int i = 0; i < histLength; i++) {
        cout << hist[i] << " ";
    }
    cout << endl;
}

// the correlation coefficient function 
double computeCorrCoef(int array1[], int array2[], int count) {  // works on array1 and array2 and count
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0;  // hold S(x), S(y), S(xy) respectively.
    double sumX2 = 0.0, sumY2 = 0.0;  // hold S(x^2), S(y^2) respectively.
    
    for (int i=0; i< count; i++){
        sumX += array1[i];
        sumY += array2[i];
        sumXY += array1[i] * array2[i];

        sumX2 += array1[i] *  array1[i];
        sumY2 += array2[i] *  array2[i];
    } 
    double corr_coef = (count * sumXY - sumX * sumY)/ (sqrt((count * sumX2 - sumX * sumX) * (count * sumY2 -  sumY * sumY))); 

    return corr_coef;
}

void TwoVarStats::computeStats() {
    //compute mean + standard deviation for array1
    Stats::computeStats();
    //compute correlation coefficient
    corr = computeCorrCoef(x,array2_copy,arraylen);
}

void TwoVarStats::printStats() {
    //print mean + standard deviation array1
    Stats::printStats();
    //print correlation coefficient
    cout << "corr coef = " << corr << endl;
}

int main( ) {
    //test code here
}