# Vritex - Smart Spell Checker & Auto-Correct Engine

**Vritex** is a high-performance desktop spell checker and real-time auto-correct engine built in **C++** using fundamental **Data Structures & Algorithms (DSA)**. It moves beyond standard dictionary lookups by combining prefix trees, dynamic programming, phonetic encoding, and contextual graph analysis into a native Windows GUI application.

---

## Key Features

* **Prefix Auto-Complete (Trie + DFS):** Offers real-time predictions as you type by traversing a prefix tree using Depth-First Search.
* **Smart Auto-Correct (Dynamic Programming):** Uses the Levenshtein Distance algorithm to compute minimum edit operations (insertions, deletions, substitutions) for misspelled words.
* **Phonetic Matching (Soundex Algorithm):** Detects phonetically similar mistakes (e.g., matching `"fone"` to `"phone"`).
* **Word Frequency & Ranking:** Prioritizes suggestions based on usage frequency and edit distance using custom sorting logic.
* **Custom User Dictionary:** Allows users to add custom words dynamically at runtime.
* **Native Desktop GUI:** Built using native WinAPI for a lightweight, dependency-free graphical interface.

---

<<<<<<< HEAD
=======
## Work in Progress – Stay tuned for updates!
# Vritex - Smart Spell Checker & Auto-Correct Engine

**Vritex** is a high-performance desktop spell checker and real-time auto-correct engine built in **C++** using fundamental **Data Structures & Algorithms (DSA)**. It moves beyond standard dictionary lookups by combining prefix trees, dynamic programming, phonetic encoding, and contextual graph analysis into a native Windows GUI application.

---

## Key Features

* **Prefix Auto-Complete (Trie + DFS):** Offers real-time predictions as you type by traversing a prefix tree using Depth-First Search.
* **Smart Auto-Correct (Dynamic Programming):** Uses the Levenshtein Distance algorithm to compute minimum edit operations (insertions, deletions, substitutions) for misspelled words.
* **Phonetic Matching (Soundex Algorithm):** Detects phonetically similar mistakes (e.g., matching `"fone"` to `"phone"`).
* **Word Frequency & Ranking:** Prioritizes suggestions based on usage frequency and edit distance using custom sorting logic.
* **Context-Aware Suggestions:** Utilizes an adjacency list / graph-based model to evaluate two-word (bigram) context.
* **Custom User Dictionary:** Allows users to add custom words dynamically at runtime.
* **Native Desktop GUI:** Built using native WinAPI for a lightweight, dependency-free graphical interface.

---

>>>>>>> 06d6af1 (updated the readme file)
## Data Structures & Algorithms Used

* **Trees (Trie / Prefix Tree):** Enables O(L) word lookups and efficient autocomplete traversals.
* **Dynamic Programming:** 2D matrix DP table for computing edit distances between strings.
* **Graphs & Adjacency Lists:** Maps contextual relationships between consecutive words.
* **Sorting Algorithms:** Custom comparator-based sorting to order candidates by edit distance, phonetic similarity, and word frequency.
* **String Manipulation:** Implements the Soundex phonetic algorithm to generate 4-character phonetic encodings.
* **Standard Template Library (STL):** Utilizes `std::vector`, `std::string`, and `std::unordered_map`.

---

## Project Structure

```text
Vritex/
│
├── data/
│   ├── dictionary.txt        # Core dictionary dataset with word frequencies
│   └── user_dict.txt         # User-added custom words
│
├── include/
│   ├── Trie.h                # Trie & DFS autocomplete implementation
│   ├── EditDistance.h        # Levenshtein Distance (Dynamic Programming)
│   ├── Phonetic.h            # Soundex phonetic matching
│   └── VritexEngine.h        # Core engine integrating all modules
│
├── src/
│   └── main.cpp              # WinAPI GUI application entry point
│
├── README.md                 # Project documentation
<<<<<<< HEAD
```

## Team Members

* **Akshra Dang**
* **Satveer Kaur Brar**
* **Navdeep Kaur**
* **Arshpreet Kour**
* **Arushi**
=======
```
>>>>>>> 06d6af1 (updated the readme file)
