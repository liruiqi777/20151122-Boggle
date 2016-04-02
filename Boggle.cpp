/*
 * Boggle.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: Gessi
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Boggle.h"
#include "Dictionary.h"


using namespace std;


Boggle::Boggle(){

	string fileName;
	ifstream puzzleStream;    // will be the puzzle file

	// read in the puzzle file name
	do {
		cout << "Enter Boggle board file name: ";
		cin >> fileName;
		puzzleStream.open(fileName.c_str(), ios::in);
	} while (!puzzleStream.good());  // keep trying until it works

	string line;
	if (!getline(puzzleStream, line)){
		cerr << "Error: Boggle board file is empty" << endl;
		numRows = 0;
		numCols = 0;
		return;
	}

	// put the first puzzle line in theBoard
	numCols = line.size();
	for (int i = 0; i < numCols; i++) {
		theBoard[0][i] = tolower(line.at(i));
	}

	// put the rest of the puzle lines in theBoard
	for (numRows = 1; getline(puzzleStream, line); numRows ++) {
		// make sure it's rectangular
		if (line.size() != numCols) {
			cerr << "Error: Boggle board is"
					"not rectangular" << endl;
			numRows = 0;
			numCols = 0;
			return;
		}

		// put this puzzle line in theBoard
		for (int i = 0; i < numCols; i++){
			theBoard[numRows][i] = tolower(line.at(i));
		}
	}

	// find all words that appeared in the board
	for (int r = 0; r < numRows; r++){
		for (int c = 0; c < numCols; c++){
			findWord(theBoard, r, c, "");
		}
	}
}

// using a for loop to the row and column number and then
// roll over every letter in the puzzle and print them
void Boggle::print(){
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++){
				cout << char(toupper(theBoard[r][c])) << " ";
		}
		cout << endl;
	}

	cout << endl;
}


void Boggle::humanPlay(){

	// ask if the person wants to play the game
	string answer;
	cout << "Would you like to make a feeble attempt to find"
		<< "some words before the computer finds them all and"
		<< "crushes your spirit? (y or n)";
	cin >> answer;
	if (answer.compare("n") == 0){
		cout << "Human Words:" << endl;
		cout << "None entered - SHAME!!" << endl;
		cout << "Total score: 0" << endl << endl;
		return;
	}

	// if the person wants to play, then check if the word input
	// is valid and count points accordingly
	cout << "Enter as many words as you want, one to a line."
		<< endl << "Enter an exlamation point when you are done."
		<< endl;

	string word = "";
	while (word != "!"){
		if (word != ""){
			if(isLegit(word, ansList)){
				ansList.push_back(word);
			}
		}
		cin >> word;
	}

	int score = 0;
	cout << "Human Words:" << endl;
	cout << "=============" << endl;
	string ans;
	for (vector<string>::iterator iter = ansList.begin();
			iter < ansList.end(); iter++){
		ans = *iter;
		cout << ans << endl;
		if (ans.size() > 2){
			score ++;
			if (ans.size() > 4){
				score ++;
				if (ans.size() > 5){
					score ++;
					if (ans.size() > 6){
						score = score + 2;
						if (ans.size() > 10){
							score = score + 6;
						}
					}
				}
			}
		}
	}
	cout << endl;
	cout << "Total score: " << score << endl << endl << endl;
}

void Boggle::computerPlay(){
	cout << "Computer Words:" << endl;
	cout << "===============";
	int score = 0;

	// print out all words in the board, check if the human
	// player has found it, and count points accordingly
	string ans;
	for (vector<string>::iterator iter = wordsOnBoard.begin();
			iter < wordsOnBoard.end(); iter++){
		ans = *iter;
		cout << endl << ans;
		if (!alreadyUsed(ans, ansList)){
			if (ans.size() > 2){
				score ++;
				if (ans.size() > 4){
					score ++;
					if (ans.size() > 5){
						score ++;
						if (ans.size() > 6){
							score = score + 2;
							if (ans.size() > 7){
								score = score + 6;
							}
						}
					}
				}
			}
		}else{
			cout << "     disallowed: found by human";
		}
	}

	cout << endl << endl << "Total Score: " << score;
}

bool Boggle::isLegit(string word, vector<string> ansList){

	// check if the word can be counted as a legit word and
	// if not, print out why
	bool isLegit = true;
	if (word.size() < 3){
		cout << "    invalid word: words must have 3 "
				"or more characters" << endl;
		isLegit = false;
	}
	if (!dictionary.binarySearch(word)){
		cout << "    invalid word: not in dictionary" << endl;
		isLegit = false;
	}
	if (!alreadyUsed(word,wordsOnBoard)){
		cout << "    invalid word: not in the board" << endl;
		isLegit = false;
	}
	if(alreadyUsed(word, ansList)){
		cout << "    invalid word: already used" << endl;
		isLegit = false;
	}

	if (isLegit){
		cout << "    Good word!" << endl;
	}

	return isLegit;
}

bool Boggle::alreadyUsed(string word, vector<string> wordList){

	// check if the word is already in the given vector
	for (vector<string>::iterator iter = wordList.begin();
			iter < wordList.end(); iter++){
		if (*iter == word){
			return true;
		}
	}
	return false;
}


void Boggle::findWord(char theBoard[MAX_ROWS][MAX_COLS],
			int startR, int startC, string word){
	// base cases

	if (startR < 0 || startR >= numRows || startC < 0 ||
			startC >= numCols || theBoard[startR][startC] == ' ')
		return;

	// add the next letter to the existing string and see if it
	// is in the dictionary and not found alreadu
	word = word + theBoard[startR][startC];
	if (dictionary.binarySearch(word) && word.size() > 2){
		if (!alreadyUsed(word, wordsOnBoard)){
			wordsOnBoard.push_back(word);
		}
	}

	// remove used letter so that the word cannot be
	// used repeatedly
	char letter = theBoard[startR][startC];
	theBoard[startR][startC] = ' ';

	// search all either directions
	if (dictionary.isPrefix(word)){
		for (int rOff = -1; rOff <= 1; rOff++){
			for (int cOff = -1; cOff <= 1; cOff++){
				if (rOff != 0 || cOff != 0){
					findWord(theBoard, startR + rOff,
							startC + cOff, word);
				}
			}
		}
	}

	// put the removed letter back after search in this direction
	// has been completed
	theBoard[startR][startC] = letter;
}
