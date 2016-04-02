/*
 * Dictionary.cpp
 *
 *  Created on: Nov 11, 2015
 *      Author: Gessi
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary(){
	// constructing the dictionary

	string fileName;
	ifstream dictStream;

	// read in the ditionary file name
	do {
		cout << "Enter dictionary file name: ";
		cin >> fileName;
		dictStream.open (fileName.c_str(), ios::in);
	} while (!dictStream.good());
	// keep trying until this works

	string line;
	// make sure the file has some stuff in it
	if (!getline(dictStream, line)){
		cerr << "Error: dictionary file is empty" << endl;
		dictionary.clear();
		return;
	}

	string word;
	while (dictStream >> word) {
		dictionary.push_back(word);
	}

	cout << "Dictionary size is " << dictionary.size()
			<< endl << endl;
}


bool Dictionary::binarySearch(string word){

	int dictStart = 0;
	int dictEnd = dictionary.size() - 1;

	// if the the word is not the same with the middle word
	// in the dictionary, then execute the following codes
	while (word.compare(dictionary.at
			((dictStart + dictEnd)/2)) != 0) {

		// Two cases where the binary search has reached the end
		// and the word is not in the dictionary
		if (dictStart == dictEnd || (dictStart == dictEnd - 1
				&& word.compare(dictionary.at (dictEnd)) != 0)) {
			return false;

		// if there are portion of the dictionary to search
		// through then reset the boundary where the target
		// word might be
		} else if (word.compare(dictionary.at
				((dictStart + dictEnd)/2)) < 0) {
			dictEnd = (dictStart + dictEnd)/2 - 1;
		} else {
			dictStart = (dictStart + dictEnd)/2 + 1;
		}
	}

	// if the word is same with some word within the dictionary
	// then return true
	return true;
}


bool Dictionary::isPrefix(string word){

	int dictStart = 0;
	int dictEnd = dictionary.size() - 1;

	// Similar idea as the binary search, but instead comparing
	// the entire word, only compare the first few characters
	while (word.compare((dictionary.at ((dictStart + dictEnd)/2))
			.substr(0, word.length())) != 0) {

		// Two scenarios where the given string is not a prefix
		if (dictStart == dictEnd || (dictStart == dictEnd - 1 &&
				word.compare((dictionary.at (dictEnd))
				.substr(0, word.length())) != 0)) {
			return false;

		// Narrowing down next search's boundary
		} else if (word.compare((dictionary.at
				((dictStart + dictEnd)/2)).
				substr(0, word.length())) < 0) {
			dictEnd = (dictStart + dictEnd)/2 - 1;
		} else {
			dictStart = (dictStart + dictEnd)/2 + 1;
		}
	}

	return true;

}

