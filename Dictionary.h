/*
 * Dictionary.h
 *
 *  Created on: Nov 11, 2015
 *      Author: Gessi
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_


#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Dictionary{

	public:
		// constructor
		Dictionary();

		// functions in dictionary class
		bool binarySearch (string word);
		bool isPrefix(string word);
		int size() {return (int) dictionary.size();}
		string at(int i) {return dictionary.at(i);}

	private:
		vector<string> dictionary;

};


#endif /* DICTIONARY_H_ */
