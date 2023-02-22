/**************************
 *
 * Program 1: TwentyFour
 * Course: CS 211, Spring 2023, UIC
 * System: CLion on MacOS
 * Author: Aamir Merchant
 *
 * ************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//gets arguments from command line. Void return type
void getArguments(int argc, char *argv[], int *easy, int *debug) {
    if (argc == 1 || argc == 0) {
        return;
    }
    else {
        while ( (argc -= 2) > 0) {	// while there is another pair of strings
            if (argv[ 1][ 0] != '-') // Invalid syntax, no "-" before option
                return;
            switch (argv[ 1][ 1]) {	// handle options
                case 'd':
                    *debug = atoi( argv[ 2]);
                    break;
                case 'e':
                    *easy = atoi(argv[ 2]);
                    break;
                default:
                    *easy = 1;
                    *debug = 0;
            } // end switch
            argv += 2;	// advance to next pair of command line options
        } //end while
    } //end else
}//end getArguments


//displays welcome message at start of game
void welcome(){
    printf("Welcome to the game of TwentyFour.\n");
    printf("Use each of the four numbers shown below exactly once,\n"
           "combining them somehow with the basic mathematical operators (+,-,*,/)\n"
           "to yield the value twenty-four.\n\n");
} //end welcome


//prints out the 3188 solutions to the game if debug mode is on and places those into an array. Void return type
void debugMode(int (*debugArr)[][4], int debug){
    int count = 1;
    int debugArrCount = 0;

    for(int i = 1; i <= 9; i++){
        for (int j = 1; j <= 9; ++j) {
            for (int k = 1; k <= 9; k++) {
                for (int l = 1; l <= 9 ; ++l) {

                    int index = count;

                    //The lines below go through the different combinations of the operators when there are four
                    //numbers and three operators looking for a solution to the game.
                    // If debug mode is on the equations that equal 24 are printed.
                    int ppp = i + j + k + l;
                    if (ppp == 24) {if(debug == 1){printf("%d. %d+%d+%d+%d\n", count, i, j, k, l);} count++;}
                    int pps = i + j + k - l;
                    if (pps == 24) {if(debug == 1){printf("%d. %d+%d+%d-%d\n", count, i, j, k, l);} count++;}
                    int ppm = (i + j + k) * l;
                    if (ppm == 24) {if(debug == 1){printf("%d. %d+%d+%d*%d\n", count, i, j, k, l);} count++;}
                    double ppd = (double)(i + j + k) / l;
                    if (fabs(ppd - 24) < 0.00001) {if(debug == 1){printf("%d. %d+%d+%d/%d\n", count, i, j, k, l);} count++;}
                    int psp = i + j - k + l;
                    if (psp == 24) {if(debug == 1){printf("%d. %d+%d-%d+%d\n", count, i, j, k, l);} count++;}
                    int pss = i + j - k - l;
                    if (pss == 24) {if(debug == 1){printf("%d. %d+%d-%d-%d\n", count, i, j, k, l);} count++;}
                    int psm = (i + j - k) * l;
                    if (psm == 24) {if(debug == 1){printf("%d. %d+%d-%d*%d\n", count, i, j, k, l);} count++;}
                    double psd = (double )(i + j - k) / l;
                    if (fabs(psd - 24) < 0.00001) {if(debug == 1){printf("%d. %d+%d-%d/%d\n", count, i, j, k, l);} count++;}
                    int pmp = (i + j) * k + l;
                    if (pmp == 24) {if(debug == 1){printf("%d. %d+%d*%d+%d\n", count, i, j, k, l);} count++;}
                    int pms = (i + j) * k - l;
                    if (pms == 24) {if(debug == 1){printf("%d. %d+%d*%d-%d\n", count, i, j, k, l);} count++;}
                    int pmm = (i + j) * k * l;
                    if (pmm == 24) {if(debug == 1){printf("%d. %d+%d*%d*%d\n", count, i, j, k, l);} count++;}
                    double pmd = (double )(i + j) * k / l;
                    if (fabs(pmd - 24) < 0.00001) {if(debug == 1){printf("%d. %d+%d*%d/%d\n", count, i, j, k, l);} count++;}
                    double pdp = (double )(i + j) / k + l;
                    if (fabs(pdp - 24) < 0.00001) {if(debug == 1){printf("%d. %d+%d/%d+%d\n", count, i, j, k, l);} count++;}
                    double pds = (double )(i + j) / k - l;
                    if (fabs(pds - 24) < 0.00001) {if(debug == 1){printf("%d. %d+%d/%d-%d\n", count, i, j, k, l);} count++;}
                    double pdm = (double )(i + j) / k * l;
                    if (fabs(pdm - 24) < 0.00001) {if(debug == 1){printf("%d. %d+%d/%d*%d\n", count, i, j, k, l);} count++;}
                    double pdd = (double )(i + j) / k / l;
                    if (fabs(pdd - 24) < 0.00001) {if(debug == 1){printf("%d. %d+%d/%d/%d\n", count, i, j, k, l);} count++;}

                    int spp = i - j + k + l;
                    if (spp == 24) {if(debug == 1){printf("%d. %d-%d+%d+%d\n", count, i, j, k, l);} count++;}
                    int sps = i - j + k - l;
                    if (sps == 24) {if(debug == 1){printf("%d. %d-%d+%d-%d\n", count, i, j, k, l);} count++;}
                    int spm = (i - j + k) * l;
                    if (spm == 24) {if(debug == 1){printf("%d. %d-%d+%d*%d\n", count, i, j, k, l);} count++;}
                    double spd = (double )(i - j + k) / l;
                    if (fabs(spd - 24) < 0.00001) {if(debug == 1){printf("%d. %d-%d+%d/%d\n", count, i, j, k, l);} count++;}
                    int ssp = i - j - k + l;
                    if (ssp == 24) {if(debug == 1){printf("%d. %d-%d-%d+%d\n", count, i, j, k, l);} count++;}
                    int sss = i - j - k - l;
                    if (sss == 24) {if(debug == 1){printf("%d. %d-%d-%d-%d\n", count, i, j, k, l);} count++;}
                    int ssm = (i - j - k) * l;
                    if (ssm == 24) {if(debug == 1){printf("%d. %d-%d-%d*%d\n", count, i, j, k, l);} count++;}
                    double ssd = (double )(i - j - k) / l;
                    if (fabs(ssd - 24) < 0.00001) {if(debug == 1){printf("%d. %d-%d-%d/%d\n", count, i, j, k, l);} count++;}
                    int smp = (i - j) * k + l;
                    if (smp == 24) {if(debug == 1){printf("%d. %d-%d*%d+%d\n", count, i, j, k, l);} count++;}
                    int sms = (i - j) * k - l;
                    if (sms == 24) {if(debug == 1){printf("%d. %d-%d*%d-%d\n", count, i, j, k, l);} count++;}
                    int smm = (i - j) * k * l;
                    if (smm == 24) {if(debug == 1){printf("%d. %d-%d*%d*%d\n", count, i, j, k, l);} count++;}
                    double smd = (double )(i - j) * k / l;
                    if (fabs(smd - 24) < 0.00001) {if(debug == 1){printf("%d. %d-%d*%d/%d\n", count, i, j, k, l);} count++;}
                    double sdp = (double )(i - j) / k + l;
                    if (fabs(sdp - 24) < 0.00001) {if(debug == 1){printf("%d. %d-%d/%d+%d\n", count, i, j, k, l);} count++;}
                    double sds = (double )(i - j) / k - l;
                    if (fabs(sds - 24) < 0.00001) {if(debug == 1){printf("%d. %d-%d/%d-%d\n", count, i, j, k, l);} count++;}
                    double sdm = (double )(i - j) / k * l;
                    if (fabs(sdm - 24) < 0.00001) {if(debug == 1){printf("%d. %d-%d/%d*%d\n", count, i, j, k, l);} count++;}
                    double sdd = (double )(i - j) / k / l;
                    if (fabs(sdd - 24) < 0.00001) {if(debug == 1){printf("%d. %d-%d/%d/%d\n", count, i, j, k, l);} count++;}

                    int mpp = (i * j) + k + l;
                    if (mpp == 24) {if(debug == 1){printf("%d. %d*%d+%d+%d\n", count, i, j, k, l);} count++;}
                    int mps = (i * j) + k - l;
                    if (mps == 24) {if(debug == 1){printf("%d. %d*%d+%d-%d\n", count, i, j, k, l);} count++;}
                    int mpm = ((i * j) + k) * l;
                    if (mpm == 24) {if(debug == 1){printf("%d. %d*%d+%d*%d\n", count, i, j, k, l);} count++;}
                    double mpd = (double )((i * j) + k) / l;
                    if (fabs(mpd - 24) < 0.00001) {if(debug == 1){printf("%d. %d*%d+%d/%d\n", count, i, j, k, l);} count++;}
                    int msp = (i * j) - k + l;
                    if (msp == 24) {if(debug == 1){printf("%d. %d*%d-%d+%d\n", count, i, j, k, l);} count++;}
                    int mss = (i * j) - k - l;
                    if (mss == 24) {if(debug == 1){printf("%d. %d*%d-%d-%d\n", count, i, j, k, l);} count++;}
                    int msm = ((i * j) - k) * l;
                    if (msm == 24) {if(debug == 1){printf("%d. %d*%d-%d*%d\n", count, i, j, k, l);} count++;}
                    double msd = (double )((i * j) - k) / l;
                    if (fabs(msd - 24) < 0.00001) {if(debug == 1){printf("%d. %d*%d-%d/%d\n", count, i, j, k, l);} count++;}
                    int mmp = (i * j) * k + l;
                    if (mmp == 24) {if(debug == 1){printf("%d. %d*%d*%d+%d\n", count, i, j, k, l);} count++;}
                    int mms = (i * j) * k - l;
                    if (mms == 24) {if(debug == 1){printf("%d. %d*%d*%d-%d\n", count, i, j, k, l);} count++;}
                    int mmm = (i * j) * k * l;
                    if (mmm == 24) {if(debug == 1){printf("%d. %d*%d*%d*%d\n", count, i, j, k, l);} count++;}
                    double mmd = (double )(i * j) * k / l;
                    if (fabs(mmd - 24) < 0.00001) {if(debug == 1){printf("%d. %d*%d*%d/%d\n", count, i, j, k, l);} count++;}
                    double mdp = (double )(i * j) / k + l;
                    if (fabs(mdp - 24) < 0.00001) {if(debug == 1){printf("%d. %d*%d/%d+%d\n", count, i, j, k, l);} count++;}
                    double mds = (double )(i * j) / k - l;
                    if (fabs(mds - 24) < 0.00001) {if(debug == 1){printf("%d. %d*%d/%d-%d\n", count, i, j, k, l);} count++;}
                    double mdm = (double )(i * j) / k * l;
                    if (fabs(mdm - 24) < 0.00001) {if(debug == 1){printf("%d. %d*%d/%d*%d\n", count, i, j, k, l);} count++;}
                    double mdd = (double )(i * j) / k / l;
                    if (fabs(mdd - 24) < 0.00001) {if(debug == 1){printf("%d. %d*%d/%d/%d\n", count, i, j, k, l);} count++;}

                    double dpp = ((1.0*i) / j) + k + l;
                    if (fabs(dpp - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d+%d+%d\n", count, i, j, k, l);} count++;}
                    double dps = ((1.0*i) / j) + k - l;
                    if (fabs(dps - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d+%d-%d\n", count, i, j, k, l);} count++;}
                    double dpm = (((1.0*i) / j) + k) * l;
                    if (fabs(dpm - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d+%d*%d\n", count, i, j, k, l);} count++;}
                    double dpd = (((1.0*i) / j) + k) / l;
                    if (fabs(dpd - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d+%d/%d\n", count, i, j, k, l);} count++;}
                    double dsp = ((1.0*i) / j) - k + l;
                    if (fabs(dsp - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d-%d+%d\n", count, i, j, k, l);} count++;}
                    double dss = ((1.0*i) / j) - k - l;
                    if (fabs(dss - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d-%d-%d\n", count, i, j, k, l);} count++;}
                    double dsm = (((1.0*i) / j) - k) * l;
                    if (fabs(dsm - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d-%d*%d\n", count, i, j, k, l);} count++;}
                    double dsd = (((1.0*i) / j) - k) / l;
                    if (fabs(dsd - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d-%d/%d\n", count, i, j, k, l);} count++;}
                    double dmp = ((1.0*i) / j) * k + l;
                    if (fabs(dmp - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d*%d+%d\n", count, i, j, k, l);} count++;}
                    double dms = ((1.0*i) / j) * k - l;
                    if (fabs(dms - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d*%d-%d\n", count, i, j, k, l);} count++;}
                    double dmm = ((1.0*i) / j) * k * l;
                    if (fabs(dmm - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d*%d*%d\n", count, i, j, k, l);} count++;}
                    double dmd = ((1.0*i) / j) * k / l;
                    if (fabs(dmd - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d*%d/%d\n", count, i, j, k, l);} count++;}
                    double ddp = ((1.0*i) / j) / k + l;
                    if (fabs(ddp - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d/%d+%d\n", count, i, j, k, l);} count++;}
                    double dds = ((1.0*i) / j) / k - l;
                    if (fabs(dds - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d/%d-%d\n", count, i, j, k, l);} count++;}
                    double ddm = ((1.0*i) / j) / k * l;
                    if (fabs(ddm - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d/%d*%d\n", count, i, j, k, l);} count++;}
                    double ddd = ((1.0*i) / j) / k / l;
                    if (fabs(ddd - 24) < 0.00001) {if(debug == 1){printf("%d. %d/%d/%d/%d\n", count, i, j, k, l);} count++;}


                    //if there is a solution with the current four numbers, then they are added to the array
                        while (index != count) {
                            (*debugArr)[debugArrCount][0] = i;
                            (*debugArr)[debugArrCount][1] = j;
                            (*debugArr)[debugArrCount][2] = k;
                            (*debugArr)[debugArrCount][3] = l;
                            debugArrCount++;
                            index++;
                        } //end while

                } //end l
            } //end k
        } //end j
    } //end i

} //end debugMode


//chooses a random row and prints the numbers corresponding to that row in the 2D array for easy mode. Returns the row
int easyMode(int arr[10][4]){
    int row = rand() % 10;
    printf("The numbers to use are: %d, %d, %d, %d.\n", arr[row][0], arr[row][1], arr[row][2], arr[row][3]);
    return row;
} //end easyMode


//chooses a random row and prints the numbers corresponding to that row in the 2D array for hard mode. Returns the row
int hardMode(int arr[3188][4]){
    int row = rand() % 3188;
    printf("The numbers to use are: %d, %d, %d, %d.\n", arr[row][0], arr[row][1], arr[row][2], arr[row][3]);
    return row;
} //end hardMode


//prompts the choosing of three operators, accounts for errors, and returns the three chosen operators as char array
char * chooseOperator(){
    printf("Enter the three operators to be used, in order (+,-,*, or /): ");
    char *operators = malloc(4); //allocates memory for the char array
    scanf("%s", operators);
    //Error for if incorrect amount of operators entered
    if(operators[3] != 0 || operators[2] == 0){
        printf("Error! The number of operators is incorrect. Please try again.\n\n");
        return 0;
    }
    //Error for if wrong operator is entered
    for (int i = 0; i < 3; ++i) {
        if(operators[i] != '+' && operators[i] != '-' && operators[i] != '*' && operators[i] != '/'){
            printf("Error! Invalid operator entered. Please try again.\n\n");
            return 0;
        }
    }
    return operators;
} //end chooseOperator


//calculates the result given the number sequence and chosen operators and outputs to console. Void return type
void calculate(const char *operators, int row, int arr[][4]){
    int first, second, third;

        //The lines below make calculations depending on the first operator chosen and the first two numbers
        if (operators[0] == '+') {
            first = arr[row][0] + arr[row][1];
            printf("%d + %d = %d.\n", arr[row][0], arr[row][1], first);
        } else if (operators[0] == '-') {
            first =  arr[row][0] - arr[row][1];
            printf("%d - %d = %d.\n", arr[row][0], arr[row][1], first);
        } else if (operators[0] == '*') {
            first = arr[row][0] * arr[row][1];
            printf("%d * %d = %d.\n", arr[row][0], arr[row][1], first);
        } else if (operators[0] == '/') {
            first = (double)arr[row][0] / arr[row][1];
            printf("%d / %d = %d.\n", arr[row][0], arr[row][1], first);
        }
        //The lines below make calculations depending on the second operator chosen and the previous calculation and third number
        if (operators[1] == '+') {
            second = first + arr[row][2];
            printf("%d + %d = %d.\n", first, arr[row][2], second);
        } else if (operators[1] == '-') {
            second = first - arr[row][2];
            printf("%d - %d = %d.\n", first, arr[row][2], second);
        } else if (operators[1] == '*') {
            second = first * arr[row][2];
            printf("%d * %d = %d.\n", first, arr[row][2], second);
        } else if (operators[1] == '/') {
            second = (double)first / arr[row][2];
            printf("%d / %d = %d.\n", first, arr[row][2], second);
        }
        //The lines below make calculations depending on the third operator chosen and the previous calculation and fourth number
        if (operators[2] == '+') {
            third = second + arr[row][3];
            printf("%d + %d = %d.\n", second, arr[row][3], third);
        } else if (operators[2] == '-') {
            third = second - arr[row][3];
            printf("%d - %d = %d.\n", second, arr[row][3], third);
        } else if (operators[2] == '*') {
            third = second * arr[row][3];
            printf("%d * %d = %d.\n", second, arr[row][3], third);
        } else if (operators[2] == '/') {
            third = (double)second / arr[row][3];
            printf("%d / %d = %d.\n", second, arr[row][3], third);
        }
        //prints statement depending on result
        if(third == 24){
            printf("Well done! You are a math genius.\n\n");
        } else {
            printf("Sorry. Your solution did not evaluate to 24.\n\n");
        }
} //end calculate


int main(int argc, char *argv[]){

    //default values for easy and debug
    int easy = 1;
    int debug = 0;
    getArguments(  argc, argv, &easy, &debug);

    srand(1);

    welcome();

    //easy mode array
    int arr[10][4] = {
            {3, 9, 4, 1},
            {8, 5, 8, 1},
            {6, 1, 5, 1},
            {2, 8, 7, 8},
            {5, 2, 9, 2},
            {2, 6, 8, 4},
            {5, 5, 4, 3},
            {6, 6, 2, 6},
            {8, 4, 2, 6},
            {6, 2, 8, 1}
    };

    int debugArr[3188][4];
    debugMode(&debugArr, debug);

    int row;
    char playAgain = 'Y';
    while (playAgain != 'N') {

        //if easy mode selected then uses easyMode command otherwise uses hardMode
        if(easy == 1) {
            row = easyMode(arr);
        } else {
            row = hardMode(debugArr);
        }

        char *operators = chooseOperator();
        if(operators == 0){ continue; } //if an error was detected game continues with new numbers

        if(easy == 1) {
            calculate(operators, row, arr);
        } else {
            calculate(operators, row, debugArr);
        }

        free(operators); //frees the char array which was allocated in the chooseOperator function

        printf("Would you like to play again? Enter N for no and any other character for yes. ");
        scanf(" %c", &playAgain);
        printf("\n");

    } //end while

    printf("Thanks for playing!");

    return 0;
} //end main
