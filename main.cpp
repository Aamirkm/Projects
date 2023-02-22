/****************************
 *
 * Program 4: IMDB
 * Course: CS 141, Fall 2022, UIC
 * System: CLion on MacOS
 * Author: Aamir Merchant, helper code provided by Dr. Sara Riazi
 *
 * *** **********************/

#include <iostream>
#include <cctype>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

//Creates struct for title record file
struct TitleRecord{
    string titleID;
    string primaryTitle;
    string startYear;
    string genres;
};
vector<TitleRecord> titleRecord;
TitleRecord nullTitleRecord = {"", "", "", ""};

//Creates struct for name record file
struct NameRecord{
    string nameID;
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
};
vector<NameRecord> nameRecord;
NameRecord nullNameRecord = {"","","","",""};

//Creates struct for principal record file
struct PrincipalRecord{
    string titleID;
    string nameID;
    string character;
    string category;
};
vector<PrincipalRecord> principalRecord;
PrincipalRecord nullPrincipalRecord = {"","","", ""};

vector<string> principalFileLines;
vector<string> nameFileLines;
vector<string> titleFileLines;
string phrase;

/*********************************************** Helper functions ***************************************/

//The splitString function takes a line and split it on the delimiter and push the parts into items
void splitString(string line, char delimiter, vector<string>& items ) {
    stringstream s_stream(line);
    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }
}

/**********************************************************************************************************/
//menu function displays the menu and prompts for choice and phrase
int menu(){
    cout << "Select a menu option:" << endl
         << '\t' << "1. Search for movies" << endl
         << '\t' << "2. Search for actors/actresses" << endl
         << '\t' << "3. Exit" << endl
         << "Your choice --> ";
    int choice;
    cin >> choice;
    if(cin.fail()){
        exit(0);
    }
    if(choice == 3){
        exit(0);
    } else if(choice == 2 || choice == 1){
        cout << "Enter search phrase: ";
        cin >> phrase;
        if(cin.fail()){
            return 0;
        }
    }
    return choice;
} //End menu

//function opens and checks that the files are open
fstream openFiles(string file){

    fstream fileName(file, ios::in);
    if(!fileName.is_open()){
        exit(0);
    }
    return fileName;

} //End openFile function

//The function splits the title file lines and puts them into the structs categories
void splitTitleFileLine(vector<string> splitTitleFileLines){
    int place = 0;
    for(int i = 0; i < titleFileLines.size(); i++){
        splitString(titleFileLines.at(i), '\t', splitTitleFileLines);
        titleRecord.at(i).titleID = splitTitleFileLines.at(place);
        place += 9;
    }
    place = 2;
    for(int i = 0; i < titleFileLines.size(); i++){
        splitString(titleFileLines.at(i), '\t', splitTitleFileLines);
        titleRecord.at(i).primaryTitle = splitTitleFileLines.at(place);
        place += 9;
    }
    place = 5;
    for(int i = 0; i < titleFileLines.size(); i++){
        splitString(titleFileLines.at(i), '\t', splitTitleFileLines);
        titleRecord.at(i).startYear = (splitTitleFileLines.at(place));
        place += 9;
    }
    place = 8;
    for(int i = 0; i < titleFileLines.size(); i++){
        splitString(titleFileLines.at(i), '\t', splitTitleFileLines);
        titleRecord.at(i).genres = (splitTitleFileLines.at(place));
        place += 9;
    }
} //End split function

//The function splits the name file lines and puts them into the structs categories
void splitNameFileLine(vector<string> splitNameFileLines){
    int place = 0;
    for(int i = 0; i < nameFileLines.size(); i++){
        splitString(nameFileLines.at(i), '\t', splitNameFileLines);
        nameRecord.at(i).nameID = splitNameFileLines.at(place);
        place += 6;
    }
    place = 1;
    for(int i = 0; i < nameFileLines.size(); i++){
        splitString(nameFileLines.at(i), '\t', splitNameFileLines);
        nameRecord.at(i).primaryName = splitNameFileLines.at(place);
        place += 6;
    }
    place = 2;
    for(int i = 0; i < nameFileLines.size(); i++){
        splitString(nameFileLines.at(i), '\t', splitNameFileLines);
        nameRecord.at(i).birthYear = splitNameFileLines.at(place);
        place += 6;
    }
    place = 3;
    for(int i = 0; i < nameFileLines.size(); i++){
        splitString(nameFileLines.at(i), '\t', splitNameFileLines);
        nameRecord.at(i).deathYear = splitNameFileLines.at(place);
        place += 6;
    }
    place = 4;
    for(int i = 0; i < nameFileLines.size(); i++){
        splitString(nameFileLines.at(i), '\t', splitNameFileLines);
        nameRecord.at(i).primaryProfession = splitNameFileLines.at(place);
        place += 6;
    }
} //End split function

