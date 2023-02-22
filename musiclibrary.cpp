/****************************
 *
 * Program 2: Music Library
 * Course: CS 251, Spring 2023, UIC
 * System: CLion on MacOS
 * Author: Aamir Merchant
 *
 ****************************/
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include "helpers.cpp"

using namespace std;



struct musicStruct {
    string albumTitle;
    set<string> artistName;
    set<string> songTitle;
};


//overloads the < operator for comparison for the set of musicStruct. Returns boolean
bool operator<(const musicStruct &lhs, const musicStruct &rhs) {
    return lhs.albumTitle < rhs.albumTitle;
}//End operator


//loads the data file into the correct set. Passed a string that may contain text file. Void return value.
void load(string txtFile, musicStruct music, set<musicStruct> &mySet){

    //opens the file
    ifstream file;
    if(txtFile.empty()){
        file.open("musicdatabase.txt");
        txtFile = "musicdatabase.txt";
    } else {
        file.open(txtFile);
    }
    if(!file.is_open()){
        cout << "Error: Could not open music library file - " << txtFile << endl;
    }

    string line, title;

    //reads through file placing the lines into the correct category for each set in each struct and placing that struct
    //into the set of structs
    while(!file.eof()){
        getline(file, line);
        if(line.empty()){
            break;
        }
        title = line;
        music.albumTitle = title;
        getline(file, line);
        while(line.substr(0, 2) != "01"){
            music.artistName.insert(line);
            getline(file, line);
        }

        while(line != title){
            music.songTitle.insert(line);
            getline(file, line);
        }
        mySet.insert(music);
        music.songTitle.clear();
        music.artistName.clear();
    }

    file.close();

}//End load


//displays statistics for the music library. Void return value.
void stats(string command, set<musicStruct> &mySet){

        cout << "Overall Music Library Stats" << endl
             << "===========================" << endl;

        //collects proper numbers for each statistic
        int totalRecords = mySet.size();
        int totalUniqueArtists;
        int totalSongs = 0;
        set <string> uniqueArtistSet;
        //uses set to only have an artist displayed once
        for (auto &x : mySet) {
            uniqueArtistSet.insert(x.artistName.begin(), x.artistName.end());
            totalSongs += x.songTitle.size();
        }
        totalUniqueArtists = uniqueArtistSet.size();
        uniqueArtistSet.clear();

        cout << "Total Records: " << totalRecords << endl
             << "Total Unique Artists: " << totalUniqueArtists << endl
             << "Total Songs: " << totalSongs << endl << endl;

        //outputs full library using for loops to go through the sets
    if(command == "-d") {

        cout << "Your Current Music Library Includes" << endl
             << "===================================" << endl;
        for (auto &s: mySet) {
            cout << s.albumTitle << endl;
            for (auto &x: s.artistName) {
                cout << " " << x << endl;
            }
            for (auto &z: s.songTitle) {
                cout << "   " << z << endl;
            }
        }

        cout << endl;
    } //end -d

}//End stats


//exports the music library into a file. Is passed a string that may contain name of text file. Void return value.
void exportFile(string txtfile, set<musicStruct> &mySet){

    if(mySet.empty()){
        cout << "Error: Cannot export empty music library." << endl;
    }

    ofstream file;

    //opens the file to be exported to
    if(txtfile.empty()){
        file.open("musicdatabase.txt");
    } else {
        file.open(txtfile);
    }

    //goes through music library using for loops and outputs them to file
    for (auto &s: mySet) {
        file << s.albumTitle << endl;
        for (auto &x: s.artistName) {
            file << x << endl;
        }
        for (auto &z: s.songTitle) {
            file << z << endl;
        }
        file << s.albumTitle << endl;
    }

    file.close();

}//End exportFile


//final outputs at the end of searches. Void return value.
void searchEnd(set<string> &setOrder, bool &exists){
    //checks if result has been found or not and outputs
    if(!exists){
        cout << "No results found." << endl;
    } else {
        for (auto &z : setOrder) {
            cout << z << endl;
        }
    }
    cout << endl;
    exists = false;
}//End searchEnd


//displays message if there is a match for the search. Void return value.
void existsMessage(bool &exists){
    if (!exists) {
        cout << "Your search results exist in the following albums: " << endl;
        exists = true;
    }
}//End existsMessage


//searches for an album within music library. Void return value.
void searchMiddle(set<string> &setOrder, set<musicStruct> &mySet, string command, bool &exists){
    //uses stringstream to parse through the words being searched for in album name
    stringstream s(command);
    string scommand;
    while(s >> scommand) {
        for (auto &x: mySet) {
            string title = x.albumTitle;
            tolower(title);
            //if an album match is found message is displayed, and it is inserted into a set to be displayed in order
            if (title.find(scommand) != string::npos) {
                existsMessage(exists);
                setOrder.insert(x.albumTitle);
            }//End if
        }//End for-loop
    }//End while

}//End searchMiddle


