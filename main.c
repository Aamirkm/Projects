/**************************
 *
 * Program 1: Weaver
 * Course: CS 211, Spring 2023, UIC
 * System: CLion on MacOS
 * Author: Aamir Merchant
 *
 * ************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



//displays initial messages at start of game
void welcome(){
    printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
    printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
    printf("Enjoy!\n\n");
}//end welcome()


//displays message and returns the number of letters inputted
int getNumWords(){
    int numLetters = 0;
    printf("How many letters do you want to have in the words? ");
    scanf("%d", &numLetters);
    return numLetters;
}//end getNumWords()


//creates dynamically allocated array and places words from file if matches numLetters
char ** findWords(int numLetters, int *index){

    char** arr = (char**) malloc(sizeof(char*)); //array of char pointers
    arr[0] = (char*)malloc((numLetters + 1) * sizeof(char)); //array of chars within arr

    char filename[] = "words.txt";
    FILE *filePtr  = fopen(filename, "r"); // "r" means we open the file for reading

    // Check that the file was able to be opened
    if(filePtr == NULL) {
        printf("Error: could not open %s for reading\n", filename);
        exit(-1);
    }

    // Read each word from file, and print them one by one
    char inputString[ 81];
    while(fscanf(filePtr, "%s", inputString) != EOF) {
        if(strlen(inputString) == numLetters){ //if length matches numLetters
            strcpy(arr[*index], inputString); //writes the word into 2D array
            (*index)++;

            arr = realloc(arr, (sizeof(char *)) + (sizeof(char *) * (*index))); //grows arr size by one
            arr[*index] = (char *) malloc((numLetters + 1) * sizeof(char)); //grows arr

        }//end if
    }//end while

    free(arr[*index]); //frees the last spot in dynamically allocated array

    printf("Number of %d-letter words found: %d.\n\n" , numLetters, *index);

    // Close the file
    fclose(filePtr);
    return arr;

}//end findWords()


//prompts user for words and then returns the inputted words
char* getWords(char a[]){
    printf("Enter starting and ending words, or 'r' for either for a random word: ");
    scanf(" %[^\n]", a);
    return a;
}//end getWords()


//checks the length of words inputted by user and returns bool value
bool checkWordsLength(char *word1, char *word2, int numLetters){
    char r[81] = "r";
    //returns false if word length does not match numLetters or does not equal "r"
    if(strlen(word1) != numLetters && strcmp(word1, r) != 0){
        printf("Your word, '%s', is not a %d-letter word. Try again.\n", word1, numLetters);
        return false;
    }
    //returns false if word length does not match numLetters or does not equal "r"
    if (strlen(word2) != numLetters && strcmp(word2, r) != 0){
        printf("Your word, '%s', is not a %d-letter word. Try again.\n", word2, numLetters);
        return false;
    }
    return true;
}//end checkWordsLength()


//checks if the words are found in the dictionary text file and returns bool value
bool checkValidDict(char *word1, char *word2, char **wordsArr, int index){
    bool word1bool = false;
    bool word2bool = false;
    //goes through the array of dictionary words
    //if a word matches with the inputted words then bool value changed to true
    for(int i = 0; i < index; i++){
        if(strcmp(wordsArr[i], word1) == 0)
            word1bool = true;
        if(strcmp(wordsArr[i], word2) == 0)
            word2bool = true;
    }

    //if inputted word is "r" then bool value changed to true
    char r[81] = "r";
    if(strcmp(word1, r) == 0)
        word1bool = true;
    if(strcmp(word2, r) == 0)
        word2bool = true;

    //if word bool value still false, message is outputted
    if(!word1bool) {
        printf("Your word, '%s', is not a valid dictionary word. Try again.\n", word1);
        return false;
    }
    if(!word2bool)
        printf("Your word, '%s', is not a valid dictionary word. Try again.\n" , word2);

    return word1bool && word2bool;
}//end checkValidDict()


//checks the length of inputted word and returns bool value
bool checkWordLength(char *inputWord, int numLetters){
    //if string length does not equal numLetters displays message and returns false
    if(strlen(inputWord) != numLetters){
        printf("Your word, '%s', is not a %d-letter word. Try again.\n" , inputWord, numLetters);
        return false;
    }
    return true;
}//end checkWordLength()


//checks if inputted word is in dictionary array and returns bool value
bool checkDict(char *inputWord, char **arr, int index){
    //goes through dictionary array and if match is found returns true
    for(int i = 0; i < index; i++){
        if(strcmp(inputWord, arr[i]) == 0)
            return true;
    }
    //prints message if match is not found and returns false
    printf("Your word, '%s', is not a valid dictionary word. Try again.\n" , inputWord);
    return false;
}//end checkDict()


//checks if exactly one character difference between words and returns bool value
bool checkChange(char *inputWord, char *previousWord, int numLetters){
    int changes = 0;
    //goes through words character by character and adds to count if letter does not match
    for(int i = 0; i < numLetters; i++ ){
        if(inputWord[i] != previousWord[i])
            changes++;
    }
    //if changes is not exactly one displays message and returns false
    if(changes != 1) {
        printf("Your word, '%s', is not exactly 1 character different. Try again.\n" , inputWord);
        return false;
    }
    return true;
}//end checkChange()


int main() {

    srand(1);
    welcome();
    int choice = 0;
    do {
        int numLetters = getNumWords(); //gets number of letters
        int index = 0;
        char **wordsArr = findWords(numLetters, &index); //fills dynamically allocated array

        do {

            char bothWords[81] = "";
            bool correctWords = false;
            char firstWord[81] = "";
            char secWord[81] = "";


            while (!correctWords) {
                getWords(bothWords); //gets inputted words

                char *word1 = strtok(bothWords, " "); //splits bothWords
                char *word2 = strtok(NULL, " "); //splits bothWords

                correctWords = checkWordsLength(word1, word2, numLetters); //checks words lengths
                if (!correctWords) continue;

                correctWords = checkValidDict(word1, word2, wordsArr, index); //check if words are valid dict words

                strcpy(firstWord, word1);
                strcpy(secWord, word2);

            }//end while

            //if either word is "r" then replaces it with random word
            if (strcmp(firstWord, "r") == 0) strcpy(firstWord, wordsArr[rand() % index]);
            if (strcmp(secWord, "r") == 0) strcpy(secWord, wordsArr[rand() % index]);

            printf("Your starting word is: %s.\n", firstWord);
            printf("Your ending word is: %s.\n\n", secWord);

            printf("On each move enter a word of the same length that is at most 1 character different and is also in the dictionary.\n");
            printf("You may also type in 'q' to quit guessing.\n");

            char inputWord[81] = "";
            char startWord[81] = "";
            strcpy(startWord, firstWord);
            correctWords = false;
            int count = 1;

            while ((strcmp(inputWord, secWord) != 0) || !correctWords) {

                printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ", count, firstWord, secWord);
                scanf("%s", inputWord);
                if (strcmp(inputWord, "q") == 0) break;

                correctWords = checkWordLength(inputWord, numLetters); //checks length of word
                if (!correctWords) continue;

                correctWords = checkDict(inputWord, wordsArr, index); //checks if word is in dict
                if (!correctWords) continue;

                correctWords = checkChange(inputWord, firstWord, numLetters); //check if exactly one change
                if (!correctWords) continue;

                strcpy(firstWord, inputWord);
                count++;

            }//end while

            if (strcmp(inputWord, "q") != 0) {
                printf("Congratulations! You changed '%s' into '%s' in %d moves.\n", startWord, secWord, --count);
            }

            //prints options after game ends
            printf("\nEnter: \t1 to play again,\n");
            printf("\t2 to change the number of letters in the words and then play again, or\n");
            printf("\t3 to exit the program.\n");
            printf("Your choice --> ");
            scanf("%d", &choice);

        } while (choice == 1);

        //frees dynamically allocated 2D array
        for (int i = 0; i < index; i++) {
            free(wordsArr[i]);
        }
        free(wordsArr);

    }while(choice == 2);

    printf("\nThanks for playing!\nExiting...");

    return 0;
}