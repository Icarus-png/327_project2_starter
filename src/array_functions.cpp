/*
 * array_functions.cpp
 *
 *  Created on: Feb 16, 2020
 *      Author: Josh Beck
 */

//============================================================================
//	TODO add necessary includes here
//============================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "array_functions.h"
#include "constants.h"
#include "utilities.h"

using namespace std;
//============================================================================
//	stuff you will need
//============================================================================

//TODO define a structure to track words and number of times they occur
struct entry {
	int count;
	string word;
};

//TODO add a global array of entry structs (global to this file)
entry arr[constants::MAX_WORDS];

//TODO add variable to keep track of next available slot in array
int slot = 0;

//TODO define all functions in header file
void clearArray() {
	slot = 0;
}

int getArraySize() {
	return slot;
}

std::string getArrayWordAt(int i) {
	return arr[i].word;
}

int getArrayWord_NumbOccur_At(int i) {
	return arr[i].count;
}

bool processFile(std::fstream &myfstream) {
	string line;
	if (!myfstream.is_open()) {
			return false;
		}
	while (getline(myfstream, line)) {
		processLine(line);
	}
	return true;
}

void processLine(std::string &myString) {
	stringstream ss(myString);
	string tempToken;

	while (getline(ss, tempToken, constants::CHAR_TO_SEARCH_FOR)) {
		processToken(tempToken);
	}
}

//Probably way more complicated that it needs to be. Look back over to streamline.
void processToken(std::string &token) {
	strip_unwanted_chars(token);
	string temp = token;
	//int count = 0;
	//int bruh;
	//bool soloVal = true;

	if (token != "") {
		toUpper(temp);
		for (int i = 0; i < slot; i++) {
			string arrVal = arr[i].word;
			toUpper(arrVal);
			if(temp == arrVal) {
				//count++;
				//bruh = i;
				//soloVal = false;
				arr[i].count++;
				return;
			}
		}



		//if (soloVal) {
		entry newEnt;
		newEnt.word = token;
		newEnt.count = 1;
		arr[slot] = newEnt;
		slot++;
		//} else {
		//	arr[bruh].count = count;
		//}
	}
}

bool openFile(std::fstream& myfile, const std::string& myFileName, std::ios_base::openmode mode) {
	myfile.open(myFileName, mode);
	processFile(myfile);
	return myfile.is_open();
}

void closeFile(std::fstream& myfile) {
	if (myfile.is_open()) {
		myfile.close();
	}
}

/* serializes all content in myEntryArray to file outputfilename
 * returns  FAIL_FILE_DID_NOT_OPEN if cannot open outputfilename
 * 			FAIL_NO_ARRAY_DATA if there are 0 entries in myEntryArray
 * 			SUCCESS if all data is written and outputfilename closes OK
 * */
int writeArraytoFile(const std::string &outputfilename) {
	ofstream ofile;
	ofile.open(outputfilename.c_str());

	if (!ofile.is_open()) {
		return constants::FAIL_FILE_DID_NOT_OPEN;
	}
	else if (slot == 0) {
		return constants::FAIL_NO_ARRAY_DATA;
	}
	else {
		for (int i = 0; i < slot; i++) {
			string count = to_string(arr[i].count);
			string word = arr[i].word;
			ofile <<word + " " + count << endl;
		}
		return constants::SUCCESS;
	}
}

void sortArray(constants::sortOrder so) {
	if (so == constants::ASCENDING) {
		for (int i = 0; i < slot-1; i++) {
			for (int j = i+1; j < slot; j++) {
				string bruh = arr[i].word;
				string yeet = arr[j].word;
				toUpper(bruh);
				toUpper(yeet);
				if (bruh > yeet) {
					entry temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}

	else if (so == constants::DESCENDING) {
		for (int i = 0; i < slot - 1; i++) {
			for (int j = i + 1; j < slot; j++) {
				string bruh = arr[i].word;
				string yeet = arr[j].word;
				toUpper(bruh);
				toUpper(yeet);
				if (bruh < yeet) {
					entry temp = arr[j];
					arr[j] = arr[i];
					arr[i] = temp;
				}
			}
		}
	}
	else if (so == constants::NUMBER_OCCURRENCES) {
		for (int i = 0; i < slot - 1; i++) {
			for (int j = i + 1; j < slot; j++) {
				if (arr[i].count < arr[j].count) {
					entry temp = arr[j];
					arr[j] = arr[i];
					arr[i] = temp;
				}
			}
		}
	}
	else {
		return;
	}
}
//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!