//overloaded function for searching for a song or artist within music library. Void return value.
void searchMiddle(set<string> &setOrder, set<musicStruct> &mySet, string command, bool &exists, string type) {
    //uses stringstream to parse through the words being searched for in artist or song name
    stringstream s(command);
    string scommand;
        while (s >> scommand) {
            for (auto &x: mySet) {
                if(type == "artist"){
                    //goes through artistName sets looking for matching artist
                for (auto &y: x.artistName) {
                    string artistName = y;
                    tolower(artistName);
                    //if artist is found, added to set to be ordered and a message is displayed
                    if (artistName.find(scommand) != string::npos) {
                        existsMessage(exists);
                        setOrder.insert(x.albumTitle);
                    }
                }//End for-loop of artistName set
                } else {
                    //goes through songTitle sets looking for matching song
                    for (auto &y: x.songTitle) {
                        string songTitle = y;
                        tolower(songTitle);
                        ////if song is found, added to set to be ordered and a message is displayed
                        if (songTitle.find(scommand) != string::npos) {
                            existsMessage(exists);
                            setOrder.insert(x.albumTitle);
                        }
                    }//End for-loop of songTitle set
                }//End if
            }//End for-loop of mySet
        }//End while loop for stringstream
}//End searchMiddle


//function that calls other functions to search for albums. Void return value.
void searchAlbum(string command, set<musicStruct> &mySet){
    command = command.substr(command.find(' ') + 1); //removes "album" from command
    tolower(command);
    bool exists = false;
    set <string> setOrder;

    searchMiddle(setOrder, mySet, command, exists);
    searchEnd(setOrder, exists);
}//End searchAlbum


//searches for artists when plus modifier is used
void searchArtistModifierPlus(string command, set<musicStruct> &mySet, bool &exists){
    command = command.substr(command.find(' ') + 1); //removes "artist" from command
    set<string> setOrder;
    stringstream s(command);
    string scommand;
    string scommand1;
    //goes through each word and removes the plus prepended to it
    while(s >> scommand) {
        s >> scommand1;
        scommand = scommand.substr(scommand.find('+') + 1);
        scommand1 = scommand1.substr(scommand1.find('+') + 1);
        //goes through the sets looking for a matching artist name
        for (auto &x: mySet) {
            for (auto &y: x.artistName) {
                string artistName = y;
                tolower(artistName);

                //if an artist name is found with all words then message displayed and added to set to be ordered and displayed
                if (artistName.find(scommand) != string::npos && artistName.find(scommand1) != string::npos) {
                    existsMessage(exists);
                    setOrder.insert(x.albumTitle);
                }

            }//End for-loop through artistName set
        }//End for-loop through mySet
    }//End while loop
    searchEnd(setOrder, exists);
}//End searchArtistModifierPlus


//searches for song when plus modifier is used
void searchSongModifierPlus(string command, set<musicStruct> &mySet, bool &exists){
    command = command.substr(command.find(' ') + 1); //removes "song" from command
    set<string> setOrder;
        stringstream s(command);
        string scommand;
        string scommand1;
         //goes through each word and removes the plus prepended to it
        while(s >> scommand) {
            s >> scommand1;
            scommand = scommand.substr(scommand.find('+') + 1);
            scommand1 = scommand1.substr(scommand1.find('+') + 1);
            //goes through the sets looking for a matching song name
            for (auto &x: mySet) {
                for (auto &y: x.songTitle) {
                    string songTitle = y;
                    tolower(songTitle);

                        ////if a song name is found with all words then message displayed and added to set to be ordered and displayed
                        if (songTitle.find(scommand) != string::npos && songTitle.find(scommand1) != string::npos) {
                            existsMessage(exists);
                            setOrder.insert(x.albumTitle);
                        }

                }//End for-loop through songTitle set
            }//End for-loop through mySet
        }//End while loop
    searchEnd(setOrder, exists);
}//End searchSongModifierPlus


//used to see if search condition is met for search and then places into set and displays message.
void searchModifierMinus(string scommand, string scommand1, set<string> &setOrder, bool &exists, musicStruct x, string title){

        tolower(title);

        if (title.find(scommand) != string::npos && title.find(scommand1) == string::npos) {
            existsMessage(exists);
            setOrder.insert(x.albumTitle);
        }
        //if there exists the word with minus within an album, it is taken out of the set.
        if(title.find(scommand1) != string::npos){
            setOrder.erase(x.albumTitle);
        }
}//End searchModifierMinus


