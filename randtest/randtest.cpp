#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using namespace std;


#define ITERATIONS (10000)
#define BINS (100)

// Assuming a uniform, equiprobable distribution of outcomes
#define EXPECTED_COUNTS (ITERATIONS/BINS)

static unsigned int randcnt[BINS];


int main(void)
{
    unsigned int seed;
    unsigned int sum=0;
    int diff;
    int bin, idx, jdx, histLength;
    double ave=0.0, var=0.0, std=0.0;
    ofstream fout;

    histLength = (int)(1.3 * EXPECTED_COUNTS);

    for(idx=0; idx < BINS; idx++) randcnt[idx]=0;

    do
    {
        cout << "Built-in Random number generator with range 0..." << RAND_MAX
             << " will be used in scaled range 0..." << BINS << "\n";
        cout << "Enter a random number seed value between 0 and " << BINS << ": ";
        cin >> seed;
        if(seed >= BINS) cerr << "ERROR - seed value out of range\n";

    } while (seed >= BINS);

    // Set the seed for this test
    srand(seed);

    for(idx=0; idx < ITERATIONS; idx++)
    {
        bin = rand() % BINS; // must remain in range of 0 to 49, so take modulo 50
        (randcnt[bin])++;
        // cout << "bin=" << bin << ", " << (randcnt[bin]) << "\n";
    }


    // Produce the ASCII histogram and statistics for this seed
    for(idx=0; idx < BINS; idx++)
    {
        // for formatting, keep width for output 000...999 to three spaces
        cout.width(3);

        cout << right << setw(3) << idx << ", " << right << setw(3) << (randcnt[idx]) << " - ";

        // compute sum and average for each bin
        sum += randcnt[idx];
        ave += ((double)(randcnt[idx]))/((double)BINS);

        // This assumes that the bin count will be less than 2 x EXPECTED_COUNT
        for(jdx=0; jdx < histLength; jdx++)
        {
            if(((unsigned int)jdx) < (randcnt[idx]))
                cout << "*";
            else
                cout << " ";
        }

        // we expect 20 counts, so diff is actual counts - 20
        diff = (randcnt[idx]) - EXPECTED_COUNTS;

        // Compute difference from mean and square it and average over all bins
        var += ((double)(diff*diff)) / ((double)BINS);
        cout << right << setw(4) << diff;

        cout << "\n";
    }


    std = sqrt(var);

    // Output of overall distribution standard deviation and Excel plot output for all
    // seeds between 0 ... BINS

    cout << "\nSum of all counts in all bins is " << sum 
         << ", ave=" << ave << ", var=" << var 
         << ", std=" << std << "\n";

    // Output a file with CSV list of seed and variance, std-deviation for plotting
    fout.open("randstats.txt");
    fout << "seed" << "," << "var" << "," << "std" << "\n";

    for(seed=0; seed < BINS; seed++)
    {
        srand(seed);

        for(idx=0; idx < BINS; idx++) randcnt[idx]=0;
            sum=0, ave=0.0, diff=0, var=0.0;

        for(idx=0; idx < ITERATIONS; idx++)
        {
            bin = rand() % BINS; // must remain in range of 0 to BINS, so take modulo BINS
            (randcnt[bin])++;
        }

        for(idx=0; idx < BINS; idx++)
        {
            sum += randcnt[idx];
            ave += ((double)(randcnt[idx]))/((double)BINS);
            diff = (randcnt[idx]) - EXPECTED_COUNTS;
            var += ((double)(diff*diff)) / ((double)BINS);
        }

        std = sqrt(var);

        fout << seed << "," << ave << "," << var << "," << std << "\n";

    }

    fout.close();

    return 0;
}
