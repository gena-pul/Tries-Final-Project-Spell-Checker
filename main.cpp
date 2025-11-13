#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TrieNode {
   TrieNode* children[26];
   bool isEndOfWord;

   TrieNode() {
      isEndOfWord = false;
      for(int i = 0; i < 26; i++){
	children[i] = nullptr;
      }
   }
};

class Trie {
private: 
    TrieNode* root;

    void collectSuggestions(TrieNode* node, string fix, vector<string>& suggestions);
    bool deleteHelper(TrieNode* node, string word, int depth);

public:
    Trie();

    void insert(string word);
    bool search(string word);
    void deleteWord(string word);
    void spellCheck(string word);
};

Trie::Trie() {
     root = new TrieNode();
}

void Trie::collectSuggestions(TrieNode* node, string fix, vector<string>& suggestions) {
    if (node->isEndOfWord) {
	suggestions.push_back(fix);
    }

    for (int i = 0; i < 26; i++) {
	if (node->children[i]) {
	   char nextChar = 'a' + i;
	   collectSuggestions(node->children[i], fix + nextChar, suggestions);
	}
    }
}

bool Trie::deleteHelper(TrieNode* node, string word, int depth) {
    if (!node) {
       return false;
    }

    if (depth == word.size()) {
       if (!node->isEndOfWord) {
    	   return false;
       }
       node->isEndOfWord = false;

       for (int i = 0; i < 26; i++) {
           if (node->children[i]) {
	       return false;
           }
       }
       return true;
    }

   int in = word[depth] - 'a';
   if (deleteHelper(node->children[in], word, depth + 1)) {
      delete node->children[in];
      node->children[in] = nullptr;

     if (!node->isEndOfWord) {
	for (int i = 0; i < 26; i++) {
	    if (node->children[i]) {
  		return false;
	    }
	}
	return true;
     }
   }

   return false;
}

void Trie::insert(string word) {
       TrieNode* curr = root;
	for (char c : word) {
	    int in = c - 'a';
	   if (!curr->children[in]) {
	       curr->children[in] = new TrieNode();
	   }
	   curr = curr->children[in];
	}
	curr->isEndOfWord = true;
	cout << "Inserted: " << word << endl;
}

bool Trie::search(string word) {
	TrieNode* curr = root;
	for (char c : word) {
           int in = c - 'a';
	   if (!curr->children[in]) {
	      return false;
	   }
	   curr = curr->children[in];
	}
	return curr->isEndOfWord;
}

void Trie::deleteWord(string word) {
	if (search(word)) {
	   deleteHelper(root, word, 0);
	   cout << "Deleted: " << word << endl;
	} else {
	   cout << "Word is not found!" << endl;
	}
}

}
