/****************************
 *
 * Program 1: Gerrymandering
 * Course: CS 251, Spring 2023, UIC
 * System: CLion on MacOS
 * Author: Aamir Merchant
 *
 * *** **********************/

#include "ourvector.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;


//struct alias used within gerrymander struct ourvector variable for locations' district information
struct district{
    int districtNum;
    int democratVotes;
    int republicanVotes;
}; //end district
//struct alias to store locations' information
struct gerrymander{
    string location;
    int eligibleVoters{};
    ourvector<struct district> districtVector{};
}; //end gerrymander


//turns string into all lowercase and returns lowercase string
string tolower(string x){
    for(char & i : x){
        i = tolower(i);
    }
    return x;
} //end tolower


//replaces all commas within a passed by reference line with spaces and counts num of districts using num of commas
void replaceCommas(string &line, int &count){
    count = 0;
    //replaces instances of "AL" with "1" for district numbers where "AL" is used instead
    if(line.substr(line.find(',') + 1, 2) == "AL"){
        line.replace(line.find(',') + 1, 2, "1");
    }
    //replaces instances of commas with spaces
    for(uint i = 0; i < line.length(); i++ ){
        if (line[i] == ','){
            line.replace(i, 1, " ");
            count++;
        } //end if statement
    } //end for-loop
} //end replaceCommas


//splits district lines into district num, democrat votes, and republican votes and places them into proper
//variable for district struct within the gerryVector ourvector. Does not return a value instead uses pass by reference
void splitString(string &line, ourvector<struct gerrymander>& gerryVector, int vectorLoc){
    stringstream stream;
    line = line.substr(line.find('1')); //removes the location name from line
    int x;
    stream << line;
    int count = 0;
    //there are three variables repeating every three words. Using modulus operator every third word is placed into
    //its correct spot within the districtVector ourvector
    while(stream >> x){
        if(count % 3 == 0){
            //assigns the locations in the gerryVector with proper district number in correct index of districtVector
            gerryVector.at(vectorLoc).districtVector.at(count/3).districtNum = x;
        } else if(count % 3 == 1){
            //assigns the location in gerryVector with proper dem votes number in correct district of districtVector
            gerryVector.at(vectorLoc).districtVector.at(count/3).democratVotes = x;
        } else {
            //assigns the location in gerryVector with proper rep votes number in correct district of districtVector
            gerryVector.at(vectorLoc).districtVector.at(count/3).republicanVotes = x;
        }
        count ++;
    } //end while
} //end splitString


//opens and reads the district file into gerryVector and outputs the number of districts. Does not have return value
//instead uses pass by reference for parameters
void loadDistrict(const string &command, ourvector<struct gerrymander> &gerryVector, bool &dataLoaded, bool &dataAlreadyLoaded){
    //checks if data has already been loaded
    if(dataLoaded){
        cout << "Already read data in, exit and start over." << endl << endl;
        dataAlreadyLoaded = true;
        return;
    }
    //gets name of district file
    string districtTextFile = command.substr(command.find(' ')+1, command.find(".txt")-1);
    fstream districtFile;
    //opens and checks if district file is open
    districtFile.open(districtTextFile);
    if(!districtFile.is_open()){
        cout << "Invalid first file, try again." << endl << endl;
        dataLoaded = false;
        return;
    } else {
        cout << "Reading: " << districtTextFile << endl;
        dataLoaded = true;
    }

    string line;
    gerrymander gerry;
    district districtStruct{};
    int count = 0;
    //while loop goes through district file line by line
    while(!districtFile.eof()){
        getline(districtFile, line);
        if(line.empty()){return;} //skips last line of file if empty
        int numOfDistricts = 0;
        gerryVector.push_back(gerry); //pushes back a struct into gerryVector for every line of district file
        gerryVector.at(count).location = line.substr(0, line.find(',')); //adds location gerryVector
        replaceCommas(line, numOfDistricts); //replaces commas with spaces and also retrieve number of districts
        for(int i = 0; i < numOfDistricts/3; i++) {
            //pushes back correct amount of structs at each index of gerryVector for districtStruct vector
            gerryVector.at(count).districtVector.push_back(districtStruct);
        } //end for-loop
        splitString(line, gerryVector, count);
        cout << "..." << gerryVector.at(count).location << "..." << numOfDistricts/3 << " districts total" << endl;
        count++;
    } //end while
    districtFile.close();
} //end loadDistrict


