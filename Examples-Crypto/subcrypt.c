#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET (26)

struct charmap
{
    char alpha;
    char beta;
};

struct charmap submap[ALPHABET] =
{
    {'A','S'}, {'B','A'}, {'C','S'}, {'D','I'}, {'E','J'}, {'F','K'}, {'G','C'},
    {'H','M'}, {'I','Q'}, {'J','R'}, {'K','F'}, {'L','B'}, {'M','D'}, {'N','G'},
    {'O','H'}, {'P','E'}, {'Q','L'}, {'R','O'}, {'S','P'}, {'T','W'}, {'U','T'},
    {'V','Z'}, {'W','Y'}, {'X','V'}, {'Y','U'}, {'Z','X'}
};

char teststr[]="TRANSLATE THIS!";
char inputstr[80];


// This is a slow iterative look-up table that could be
// optimized.

char findbeta(char alpha)
{
    int i;

    for(i=0; i < ALPHABET; i++)
    {
        if(submap[i].alpha == alpha)
            return(submap[i].beta);
    }

    return alpha;
}


void printbeta(char *input, int length)
{
    int i;

    for(i=0; i < length; i++)
    {
        //printf("%c", findbeta(input[i]) );
        printf("%c", findbeta(toupper(input[i])) );
    }

    //printf("\ni=%d\n", i);
}


void main(void)
{
    int i;
    size_t linelen;
    char *line;

    for(i=0; i < ALPHABET; i++)
        printf("%c ", submap[i].alpha);
    printf("\n");

    for(i=0; i < ALPHABET; i++)
        printf("%c ", submap[i].beta);
    printf("\n");

    printf("%s", teststr);
    printf("\n");

    printbeta(teststr, strlen(teststr));
    printf("\n");

    while(strncmp(line, "exit", 4) != 0)
    {    
        printf("\nBETA>");
        getline(&line, &linelen, stdin);
        printf("     ");
        printbeta(line, strlen(line));
    }
    printf("\n");
}
