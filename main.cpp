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

void Trie::spellCheck(string word){
      if (search(word)) {
	 cout << word << " is spelled correctly!" << endl;
	 return;
      }

      cout << word << "' not found in dictionary.\n" ;
      cout << "Suggestions: ";

      TrieNode* curr = root;
      string prefix = "";
      for (char c : word) {
           int index = c - 'a';
           if (!curr->children[index]) {
	       break;
	   }
           prefix += c;
           curr = curr->children[index];
     }

     vector<string> suggestions;
     collectSuggestions( curr, prefix, suggestions);

     if (suggestions.empty()) {
 	cout << "No close matches found." << endl;
     } else {
	cout << endl;
	for (string s : suggestions) {
	    cout << " - "<< s << endl;
	}
     }
}

int main() {
   Trie trie;
   int choice;
   string word;

   cout << "==== Trie Spell Check ====";

   do {
      cout << "\n1. Insert word";
      cout << "\n2. Search word";
      cout << "\n3. Delete word";
      cout << "\n4. Spell check";
      cout << "\n5. Exit";
      cout << "\nEnter your choice: ";
      cin >> choice;

      switch (choice) {
       case 1:
          cout << "Enter word to insert: ";
          cin >> word;
          trie.insert(word);
          break;
       case 2:
          cout << "Enter word to insert: ";
          cin >> word;
          if (trie.search(word)) {
             cout << "Word found!\n";
          } else {
             cout << "Word not found.\n";
          }
          break;
       case 3:
          cout << "Enter word to delete: ";
          cin >> word;
          trie.deleteWord(word);
          break;
       case 4:
	  cout << "Enter word to spell check: ";
	  cin >> word;
	  trie.spellCheck(word);
	  break;
       case 5:
	  cout << "Exiting program...\n";
	  break;
       default:
	   cout << "Invalid choice.\n";
       }
   } while (choice != 5);

  return 0;
}
