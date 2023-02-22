/****************************
 *
 * Program 5: Yahtzee
 * Course: CS 141, Fall 2022, UIC
 * System: CLion on MacOS
 * Author: Aamir Merchant, starter code provided by Dr. Sara Riazi
 *
 * ***************************/


#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>

using namespace std;


//#################################################################################################

class Dice{
private:
    int value;

public:

    //Randomly assigns a value between from 1 to 6 to the dice.
    void roll();

    //Getter function for dice
    int reveal();

    //The autograder will set the values directly instead of calling roll() to avoid randomness!
    void setValue(int value) {this->value = value;}

}; //End Dice Class

void Dice::roll() {value = rand() % 6 + 1;}
int Dice::reveal() {return value;}

//#################################################################################################

const int HAND_SIZE = 5;

class Hand {
public:

    //Display the value of the five dice
    void show();

    void play() {}

    //Getter function for dice pointer
    Dice* getDice(int diceNum);

    //selection is the string of dice numbers that the player wants to keep.
    //For example, "125" means that player wants to keep the first, second, and fifth dice, and roll the rest.
    void setSelection(string selection);

    //Constructor for Hand class - creates five dice pointer objects and rolls them
    Hand();

private:

    Dice *pOne;
    Dice *pTwo;
    Dice *pThree;
    Dice *pFour;
    Dice *pFive;

}; //End Hand Class

void Hand::show(){

    cout << "Hand: "
         << pOne->reveal() << " "
         << pTwo->reveal() << " "
         << pThree->reveal() << " "
         << pFour->reveal() << " "
         << pFive->reveal() << endl;

}//End show

Dice* Hand::getDice(int diceNum){

    if(diceNum == 0){ return pOne;}
    if(diceNum == 1){ return pTwo;}
    if(diceNum == 2){ return pThree;}
    if(diceNum == 3){ return pFour;}
    if(diceNum == 4){ return pFive;}
    return nullptr;

}//End getDice

void Hand::setSelection(string selection) {

    if(selection.find("1") == string::npos){
        pOne->roll();
    }
    if(selection.find("2") == string::npos){
        pTwo->roll();
    }
    if(selection.find("3") == string::npos){
        pThree->roll();
    }
    if(selection.find("4") == string::npos){
        pFour->roll();
    }
    if(selection.find("5") == string::npos){
        pFive->roll();
    }

}//End setSelection

Hand::Hand() {

    pOne = new Dice;
    pTwo = new Dice;
    pThree = new Dice;
    pFour = new Dice;
    pFive = new Dice;
    pOne->roll();
    pTwo->roll();
    pThree->roll();
    pFour->roll();
    pFive->roll();

}//End Hand

//#################################################################################################

//List of rows in the board
const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;
const int BOARD_SIZE=13;

class Game {
public:

    //calcScore returns a score of a hand (5 dice) for given row in the board.
    //Note the rows are indexed from zero.
    //For example if the hand is 2 1 1 5 1 then calcScore(hand, ONES) returns 3 and  calcScore(hand, TWOS) returns 2.
    int calcScore(Hand *hand, int row);

    //Display the board
    void show();

    //Returns the score of the upper part of the board
    int getUpperScore();

    //Returns the score of the lower part of the board
    int getLowerScore();

    //Returns the bonus points
    int getBonusScore();

    //Returns the total score
    int getTotalScore();

    //Play a hand based on the selected row
    void play(Hand *hand, int row);

    //Check to see if a row has been played or not (returns true if a row has been played)
    bool isPlayed(int row);

    //Check to see if all rows haven been played or not (returns true if all rows have been played)
    bool isFinished();

    //Check if criteria for small straight has been met
    bool smallStraightCheck(Hand* hand);

    //Check if criteria for large straight has been met
    bool largeStraightCheck(Hand* hand);

    //Check if criteria for full house has been met
    bool fullHouseCheck(Hand* hand);

    //Check if criteria for three of a kind has been met
    bool threeOfKindCheck(Hand* hand);

    //Check if criteria for four of a kind has been met
    bool fourOfKindCheck(Hand* hand);

    //Check if criteria for yahtzee has been met
    bool yahtzeeCheck(Hand* hand);

    //Counts the number of occurrences for each die
    void diceCounts(Hand* hand);

private:
    bool onesStatus = false;
    bool twosStatus = false;
    bool threesStatus = false;
    bool foursStatus = false;
    bool fivesStatus = false;
    bool sixesStatus = false;
    bool threeOfKindStatus = false;
    bool fourOfKindStatus = false;
    bool fullHouseStatus = false;
    bool smallStraightStatus = false;
    bool largeStraightStatus = false;
    bool chanceStatus = false;
    bool yahtzeeStatus = false;
    int sum = 0, bonus = 0, total = 0;
    string ones = "-";
    string twos = "-";
    string threes = "-";
    string fours = "-";
    string fives = "-";
    string sixes = "-";
    string threeOfKind = "-";
    string fourOfKind = "-";
    string fullHouse = "-";
    string smallStraight = "-";
    string largeStraight = "-";
    string chance = "-";
    string yahtzee = "-";
    int count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0;
};

