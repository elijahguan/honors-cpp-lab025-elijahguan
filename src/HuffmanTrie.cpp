#include "project/HuffmanTrie.hpp"

#include <queue>
#include <stdexcept>

HuffmanNode::HuffmanNode(char ch, std::size_t freq)
    : character(ch), frequency(freq) {
}

HuffmanNode::HuffmanNode(
    std::size_t freq,
    std::shared_ptr<HuffmanNode> leftChild,
    std::shared_ptr<HuffmanNode> rightChild)
    : character('\0'),
      frequency(freq),
      left(std::move(leftChild)),
      right(std::move(rightChild)) {
}

bool HuffmanNode::isLeaf() const {
    return left == nullptr && right == nullptr;
}

std::shared_ptr<HuffmanNode> buildHuffmanTree(
    const std::unordered_map<char, std::size_t>& frequencies) {

    // TODO: Implement the Huffman greedy algorithm.
    //
    // 1. Create one leaf node for each character.
    // 2. Insert all nodes into a min-priority queue ordered by frequency.
    // 3. Repeatedly remove the two least-frequent nodes.
    // 4. Create a new internal node whose frequency is their sum.
    // 5. Insert the new node back into the priority queue.
    // 6. Continue until only one node remains.
    //
    // Handle an empty frequency table and the single-character case.
    //
    // Do not use a sorting-based shortcut in place of the priority queue.

    (void)frequencies;

    throw std::logic_error("TODO: implement buildHuffmanTree");
}

std::unordered_map<char, std::string> generateHuffmanCodes(
    const std::shared_ptr<HuffmanNode>& root) {

    // TODO: Traverse the Huffman tree to generate codes.
    //
    // Convention:
    //   left edge  -> '0'
    //   right edge -> '1'
    //
    // A leaf represents one character.
    // Store the complete bit string for each character.
    //
    // Special case:
    //   If the tree contains only one character, assign a valid
    //   non-empty code such as "0".

    (void)root;

    throw std::logic_error("TODO: implement generateHuffmanCodes");
}

std::string huffmanEncode(
    const std::string& text,
    const std::unordered_map<char, std::string>& codes) {

    // TODO: Replace every character with its Huffman code.
    //
    // The function should preserve character order and concatenate
    // the corresponding bit strings.
    //
    // Throw an exception if the input contains a character for which
    // no Huffman code exists.

    (void)text;
    (void)codes;

    throw std::logic_error("TODO: implement huffmanEncode");
}

std::string huffmanDecode(
    const std::string& encoded,
    const std::shared_ptr<HuffmanNode>& root) {

    // TODO: Decode the bit string by traversing the Huffman tree.
    //
    // '0' means move left.
    // '1' means move right.
    //
    // Whenever a leaf is reached, append its character and return
    // to the root for the next encoded character.
    //
    // Reject invalid bit strings.
    // Handle the single-character tree correctly.

    (void)encoded;
    (void)root;

    throw std::logic_error("TODO: implement huffmanDecode");
}


// --------------------------------------------------
// Trie
// --------------------------------------------------

Trie::Trie()
    : root(std::make_unique<TrieNode>()) {
}

void Trie::insert(const std::string& word) {

    // TODO: Insert the word character by character.
    //
    // Create a child node when the required edge does not exist.
    // Mark the final node as a complete word.
    //
    // Empty-string behavior should be handled consistently.

    (void)word;
}

bool Trie::contains(const std::string& word) const {

    // TODO: Traverse the trie one character at a time.
    // Return true only when the complete word was inserted.

    (void)word;

    return false;
}

bool Trie::startsWith(const std::string& prefix) const {

    // TODO: Traverse the trie using the prefix.
    // Return true if the prefix path exists.

    (void)prefix;

    return false;
}

std::vector<std::string> Trie::wordsWithPrefix(
    const std::string& prefix) const {

    // TODO: Find the node representing prefix, then recursively
    // collect all complete words below that node.
    //
    // Return complete words, not just suffixes.

    (void)prefix;

    return {};
}

void Trie::collectWords(
    const TrieNode* node,
    const std::string& current,
    std::vector<std::string>& results) const {

    // TODO: Recursively traverse descendants of node.
    //
    // Add current to results when node->isWord is true.
    // Continue through every child.

    (void)node;
    (void)current;
    (void)results;
}
