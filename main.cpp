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