bool Game::isPlayed(int row) {

    if(row == 0){return onesStatus;}
    if(row == 1){return twosStatus;}
    if(row == 2){return threesStatus;}
    if(row == 3){return foursStatus;}
    if(row == 4){return fivesStatus;}
    if(row == 5){return sixesStatus;}
    if(row == 6){return threeOfKindStatus;}
    if(row == 7){return fourOfKindStatus;}
    if(row == 8){return fullHouseStatus;}
    if(row == 9){return smallStraightStatus;}
    if(row == 10){return largeStraightStatus;}
    if(row == 11){return chanceStatus;}
    if(row == 12){return yahtzeeStatus;}

    return false;
}//End isPlayed

bool Game::isFinished() {

    return(onesStatus && twosStatus && threesStatus && foursStatus && fivesStatus && sixesStatus &&
       threeOfKindStatus && fourOfKindStatus && fullHouseStatus && smallStraightStatus && largeStraightStatus &&
       chanceStatus && yahtzeeStatus);

}//End isFinished

void Game::play(Hand *hand, int row) {

    //Calculate the scores of selected row and sets status to true
    if(row == 0){
        ones = to_string(calcScore(hand, row));
        onesStatus = true;
    }
    if(row == 1){
        twos = to_string(calcScore(hand, row));
        twosStatus = true;
    }
    if(row == 2){
        threes = to_string(calcScore(hand, row));
        threesStatus = true;
    }
    if(row == 3){
        fours = to_string(calcScore(hand, row));
        foursStatus = true;
    }
    if(row == 4){
        fives = to_string(calcScore(hand, row));
        fivesStatus = true;
    }
    if(row == 5){
        sixes = to_string(calcScore(hand, row));
        sixesStatus = true;
    }
    if(row == 6){
        threeOfKind = to_string(calcScore(hand, row));
        threeOfKindStatus = true;
    }
    if(row == 7){
        fourOfKind = to_string(calcScore(hand, row));
        fourOfKindStatus = true;
    }
    if(row == 8){
        fullHouse = to_string(calcScore(hand, row));
        fullHouseStatus = true;
    }
    if(row == 9){
        smallStraight = to_string(calcScore(hand, row));
        smallStraightStatus = true;
    }
    if(row == 10){
        largeStraight = to_string(calcScore(hand, row));
        largeStraightStatus = true;
    }
    if(row == 11){
        chance = to_string(calcScore(hand, row));
        chanceStatus = true;
    }
    if(row == 12){
        yahtzee = to_string(calcScore(hand, row));
        yahtzeeStatus = true;
    }

    //Calculates bonus and sets status accordingly
    bool bonusStatus = false;
    while(!bonusStatus){
        if(sum >= 63){
            bonus = 35;
            total += 35;
        } //End ifi
        bonusStatus = true;
    }//End while

} //End play

bool Game::smallStraightCheck(Hand *hand){

    diceCounts(hand);

    if( (count1 > 0 && count2 > 0 && count3 > 0 && count4 > 0)||
        (count2 > 0 && count3 > 0 && count4 > 0 && count5 > 0) ||
        (count3 > 0 && count4 > 0 && count5 > 0 && count6 > 0) ){
        return true;
    }

    return false;
}//End smallStraightCheck

bool Game::largeStraightCheck(Hand *hand) {

    diceCounts(hand);

    if ((count1 > 0 && count2 > 0 && count3 > 0 && count4 > 0 && count5 > 0) ||
        (count2 > 0 && count3 > 0 && count4 > 0 && count5 > 0 && count6 > 0)){
        return true;
    }

    return false;
}//End largeStraightCheck

bool Game::fullHouseCheck(Hand* hand){

    diceCounts(hand);

    if( (count1 == 3 || count2 == 3 || count3 == 3 || count4 == 3 || count5 == 3 || count6 == 3) &&
        (count1 == 2 || count2 == 2 || count3 == 2 || count4 == 2 || count5 == 2 || count6 == 2) ||
        yahtzeeCheck(hand) ){
        return true;
    }

    return false;
}//End fullHouseCheck

bool Game::threeOfKindCheck(Hand *hand) {

    diceCounts(hand);

    if(count1 > 2 || count2 > 2 || count3 > 2 || count4 > 2 || count5 > 2 || count6 > 2){
        return true;
    }

    return false;
}//End threeOfKindCheck