//The function splits the principal file lines and puts them into the structs categories
void splitPrincipalFileLine(vector<string> splitPrincipalFileLines){
    int place = 0;
    for(int i = 0; i < principalFileLines.size(); i++){
        splitString(principalFileLines.at(i), '\t', splitPrincipalFileLines);
        principalRecord.at(i).titleID = splitPrincipalFileLines.at(place);
        place += 6;
    }
    place = 2;
    for(int i = 0; i < principalFileLines.size(); i++){
        splitString(principalFileLines.at(i), '\t', splitPrincipalFileLines);
        principalRecord.at(i).nameID = splitPrincipalFileLines.at(place);
        place += 6;
    }
    place = 3;
    for(int i = 0; i < principalFileLines.size(); i++){
        splitString(principalFileLines.at(i), '\t', splitPrincipalFileLines);
        principalRecord.at(i).category = splitPrincipalFileLines.at(place);
        place += 6;
    }
    place = 5;
    for(int i = 0; i < principalFileLines.size(); i++){
        splitString(principalFileLines.at(i), '\t', splitPrincipalFileLines);
        principalRecord.at(i).character = splitPrincipalFileLines.at(place);
        place += 6;
    }
} //End split function

//Replaces the commas in genres for movies from the title file with spaces
void replaceComma(){
    for(int i = 0; i < titleRecord.size(); i++){
        while(titleRecord.at(i).genres.find(',') != string::npos) {
            titleRecord.at(i).genres.replace(titleRecord.at(i).genres.find(','),1," ");
        }
    }
}

//displays the found movie information
void displayFoundTitleRecord(vector<TitleRecord> foundTitleRecord){
    for (int i = 0; i < foundTitleRecord.size(); i++) {
        cout << i << ":" << endl
             << "Title: " << foundTitleRecord.at(i).primaryTitle << endl
             << "Year: " << foundTitleRecord.at(i).startYear << endl
             << "Genre: " << foundTitleRecord.at(i).genres << endl
             << "---------------" << endl;
    }
} //End displayFoundTitleRecord

//displays the found actor/actress information
void displayFoundNameRecord(vector<NameRecord> foundNameRecord){
    for (int i = 0; i < foundNameRecord.size(); i++) {
        cout << i << ":" << endl
             << foundNameRecord.at(i).primaryName << endl
             << foundNameRecord.at(i).primaryProfession << endl
             << "(" << foundNameRecord.at(i).birthYear << "-" << foundNameRecord.at(i).deathYear << ")"
             << endl
             << "---------------" << endl;
    }
} //End displayFoundNameRecord

//converts string to lowercase
void toLower(string &phrase){
    for (int i = 0; i < phrase.length(); i++) {
        phrase[i] = tolower(phrase[i]);
    }
} //End toLower

//clears vectors
void clear(vector<TitleRecord> &foundTitleRecord, vector<NameRecord> &foundNameRecord, vector<string> &splitPhrase){
    foundTitleRecord.clear();
    foundNameRecord.clear();
    splitPhrase.clear();
} //End clear

