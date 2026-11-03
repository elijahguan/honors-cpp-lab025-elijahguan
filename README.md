# Lab 025: Huffman Coding, Greedy Method, and Tries

## Description

This lab explores two important topics in algorithm design and data structures:

1. **Huffman Coding using the Greedy Method**
2. **Trie data structures for efficient string and prefix operations**

Huffman coding demonstrates how a greedy strategy can construct an optimal prefix code for a set of character frequencies. A trie demonstrates how strings can be organized by their shared prefixes.

## Student Implementation

The starter repository intentionally contains incomplete functions marked with `TODO`.

You are responsible for implementing the functions in:

    src/HuffmanTrie.cpp

### Huffman Coding

Implement:

- `buildHuffmanTree()`
- `generateHuffmanCodes()`
- `huffmanEncode()`
- `huffmanDecode()`

### Trie

Implement:

- `Trie::insert()`
- `Trie::contains()`
- `Trie::startsWith()`
- `Trie::wordsWithPrefix()`
- `Trie::collectWords()`

Do not remove the function declarations from the header.

Do not hard-code the expected test results.

---

## Part 1: Huffman Coding

Huffman coding is a lossless compression technique that constructs a binary prefix code based on character frequencies.

Characters that occur frequently should receive shorter codes, while less frequent characters generally receive longer codes.

### Greedy Strategy

The Huffman algorithm repeatedly combines the two least-frequent nodes.

For example, given character frequencies:

    a: 5
    b: 9
    c: 12
    d: 13
    e: 16
    f: 45

the algorithm repeatedly selects the two smallest frequencies and combines them.

Your implementation must use a min-priority queue to efficiently identify the two least-frequent nodes.

### Requirements

Implement `buildHuffmanTree()` so that it:

1. Creates one leaf node per character.
2. Places all nodes into a min-priority queue.
3. Removes the two lowest-frequency nodes.
4. Combines them into an internal node.
5. Reinserts the combined node.
6. Continues until one root remains.

Then implement `generateHuffmanCodes()` by traversing the tree.

Use:

    left  = 0
    right = 1

The resulting codes must be prefix-free.

### Encoding and Decoding

Implement:

    huffmanEncode()

and:

    huffmanDecode()

The following must hold:

    decode(encode(text)) == text

Your implementation must also handle the case where the input contains only one unique character.

### Complexity

Explain:

- Why a priority queue is appropriate.
- The time complexity of building the Huffman tree.
- The time complexity of generating the codes.
- The time complexity of encoding.
- The time complexity of decoding.

---

## Part 2: Greedy Method

Huffman coding is an example of a greedy algorithm.

At every step, the algorithm makes a locally optimal choice:

    Combine the two least-frequent nodes.

The important question is why this local choice leads to a globally optimal prefix code.

### Discussion Questions

1. What is the greedy choice made by Huffman's algorithm?
2. Why does the algorithm repeatedly choose the two least-frequent nodes?
3. What property makes Huffman coding suitable for a greedy strategy?
4. What is a prefix-free code?
5. Why is prefix-freeness important for decoding?
6. What would happen if one code were a prefix of another code?

---

## Part 3: Tries

A trie is a tree-based data structure designed for storing strings.

Unlike a binary search tree, a trie organizes data according to characters and shared prefixes.

For example:

    app
    apple
    application

share the prefix:

    app

A trie can exploit this shared structure.

### Required Operations

Implement:

    insert(word)

Insert a complete word into the trie.

Implement:

    contains(word)

Return true only when the complete word exists.

Implement:

    startsWith(prefix)

Return true when at least one stored word begins with the specified prefix.

Implement:

    wordsWithPrefix(prefix)

Return all complete words that begin with the specified prefix.

### Complexity

Assuming a word has length `L`, analyze the time complexity of:

- insertion
- exact search
- prefix search

Also discuss the space requirements of a trie.

---

## Important Implementation Requirements

Do not replace the required implementations with:

- `std::set`
- `std::map` as a substitute for the trie
- regular-expression searching
- library compression algorithms
- hard-coded lookup tables
- a sorting loop in place of the Huffman priority queue

The purpose of this lab is to implement and understand the underlying algorithms and data structures.

---

## Testing

Build the project:

    make

Run the demonstration:

    make run

Run the unit tests:

    make test

All provided tests should pass.

---

## Additional Questions

Answer the following questions as part of your analysis or class discussion:

1. Why is Huffman coding called a greedy algorithm?
2. What role does the priority queue play?
3. How does the frequency distribution affect the resulting Huffman codes?
4. Why can Huffman codes have different lengths?
5. Why does a trie make prefix queries efficient?
6. Compare exact search in a trie with exact search in a balanced binary search tree.
7. What happens to trie space usage when many words share prefixes?
8. What are the advantages and disadvantages of using a trie for a large dictionary?

## Deliverable

Your repository must contain:

- Completed Huffman tree implementation.
- Huffman code generation.
- Huffman encoding and decoding.
- Completed Trie implementation.
- Unit tests passing.
- A working C++17 build.
- No remaining `TODO` implementations.