//opens and reads the eligible file into gerryVector and outputs the number eligible voters. Does not have return value
//instead uses pass by reference for parameters
void loadEligible(const string& command, ourvector<struct gerrymander>& gerryVector, bool &dataLoaded, bool &dataAlreadyLoaded){
    //checks to see if data has already been loaded
    if(!dataLoaded){return;}
    if(dataAlreadyLoaded){return;}
    string eligibleTextFile = command.substr(command.find(".txt ")+5); //gets name of eligible text file
    fstream eligibleFile;
    //checks to see if file has been opened or not
    eligibleFile.open(eligibleTextFile);
    if(!eligibleFile.is_open()){
        cout << "Invalid second file, try again." << endl << endl;
        dataLoaded = false;
        return;
    } else {
        cout << "Reading: " << eligibleTextFile << endl;
    }

    string line;
    bool locMatch = false;
    //reads through eligible file line by line
    while(!eligibleFile.eof()) {
        getline(eligibleFile, line);
        if (line.empty()) { return; } //accounts for last line of file being empty
        int eligibleVoterNum = stoi(line.substr(line.find(',') + 1)); //turn eligible voter string to int
        string eligibleVoterLoc = line.substr(0, line.find(',')); //finds loc of matched eligible voter int
        for(auto & i : gerryVector){
            //if location of gerryVector index matches eligibleVoterLoc then eligibleVoterNum is initialized at index
            if(i.location == eligibleVoterLoc){
                i.eligibleVoters = eligibleVoterNum;
                locMatch = true;
            }
        } //end for-loop
        if(locMatch) {
            //outputs eligible voter file information
            cout << "..." << eligibleVoterLoc << "..." << eligibleVoterNum << " eligible voters" << endl;
        }
        locMatch = false;
    } //end while
    eligibleFile.close();
} //end loadEligible


//searches for index of searched for location by user within the gerryVector ourvector. Does not return value instead
//uses pass by reference
void search(const string& command, ourvector<struct gerrymander>& gerryVector, string &currLocation, bool &dataLoaded, int &indexOfLocation){
    string state = command.substr(command.find(' ') + 1); //stores location name
    state = tolower(state);
    indexOfLocation = -1;
    //iterates through gerryVector looking for index where inputted location matches
    for(int i = 0; i < gerryVector.size(); i++){
        string loc = tolower(gerryVector.at(i).location);
        if(state == loc){
            indexOfLocation = i;
        }
    } //end for-loop
    //checks if index was found or not
    if(!dataLoaded && indexOfLocation == -1) {
        cout << "No data loaded, please load data first." << endl << endl;
        return;
    } else if(indexOfLocation == -1){
        cout << "State does not exist, search again." << endl << endl;
    } else {
        currLocation = gerryVector.at(indexOfLocation).location;
    }
} //end search


//calculates and outputs statistics for current location. Void return type but uses pass by ref
void stats(int &indexOfLoc, ourvector<struct gerrymander>& gerryVector, bool &dataLoaded){
    //checks to see if data has been loaded already
    if(!dataLoaded){
        cout << "No data loaded, please load data first." << endl << endl;
        return;
    }
    if(indexOfLoc == -2){
        cout << "No state indicated, please search for state first." << endl << endl;
        return;
    }

    //declares variables for statistics
    int totalVotes = 0, wastedDemVotes = 0, wastedRepVotes = 0, overHalf, totalDemVotes = 0;
    double efficiencyGap;
    //iterates through districts of selected location in the district vector and collects statistics
    for(auto & i : gerryVector.at(indexOfLoc).districtVector){
        int demVotes = i.democratVotes;
        int repVotes = i.republicanVotes;
        totalVotes += (demVotes + repVotes); //counts total votes of location
        totalDemVotes += demVotes;
        overHalf = (demVotes + repVotes)/2 + 1; //calculates overHalf
        //calculates wasted votes
        if(demVotes > repVotes){
            wastedDemVotes += (demVotes - overHalf);
            wastedRepVotes += repVotes;
        } else {
            wastedRepVotes += (repVotes - overHalf);
            wastedDemVotes += demVotes;
        }
    } //end for-loop
    efficiencyGap = 100*(double((abs(wastedDemVotes - wastedRepVotes)))/totalVotes); //calculates efficiency gap
    int numOfDistricts = gerryVector.at(indexOfLoc).districtVector.size();
    string loser;
    if(totalVotes - totalDemVotes < totalDemVotes){
        loser = "Republicans";
    } else {
        loser = "Democrats";
    }
    //outputs statistics
    if(efficiencyGap < 7 || numOfDistricts < 3){
        cout << "Gerrymandered: No" << endl;
    } else {
        cout << "Gerrymandered: Yes" << endl
             << "Gerrymandered against: " << loser << endl
             << "Efficiency Factor: " << setprecision(6) << efficiencyGap << "%" << endl;
    }
    cout << "Wasted Democratic votes: " << wastedDemVotes << endl
         << "Wasted Republican votes: " << wastedRepVotes << endl
         << "Eligible voters: " << gerryVector.at(indexOfLoc).eligibleVoters
         << endl << endl;
} //end stats