//searches for a artists in album when minus is prepended to search term.
void searchArtistModifierMinus(string command, set<musicStruct> &mySet, bool &exists){
    command = command.substr(command.find(' ') + 1); //removes "artist" from command
    set<string> setOrder;
    stringstream s(command);
    string scommand;
    string scommand1;
    //uses stringstream to parse through the words being searched for in artist name
    while(s >> scommand) {
        s >> scommand1;
        scommand = scommand.substr(scommand.find('-') + 1);
        scommand1 = scommand1.substr(scommand1.find('-') + 1);
        //goes through artistName sets looking for matching artist
        for (auto &x: mySet) {
            for (auto &y: x.artistName) {
                string title = y;
                searchModifierMinus(scommand, scommand1, setOrder, exists, x, title);
            }//End for loop for artistName
        }//End for loop for mySet
    }//End while loop
    searchEnd(setOrder, exists);
}//End searchArtistModifierMinus


//searches for a song in album when minus is prepended to search term.
void searchSongModifierMinus(string command, set<musicStruct> &mySet, bool &exists){
    command = command.substr(command.find(' ') + 1); //removes "song" from command
    set<string> setOrder;
    stringstream s(command);
    string scommand;
    string scommand1;
    //uses stringstream to parse through the words being searched for in song name
    while(s >> scommand) {
        s >> scommand1;
        scommand = scommand.substr(scommand.find('-') + 1);
        scommand1 = scommand1.substr(scommand1.find('-') + 1);
        //goes through songTitle sets looking for matching artist
        for (auto &x: mySet) {
            for (auto &y: x.songTitle) {
                string title = y;
                searchModifierMinus(scommand, scommand1, setOrder, exists, x, title);
            }//End for loop for songTitle
        }//End for loop for mySet
    }//End while loop
    searchEnd(setOrder, exists);
}//End searchSongModifierMinus


//calls the correct function depending on the present modifier
void searchArtistAndSong(string command, set<musicStruct> &mySet){
    string type;
    bool exists = false;
    tolower(command);

    //if artist is being searched for
    if(command.find("artist") != string::npos){
        type = "artist";
        //and plus is present
        if(command.find('+') != string::npos){

            searchArtistModifierPlus(command, mySet, exists);
            return;

        //and minus is present
        } else if (command.find('-') != string::npos){

            searchArtistModifierMinus(command, mySet, exists);
            return;

        }

    //if song is being searched for
    } else {
        //and plus is present
        if(command.find('+') != string::npos){

            searchSongModifierPlus(command, mySet, exists);
            return;

        //and minus is present
        } else if (command.find('-') != string::npos){

            searchSongModifierMinus(command, mySet, exists);
            return;

        }
        type = "song";
    }//end if-else

    command = command.substr(command.find(' ') + 1); //removes either "album" or "song" from command

    set <string> setOrder;

    searchMiddle(setOrder, mySet, command, exists, type);
    searchEnd(setOrder, exists);
}//End searchArtistAndSong


//calls function depending on search command
void search(string command, set<musicStruct> &mySet){

    //if search command is empty displays error
    if(command.empty()){
        cout << "Error: Search terms cannot be empty." << endl
             << "No results found." << endl << endl;

    } else if(command.substr(0, command.find(' ')) == "album"){
        searchAlbum(command, mySet);

    } else if(command.substr(0, command.find(' ')) == "artist" || command.substr(0, command.find(' ')) == "song"){
        searchArtistAndSong(command, mySet);
    }
}//End search


int main(){
    string userEntry;
    string command, remains;

    musicStruct music;
    set<struct musicStruct> mySet;

    // Display welcome message once per program execution
    cout << "Welcome to the Music Library App" << endl;
    cout << "--------------------------------" << endl;

    // Stay in menu until exit command
    do
    {
        cout << endl;
        cout << "Enter a command (help for help): " << endl;
        getline(cin, userEntry);
        cout << endl;

        // Split the user entry into two pieces
        splitFirstWord(userEntry, command, remains);
        tolower(command);

        // take an action, one per iteration, based on the command
        if (command == "help")
        {
            helpCommand();
        }
        else if (command == "clear")
        {
            mySet.clear();
        }
        else if (command == "export")
        {
            exportFile(remains, mySet);
        }
        else if (command == "load")
        {
            load(remains, music, mySet);
        }
        else if (command == "stats")
        {
            stats(remains, mySet);
        }          
        else if (command == "search")
        {
            search(remains, mySet);
        }

    }while(command != "exit");    

    cout << "Thank you for using the Music Library App" << endl;
    return 0;

}//End main