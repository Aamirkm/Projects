/****************************
 *
 * Program 3: Password Checker
 * Course: CS 141, Fall 2022, UIC
 * System: CLion on MacOS
 * Author: Aamir Merchant, starter code provided by Dr. Sara Riazi
 *
 * *** **********************/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


const string rule_msg_1 = "The selected password must be at least eight characters long.";
const string rule_msg_2 = "The selected password must have at least one uppercase letter.";
const string rule_msg_3 = "The selected password must have at least one lowercase letter.";
const string rule_msg_4 = "The selected password must have at least one digit.";
const string rule_msg_5 = "The selected password must have at least one of special characters: [@,!,#,^,&,*,$]";
const string rule_msg_6 = "The selected password has been leaked.";
const string rule_msg_7 = "The selected password cannot contain a dictionary word.";
const int wordsTotal = 345618;

//Used when parsing through the leaked password file in binary search to make comparison easier
//Returns the leaked password without special characters
string RemoveSpecialChar(string x) {
    for (int i = x.length() - 1; i > -1; i--) {
        if (x.at(i) == 64 || x.at(i) == 33 || x.at(i) == 35 ||
            x.at(i) == 94 ||
            x.at(i) == 38 || x.at(i) == 42 || x.at(i) == 36) {
            x.erase(i, 1);
        }
    } //End for loop
    return x;
} //End RemoveSpecialChar

/****
 * Runs the main part of the program
 ****/
void run(string leaked_password_file, string english_word_file) {

    string password;
    cout << "Enter password: ";
    cin >> password;
    string alphaOnlyPass = password; //Password with only alphabetical characters
    string alphaNumPass = password; //Password without special characters
    //Rule 1
    if (password.length() < 8) {
        cout << rule_msg_1 << endl;
    }
    //Rule 2
    bool containsUppercase = false;
    for (int i = 0; i < password.length(); i++) {
        if (password.at(i) > 64 && password.at(i) < 91) {
            containsUppercase = true;
        }
    }
    if (!containsUppercase) {
        cout << rule_msg_2 << endl;
    }
    //Rule 3
    bool containsLowercase = false;
    for (int i = 0; i < password.length(); i++) {
        if (password.at(i) > 96 && password.at(i) < 123) {
            containsLowercase = true;
        }
    }
    if (!containsLowercase) {
        cout << rule_msg_3 << endl;
    }
    //Rule 4
    bool containsDigit = false;
    for (int i = 0; i < password.length(); i++) {
        if (password.at(i) > 47 && password.at(i) < 58) {
            containsDigit = true;
        }
    }
    if (!containsDigit) {
        cout << rule_msg_4 << endl;
    }
    //Rule 5
    bool containsSpecialChar = false;
    for (int i = 0; i < password.length(); i++) {
        if (password.at(i) == 64 || password.at(i) == 33 || password.at(i) == 35 || password.at(i) == 94 ||
            password.at(i) == 38 || password.at(i) == 42 || password.at(i) == 36) {
            containsSpecialChar = true;
        }
    }
    if (!containsSpecialChar) {
        cout << rule_msg_5 << endl;
    }

    bool isNotWord = true;
    bool isNotLeakedPass = true;
    //Imports input from the two text files
    fstream myLeakedFile(leaked_password_file, ios::in);
    fstream myWordFile(english_word_file, ios::in);
    //Checks to make sure first five rules pass before creating vectors for the dictionary words and leaked passwords file
    if (containsDigit && containsLowercase && containsSpecialChar && containsUppercase && password.length() >= 8) {
        vector<string> wordsVector(wordsTotal);
        for (int i = 0; i < wordsTotal; i++) {
            getline(myWordFile, wordsVector.at(i)); //Adds each line of string into the vector
        }
        //Puts leaked password text file lines into vector
        vector<string> leakedVector(0);
        string line;
        while(!myLeakedFile.eof()){
            getline(myLeakedFile, line);
            leakedVector.push_back(line);
        }
        leakedVector.resize(leakedVector.size()-1);
        //Removes special characters from password
        for (int i = alphaOnlyPass.length() - 1; i > -1; i--) {
            if (alphaOnlyPass.at(i) == 64 || alphaOnlyPass.at(i) == 33 || alphaOnlyPass.at(i) == 35 ||
                alphaOnlyPass.at(i) == 94 ||
                alphaOnlyPass.at(i) == 38 || alphaOnlyPass.at(i) == 42 || alphaOnlyPass.at(i) == 36) {
                alphaOnlyPass.erase(i, 1);
                alphaNumPass.erase(i,1);
            }
        }
        //Removes numbers from password
        for (int i = alphaOnlyPass.length() - 1; i > -1; i--) {
            if (alphaOnlyPass.at(i) > 47 && alphaOnlyPass.at(i) < 58) {
                alphaOnlyPass.erase(i, 1);
            }
        }
        //Makes variable lowercase
        for (int i = 0; i < alphaOnlyPass.length(); i++){
            alphaOnlyPass[i] = tolower(alphaOnlyPass[i]);
        }

        for (int i = 0; i < alphaNumPass.length(); i++){
            alphaNumPass[i] = tolower(alphaNumPass[i]);
        }
        //Binary search through leaked password file for password
        int low1, mid1, high1;
        low1 = 0;
        high1 = leakedVector.size() - 1;
        while (low1 <= high1) {
            mid1 = (low1 + high1) / 2;
            if (alphaNumPass == RemoveSpecialChar(leakedVector.at(mid1))) { //Compares password to leaked password file without special character
                cout << rule_msg_6 << endl;
                isNotLeakedPass = false;
                break;
            } else if (alphaNumPass < RemoveSpecialChar(leakedVector.at(mid1))) {
                high1 = mid1 - 1;
            } else {
                low1 = mid1 + 1;
            }
        } //End while loop
        //Binary search through words text file for password
        if (alphaOnlyPass.length() > 4) { //Makes sure the word is greater than four characters to qualify rule 7
            int low, mid, high;
            low = 0;
            high = wordsTotal - 1;
            while (low <= high) {
                mid = (low + high) / 2;
                if (alphaOnlyPass == wordsVector.at(mid)) {
                    cout << rule_msg_7 << endl;
                    isNotWord = false;
                    break;
                } else if (alphaOnlyPass < wordsVector.at(mid)) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } //End while loop
        }
    } //Ends if-statement making sure rule 1-5 are satisfied
    //Accepts password if all rules are satisfied
    if (containsDigit && containsLowercase && containsSpecialChar && containsUppercase && password.length() >= 8 && isNotWord && isNotLeakedPass){
        cout << "Password accepted!" << endl;
    }

} //End run function


int main() {
    /** Change the address of the files appropriatly based on your local machine.
     * This main function will be replaced during testing. Do not add any line of code to the main function
     **/
    string leaked_password_file = "LeakedPswd.txt"; //change this based on the location of the file on your machine
    string english_word_file = "words.txt"; //change this based on the location of the file on your machine
    run(leaked_password_file, english_word_file);

    return 0;
}