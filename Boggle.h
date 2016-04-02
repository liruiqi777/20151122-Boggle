/*
 * Boggle.h
 *
 *  Created on: Nov 11, 2015
 *      Author: Gessi
 */

#ifndef BOGGLE_H_
#define BOGGLE_H_

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Dictionary.h"

using namespace std;

class Boggle{
	public:

		static const int minLength = 3;
		static const int MAX_ROWS = 4;
		static const int MAX_COLS = 4;

		// constructor
		Boggle();

		// functions for Boggle()
		void print();
		void humanPlay();
		void computerPlay();
		bool isLegit(string word, vector<string> wordList);
		bool alreadyUsed(string word, vector<string> wordList);
		void findWord(char theBoard[MAX_ROWS][MAX_COLS],
			int startR, int startC, string word);


	private:
		int numRows;
		int numCols;
		Dictionary dictionary;
		vector<string> wordsOnBoard;
		vector<string> ansList;
		char theBoard[MAX_ROWS][MAX_COLS];
};


#endif /* BOGGLE_H_ */
