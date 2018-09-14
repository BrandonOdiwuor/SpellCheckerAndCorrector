/*
 * File: Spellchecker.h
 * Author: Brandon Wayne Odiwuor
 * -----------------------------
 * This file implements a deterministic spellchecker using a prefix tree(trie)
 */

#include <fstream>
#include <algorithm>
#include <string.h>
#include "trie.h"
#include <vector>
#include <iostream>

/*
 * Function: spellChecker
 * Usage: vector<string> mispelledWords = spellCheck(document, dictionary);
 * ------------------------------------------------------------------------
 *  Returns a vector containing all mispelled words in the document checked
 *  against the dictionary
 */
std::vector<std::string> *spellCheck(std::string document, std::string dictionary);

/*
 * Funtion: createDictionary
 * Usage: TrieNode *dictionary = createDictionary(fileName);
 * ---------------------------------------------------------
 *  Returns the root node of the trie data structure porpulated with words from
 *  the file with the name provided to be used as  a dictionary
 */

TrieNode *createDictionary(std::string dictionary);

/*
 * Function: spellCheckLine
 * Usage: spellCheck(mispelledWords, dictionary, line);
 * --------------------------
 * Helper function for spellCheck function that porpulates the mispelledWords
 * vecotore with mispelled words from line
 */

void spellCheckLine(std::vector<std::string> *mispelledWords, TrieNode *dictionary, 
		    std::string line);

/* Funtion Implementations */


std::vector<std::string> *spellCheck(std::string document, std::string dictionaryFile) {
	TrieNode *dictionary = createDictionary(dictionaryFile);
	
	std::vector<std::string> *mispelledWords;

	std::ifstream infile;
	infile.open(document.c_str());
	std::string line;
	while(getline(infile, line)) {
		spellCheckLine(mispelledWords, dictionary, line);
	}

	return mispelledWords;
}

void spellCheckLine(std::vector<std::string> *mispelledWords, TrieNode *dictionary, std::string line) {
	std::vector<std::string> words;
	char * str = new char [line.length()+1];
	strcpy (str, line.c_str());
	char * token = strtok(str, " ,.-");
	while (token != NULL) {	
		if(!search(dictionary, token)) {
			words.push_back(token);
			std::cout << token << std::endl;
		}
		token = strtok (NULL, " ,.-");
	}
	delete[] str;
}

TrieNode *createDictionary(std::string dictionary) {
	TrieNode *root = new TrieNode;
	std::ifstream infile;
	std::string word;
	infile.open(dictionary.c_str());
	while(getline(infile, word)) {
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		insert(root, word);
	}
	infile.close();
	return root;
}