bool Game::fourOfKindCheck(Hand *hand) {

    diceCounts(hand);

    if(count1 > 3 || count2 > 3 || count3 > 3 || count4 > 3 || count5 > 3 || count6 > 3){
        return true;
    }

    return false;
}//End fourOfKindCheck

bool Game::yahtzeeCheck(Hand *hand){

    if((hand->getDice(0)->reveal() == hand->getDice(1)->reveal() ) &&
       (hand->getDice(2)->reveal() == hand->getDice(3)->reveal() ) &&
       (hand->getDice(4)->reveal() == hand->getDice(0)->reveal() )){
        return true;
    }

    return false;
}//End yahtzeeCheck

void Game::diceCounts(Hand *hand){

 count1 = 0; count2 = 0; count3 = 0; count4 = 0; count5 = 0; count6 = 0;

    for(int i = 0; i < 5; i++) {
        if (hand->getDice(i)->reveal() == 1) { count1++; }
        if (hand->getDice(i)->reveal() == 2) { count2++; }
        if (hand->getDice(i)->reveal() == 3) { count3++; }
        if (hand->getDice(i)->reveal() == 4) { count4++; }
        if (hand->getDice(i)->reveal() == 5) { count5++; }
        if (hand->getDice(i)->reveal() == 6) { count6++; }
    }

}//End diceCounts

int Game::calcScore(Hand *hand, int row) {

    //Calculates sum of selected die in hand
    if(row < 6){
        int count = 0;
        for(int i = 0; i < 5; i++){
            if(hand->getDice(i)->reveal() == row+1){
                count += row+1;
            }
        }
        sum += count;
        total += count;
        return count;
    }

    //Calculates sum of all dice in hand
    if( (row == 6 && threeOfKindCheck(hand))|| (row == 7 && fourOfKindCheck(hand)) || row == 11){
        int count = 0;
        for(int i = 0; i < 5; i++){
            count += hand->getDice(i)->reveal();
        }
        total += count;
        return count;
    }

    if(row == 8 && fullHouseCheck(hand)){fullHouse = "25"; total += 25; return 25;}
    if(row == 9 && smallStraightCheck(hand)){smallStraight = "30"; total += 30; return 30;}
    if(row == 10 && largeStraightCheck(hand)){largeStraight = "40"; total += 40; return 40;}
    if(row == 12 && yahtzeeCheck(hand)) {yahtzee = "50"; total += 50; return 50;}

    return 0;
}//End calcScore

void Game::show() {

    cout <<
    "1.  Ones:" << setw(17) << ones << endl <<
    "2.  Twos:" << setw(17) << twos << endl <<
    "3.  Threes:" << setw(15) << threes << endl <<
    "4.  Fours:" << setw(16) << fours << endl <<
    "5.  Fives:" << setw(16) << fives << endl <<
    "6.  Sixes:" << setw(16) << sixes << endl <<
    "    Sum:" << setw(18) << sum << endl <<
    "    Bonus:" << setw(16) << bonus << endl <<
    "7.  Three of a kind:" << setw(6) << threeOfKind << endl <<
    "8.  Four of a kind:" << setw(7) << fourOfKind << endl <<
    "9.  Full house:" << setw(11) << fullHouse << endl <<
    "10. Small straight:" << setw(7) << smallStraight << endl <<
    "11. Large straight:" << setw(7) << largeStraight << endl <<
    "12. Chance:" << setw(15) << chance << endl <<
    "13. Yahtzee:" << setw(14) << yahtzee << endl <<
    "Total:" << setw(20) << total << endl;

}//End show

int Game::getUpperScore() {return sum;}

int Game::getLowerScore() {return total-sum;}

int Game::getBonusScore() {if(sum >= 63){return 35;} else {return 0;}}

int Game::getTotalScore() {return total;}

//#######################################################################################

//The run function is the main loop of your program
void run() {

    Game game;

    while(!game.isFinished()) {

        game.show(); //displays board

        Hand *one = new Hand(); //creates hand object
        one->show(); //shows dice in hand
        string selection;
        //prompts selection of dice to keep from hand
        for (int i = 0; i < 2; i++) {
            cout << "Keep Dice (s to stop rolling): ";
            cin >> selection;
            if (selection == "s") {
                break;
            }
            one->setSelection(selection);
            one->show();
        }//End for-loop

        //Prompts for row to be played
        int combination;
        cout << "Select a combination to play: ";
        cin >> combination;
        while(game.isPlayed(combination)){
            cout << "This combination has been played. Select another one: ";
            cin >> combination;
        }
        game.play(one, combination);
        delete one; //Deletes hand object
    }

    game.show(); //shows final board after game is finished

}//End run


int main() {

    srand(time(0));
    run();
    //test_case();
    return 0;
}