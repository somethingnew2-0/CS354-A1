/* polyeval
 * By Peter Collins and Brennan Schmidt 
 * 
 * Section 2
 *
 * This program takes an input of up to five coefficients and
 * a value for x and caculates the values for the polynomial.
 */
#include <stdio.h>
#include <stdlib.h>

/* Prototypes */
int getXValue(char *argument, int *x);
int storeCoef(char *cmdline[], int numcoef, int coefficients[]);
void printPoly(int coefficients[], int degree);
int evaluate(int coefficients[], int degree, int x);

#define ARRAYSIZE 5

/* Main function for the program. Reads in the values and calls the 
 * other functions to print the equation and evaluate it for the value of x.
 * params: argc - how many arguments are being inputted.
 *         argv[] - array of input coeficients.
 */
int main (int argc, char *argv[]) {
    int coefficients[ARRAYSIZE], x, degree;

    if (getXValue(argv[argc-1], &x) == -1) {
        exit(1);
    }

    degree = storeCoef(argv, argc, coefficients);
    if (degree == -1) {
        exit(1);
    }

    printPoly(coefficients, degree);

    evaluate(coefficients, degree, x);
	return 0;
}

/* getXValue checks the format of "x=<number>" and returns -1 if
 * the format is incorrect, 0 otherwise. It converts the value of x to an 
 * integer and stores it at the location referenced by int *x. 
 * Params: *argument: address of "x=_" from input
 *         *x: address of allocated memory space for the value of x
 */
int getXValue(char *argument, int *x) {
	if (*argument != 'x') {
        printf("Bad command line.\n");
		return -1; 
    }
    argument++;	
    if (*argument != '=') {
        printf("Bad command line.\n");
		return -1;
    }
	argument++;
	*x = atoi(argument); 
	return 0;
}

/* storeCoef checks returns a -1 and prints error message if there are
 * too many or too few coefficients. Returns 0 otherwise. It also converts
 * the coefficients from chars to ints and stores them in coefficients[].
 * Params: *cmdline[]: address of first inputted char to be converted
 *         numcoef: total number of coefficients to be converted
 *         coefficients[]: array for storing the int values of the coefficients
 */
int storeCoef(char *cmdline[], int numcoef, int coefficients[]) {
    if (numcoef < 3) {
        printf("Not enough coefficients.  Bad command line.\n");
        return -1;
    } else if (numcoef > ARRAYSIZE + 2) {
        printf("Too many coefficients.  Bad command line.\n");
        return -1;
    } else {
        int i;
        for (i = 1; i < numcoef - 1; i++) {
            coefficients[i-1] = atoi(cmdline[i]);
        }
        return numcoef - 3;
    }
    return 0;
}

/* printPoly prints the full equation with the coefficients.
 * Params: coefficients[]: array of coefficients to go with powers of x
 *         degree: highest degree of the powers of x
 */
void printPoly(int coefficients[], int degree) {
    printf("Polynomial entered:\n");
    int i;
    i = 0;
	while (degree != 0)	{
	    /* counts down the powers of x and prints them in descending order */
		printf("%dx^%d + ", coefficients[i], degree);
		i++;
		degree--;
	}
	printf("%dx^0\n", coefficients[i]);
	return;
}

/* Evaluate computes the resulting value of plugging in a value (x) for 
 * each x in the equation.
 * Params: coefficients[]: array of coeffients of descending powers of x
 *         degree: highest power of x
 *         x: value to be plugged into each x of the equation.
 */
int evaluate(int coefficients[], int degree, int x) {
    int evaluation, i, currentDegree, currentX;
    evaluation = 0;
    for (i = 0; i < degree + 1; i++) {
		/* computes a numerical value for each power of x and its 
		 * corresponding coefficient */
        currentDegree = degree - i;
        currentX = 1;
        while(currentDegree > 0) {
			/* Multiples x times itself until it equals the correct power */
            currentX *= x;
            currentDegree--;
        }
        evaluation += currentX*coefficients[i];
    } 
    printf("f(%d) = %d\n", x, evaluation);
}