//outputs a text based histogram to visualize votes within district. Void return type using pass by ref parameters
void plot(int &indexOfLoc, ourvector<struct gerrymander>& gerryVector, bool &dataLoaded){
    //checks if data has been loaded
    if(!dataLoaded){
        cout << "No data loaded, please load data first." << endl << endl;
        return;
    }
    //iterates through districtVector at given index of gerryVector calculating and outputting district votes
    for (auto & i : gerryVector.at(indexOfLoc).districtVector) {
        double demVotesPercent = 100*(double(i.democratVotes)/(i.democratVotes + i.republicanVotes));
        int demVotes = int(demVotesPercent);
        //outputs text based histogram
        cout << "District: " << i.districtNum << endl;
        for(int i = 0; i < demVotes; i++){
            cout << "D";
        }
        for(int i = 0; i < 100-demVotes; i++){
            cout << "R";
        }
        cout << endl;
    } //end for-loop
} //end plot


//prompts the user to input a command and returns the command as a string
string prompt(const bool &dataLoaded, const bool &locationLoaded, string &location){
    cout << "Data Loaded? ";
    if(dataLoaded){
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    cout << "State: ";
    if(locationLoaded){
        cout << location << endl;
    } else {
        cout << "N/A" << endl;
    }

    string command;
    cout << endl << "Enter command: ";
    getline(cin, command);
    cout << endl << "-----------------------------" << endl << endl;
    return command;
} //end prompt


//takes user prompted command and calls the corresponding function. Void return type uses pass by ref parameters
void findCommand(const string& command, ourvector<struct gerrymander>& gerryVector, bool& dataLoaded, string &currLocation, int &indexOfLoc){
    string firstCommandWord = command.substr(0,command.find(' ')); //gets command word
    bool dataAlreadyLoaded = false;

    //matches command to function
    if(firstCommandWord == "load"){
        loadDistrict(command, gerryVector, dataLoaded, dataAlreadyLoaded);
        cout << endl;
        loadEligible(command, gerryVector, dataLoaded, dataAlreadyLoaded);
    } else if(firstCommandWord == "search"){
        search(command, gerryVector, currLocation, dataLoaded, indexOfLoc);
    } else if(firstCommandWord == "plot"){
        plot(indexOfLoc, gerryVector, dataLoaded);
    } else if(firstCommandWord == "stats"){
        stats(indexOfLoc, gerryVector, dataLoaded);
    } else if(firstCommandWord == "exit"){
        exit(0);
    }
} //end findCommand


int main() {

    cout << "Welcome to the Gerrymandering App!" << endl << endl;
    ourvector<struct gerrymander> gerryVector;
    bool dataLoaded = false;
    bool locationLoaded = true;
    int indexOfLoc = -2;
    string currLocation = "N/A";
    string command = prompt(dataLoaded, locationLoaded, currLocation);
    //keeps prompting user after calls to functions within findCommand are fulfilled until "exit" command
    while(command != "exit"){
        findCommand(command, gerryVector, dataLoaded, currLocation, indexOfLoc);
        command = prompt(dataLoaded,locationLoaded,currLocation);
    } //end while

    return 0;
} //end main