/*
 *
 */

#include <iostream>
#include <vector>
#include "spellchecker.h"
using namespace std;

int main() {
	vector<string> mispelledWords;
        spellCheck("document.txt", "dictionary.txt", mispelledWords);
	for(vector<string>::iterator itr = mispelledWords.begin(); itr != mispelledWords.end(); itr++) {
		cout << *itr;
		cout << endl;
	}
	return 0;
}