int run(string titlesFile, string namesFile, string principalsFile) {

    int choiceRun = menu();

    fstream titleFile = openFiles(titlesFile);
    fstream nameFile = openFiles(namesFile);
    fstream principalFile = openFiles(principalsFile);

    /*The following three loops place the lines from their files into vectors and adds a null struct into their respective
    * struct vectors so the size of struct vector matches the initial file line size */
    string line;
    getline(titleFile, line);
    while(!titleFile.eof()){
        getline(titleFile, line);
        titleFileLines.push_back(line);
        titleRecord.push_back(nullTitleRecord);
    }

    getline(nameFile, line);
    while(!nameFile.eof()){
        getline(nameFile, line);
        nameFileLines.push_back(line);
        nameRecord.push_back(nullNameRecord);
    }

    getline(principalFile, line);
    while(!principalFile.eof()){
        getline(principalFile, line);
        principalFileLines.push_back(line);
        principalRecord.push_back(nullPrincipalRecord);
    }

    vector<string> splitTitleFileLines;
    splitTitleFileLine(splitTitleFileLines);

    vector<string> splitNameFileLines;
    splitNameFileLine(splitNameFileLines);

    vector<string> splitPrincipalFileLines;
    splitPrincipalFileLine(splitPrincipalFileLines);

    replaceComma();

    string lowercaseTitle;
    string finalPhrase;
    vector<TitleRecord> foundTitleRecord;
    vector<NameRecord> foundNameRecord;
    vector<string> splitPhrase;
    bool checker = false;

    while (choiceRun == 1 || choiceRun == 2) {

        while (finalPhrase != "done") {

            finalPhrase = "";

            if (choiceRun == 1) {

                toLower(phrase);
                splitString(phrase, '+', splitPhrase); //splits entered phrase into parts separated by '+' and places into vector

                for (int i = 0; i < titleRecord.size(); i++) {

                    //makes movie title lowercase to compare with lowercase phrase
                    lowercaseTitle = titleRecord.at(i).primaryTitle;
                    toLower(lowercaseTitle);

                    for (int x = 0; x < splitPhrase.size(); x++) {
                        if (lowercaseTitle.find(splitPhrase.at(x)) != string::npos) {
                            checker = true; //true if part of phrase exists within a title
                        } else {
                            checker = false; //false when part of phrase does not exist within title
                            break;
                        }
                    }
                    if (checker) {
                        //runs when all parts of phrase exist within a title and adds title to a vector of found titles
                        foundTitleRecord.push_back(titleRecord.at(i));
                    }
                }

                //displays message if no titles are found with the search phrase
                if (foundTitleRecord.empty()) {
                    cout << "No match found!" << endl;
                    break;
                }

                displayFoundTitleRecord(foundTitleRecord);

                cout << "Select a movie to see its actors/actresses (-1 to go back to the previous menu): ";
                cin >> choiceRun;
                if (cin.fail()) {
                    exit(0);
                }
                if (choiceRun == -1) {
                    break;
                }

                string choiceTitleID = foundTitleRecord.at(choiceRun).titleID; //selects chosen title
                for (int i = 0; i < principalRecord.size(); i++) {
                    if (principalRecord.at(i).titleID == choiceTitleID) {
                        for (int x = 0; x < nameRecord.size(); x++) {
                            //checks nameID from nameRecord vector and if person is actor/actress displays their name and character
                            if ((nameRecord.at(x).nameID == principalRecord.at(i).nameID) &&
                                ((nameRecord.at(x).primaryProfession.find("actress") != string::npos) ||
                                 (nameRecord.at(x).primaryProfession.find("actor") != string::npos))) {
                                cout << nameRecord.at(x).primaryName << " " << principalRecord.at(i).character
                                     << endl;
                            }
                        }
                    }
                }
                choiceRun = 1;
                cout << "Enter search phrase (type done to go back to the previous menu): ";
                cin >> finalPhrase;
                if (finalPhrase != "done") {
                    phrase = finalPhrase;
                }
            } //End if choice == 1

            if (choiceRun == 2) {

                toLower(phrase);
                splitString(phrase, '+', splitPhrase);//splits entered phrase into parts separated by '+' and places into vector

                for (int i = 0; i < nameRecord.size(); i++) {

                    //makes person name lowercase to compare with lowercase phrase
                    lowercaseTitle = nameRecord.at(i).primaryName;
                    toLower(lowercaseTitle);

                    for (int x = 0; x < splitPhrase.size(); x++) {
                        if (lowercaseTitle.find(splitPhrase.at(x)) != string::npos) {
                            checker = true; //true if part of phrase exists within a name
                        } else {
                            checker = false; //false when part of phrase does not exist within name
                            break;
                        }
                    }
                    if (checker) {
                        //runs when all parts of phrase exist within a name and adds name to a vector of found names
                        foundNameRecord.push_back(nameRecord.at(i));
                    }
                }
                //displays message if no titles are found with the search phrase
                if (foundNameRecord.empty()) {
                    cout << "No match found!" << endl;
                    break;
                }

                displayFoundNameRecord(foundNameRecord);

                cout << "Select an actor/actress to see movies (-1 to go back to the previous menu): ";
                cin >> choiceRun;
                if (cin.fail()) {
                    exit(0);
                }
                if (choiceRun == -1) {
                    break;
                }

                for (int i = 0; i < principalRecord.size(); i++) {
                    //if chosen nameID matches principalRecord nameID prints out the movies, dates, and character of person
                    if (foundNameRecord.at(choiceRun).nameID == principalRecord.at(i).nameID) {
                        for (int x = 0; x < titleRecord.size(); x++) {
                            if (titleRecord.at(x).titleID == principalRecord.at(i).titleID) {
                                cout << titleRecord.at(x).primaryTitle << " "
                                     << titleRecord.at(x).startYear << " "
                                     << principalRecord.at(i).character << endl;
                            }
                        }
                    }
                }
                choiceRun = 2;
                cout << "Enter search phrase (type done to go back to the previous menu): ";
                cin >> finalPhrase;
                if (finalPhrase != "done") {
                    phrase = finalPhrase;
                }
            } //End if choice == 2

            clear(foundTitleRecord, foundNameRecord, splitPhrase);

        } //End while loop for finalPhrase != "done"

        clear(foundTitleRecord, foundNameRecord, splitPhrase);
        choiceRun = menu();
        finalPhrase = "";

    } //End while loop for choice


    return 0;
} //End run

int main() {
    //Change these addresses according to your local machine
    string titlesFile =	"movie.titles.tsv";
    string namesFile = "movie.names.tsv";
    string principalsFile = "movie.principals.tsv";

    //DO NOT change the main function. The main function will be removed by the autograder
    run(titlesFile, namesFile, principalsFile);
    return 0;
}
