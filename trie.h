/*
 * File: trie.h
 * Author: Brandon Wayne Odiwuor
 * Date: Septermber 11th, 2018
 * -----------------------------
 *  This file exports implementation of Trie data structure
 */

#ifndef _trie_h
#define _trie_h

#include <iostream>
#include <string>

/*
 * Type: TrieNode
 * --------------
 *  This structure stores properties of nodes of the trie(radix tree)
 */

struct TrieNode {
	char character;
	TrieNode *children[26] = {NULL};
	bool isEndOfWord = false;
};

/*
 * Function: createNode
 * Usage: TrieNode *node = createNode(char c);
 * -------------------------------------------
 *  Creates a Node and initializes its character property to c,
 *  Returns a pointer to the node created
 */

TrieNode *createNode(char character);

/*
 * Function: insert
 * Usage: insert(root, word);
 * --------------------------
 *  Inserts word into trie whose root has been specified
 */

void insert(TrieNode *root, std::string word);

/*
 * Function: search
 * Usage: search(root, word);
 * --------------------------
 *  Returns true if word is in the trie whose root is previded and false otherwise
 */

bool search(TrieNode *root, std::string word);

/* Function Implementations */

TrieNode *createNode(char character) {
        TrieNode *newNode = new TrieNode;
        newNode->character = character;
        return newNode;
}

void insert(TrieNode *root, std::string word) {
	TrieNode *currentNode = root;
	for(int i = 0; i < word.length(); i++) {
		int index = word[i] - 'a';
		if(!currentNode->children[index]) {
			TrieNode *newNode = createNode(word[i]);
			currentNode->children[index] = newNode;
		}
		currentNode = currentNode->children[index];
	}
	currentNode->isEndOfWord = true;
}

bool search(TrieNode *root, std::string word) {
	TrieNode *currentNode = root;
        for(int i = 0; i < word.length(); i++) {
                int charIndex = word[i] - 'a';
		if(!currentNode->children[charIndex]) {
			return false;
		}
		currentNode = currentNode->children[charIndex];
	}
	return currentNode->isEndOfWord;
}

#endif
