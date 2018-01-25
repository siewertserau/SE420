#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;


#define EXPECTED_COUNTS (20)
#define ITERATIONS (1000)
#define BINS (50)

static unsigned int randcnt[BINS];


int main(void)
{
    unsigned int seed;
    unsigned int sum=0;
    int diff;
    int bin, idx, jdx;
    double ave=0.0, var=0.0, std=0.0;
    ofstream fout;

    for(idx=0; idx < BINS; idx++) randcnt[idx]=0;

    do
    {
        cout << "Built-in Random number generator with range 0..." << RAND_MAX
             << " will be used in scaled range 0...49\n";
        cout << "Enter a random number seed value between 0 and 49: ";
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
        // for formatting, keep width for output 0...49 to two spaces
        cout.width(2);

        cout << idx << ", " << (randcnt[idx]) << " - ";

        // compute sum and average for each bin
        sum += randcnt[idx];
        ave += ((double)(randcnt[idx]))/((double)BINS);

        for(jdx=0; jdx < BINS; jdx++)  // This assumes that the bin count will be less than BINS
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
        cout << diff;

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
            bin = rand() % BINS; // must remain in range of 0 to 49, so take modulo 50
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

        fout << seed << "," << var << "," << std << "\n";

    }

    fout.close();

    return 0;
}
