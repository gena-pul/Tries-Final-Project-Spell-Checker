Tries: Spell Check

   Many tree based data structures work by moving through their stored data in an orderly, step by step fashion to reach
a result. Building a spell check system with a Trie required thinking carefully about how each function behaves, how they 
call one another, and how the structure handles words internally. Every part of the code needed careful research to 
understand the underlying concepts and the extra helper tools required. The program ultimately supports insertion, 
search, deletion and spell checking, while two supporting functions collectSuggestions() and deleteHelper() make
these operations possible. All functions work together to form a quick and reliable spell check system.

   One of the main goals was to keep the runtime for each operation as fast as possible when designing the Trie. In a 
Trie, the running time for most functions depends on the length of the word, not the size of the dictionary. For 
example, the insert function runs in O(L) time, where L is the number of characters in the word. It simply moves
through each character once and creates node as needed. The search function also operates in O(L) time, following
the path of characters until the end. The delete function also has a runtime of O(L), even though it uses recursion,
because it only descends one level per character. Its helper function ensures nodes are properly removed without 
breaking shared prefixes. Spell check begins with a search that runs in O(L) time, but collecting suggestions can vary.
In the worst case, gathering suggestions below a node can take time proportional to all stored words that share that prefix.

   Although the Trie performs quickly, it is not free of limitations. One drawback is that each node stores 26 pointers, one
for lowercase letter, making it relatively memory heavy. The program also only handles lowercase letters, ignoring
uppercase input. Another limitation is that suggestion collection is prefix based, meaning it compares the beginning of the
word rather than its overall similarity. Additionally, the program currently accepts any character the user enters, including
undefined ones leading to weird behavior. Despite these constraints, the system remains highly effective. It offers very fast 
lookups, provides natural dictionary like features, and produces accurate suggestions almost instantly.

   Overall, the program operates efficently and reaches its goals. The runtime are well optimized and the structure is clean.
The Trie performs its tasks quickly and reliably. While a few limitations exist, they are manageable and do not overshadow
the strong performance or usefulness of the spell check system. The advantages ultimately outweigh the disadvantages, 
resulting in a well functioning and dependable program.
