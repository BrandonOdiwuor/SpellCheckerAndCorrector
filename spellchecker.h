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
 * Funtion: createDictionary
 * Usage: TrieNode *dictionary = createDictionary(fileName);
 * ---------------------------------------------------------
 *  Returns the root node of the trie data structure porpulated with words from
 *  the file with the name provided to be used as  a dictionary
 */

TrieNode *createDictionary(std::string dictionary);

/*
 * Function: spellChecker
 * Usage: vector<string> mispelledWords = spellCheck(document, dictionary, mispelledWords);
 * ------------------------------------------------------------------------
 *  Porpulates mispelledWords vector with all mispelled words in the document checked
 *  against the dictionary
 */

void spellCheck(std::string document, std::string dictionary, std::vector<std::string> &mispelledWords);

/*
 * Function: spellCheckLine
 * Usage: spellCheck(mispelledWords, dictionary, line);
 * --------------------------
 * Helper function for spellCheck function that porpulates the mispelledWords
 * vecotore with mispelled words from line
 */

void spellCheckLine(std::vector<std::string> &mispelledWords, TrieNode *dictionary, 
		    std::string line);

/* Funtion Implementations */


void spellCheck(std::string document, std::string dictionaryFile, std::vector<std::string> &mispelledWords) {
	TrieNode *dictionary = createDictionary(dictionaryFile);

	std::ifstream infile;
	infile.open(document.c_str());
	std::string line;
	while(getline(infile, line)) {
		spellCheckLine(mispelledWords, dictionary, line);
	}
}

void spellCheckLine(std::vector<std::string> &words, TrieNode *dictionary, std::string line) {
	char * str = new char [line.length()+1];
	strcpy (str, line.c_str());
	char * token = strtok(str, " ,.-");
	while (token != NULL) {	
		if(!search(dictionary, token)) {
			words.push_back(token);
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
