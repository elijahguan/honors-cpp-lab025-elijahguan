#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

struct HuffmanNode {
    char character;
    std::size_t frequency;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;

    HuffmanNode(char ch, std::size_t freq);
    HuffmanNode(
        std::size_t freq,
        std::shared_ptr<HuffmanNode> leftChild,
        std::shared_ptr<HuffmanNode> rightChild);

    bool isLeaf() const;
};

// Build a Huffman tree from character frequencies.
std::shared_ptr<HuffmanNode> buildHuffmanTree(
    const std::unordered_map<char, std::size_t>& frequencies);

// Generate the binary Huffman code for every character.
std::unordered_map<char, std::string> generateHuffmanCodes(
    const std::shared_ptr<HuffmanNode>& root);

// Encode text using a Huffman code table.
std::string huffmanEncode(
    const std::string& text,
    const std::unordered_map<char, std::string>& codes);

// Decode a Huffman bit string using the Huffman tree.
std::string huffmanDecode(
    const std::string& encoded,
    const std::shared_ptr<HuffmanNode>& root);


// --------------------------------------------------
// Trie
// --------------------------------------------------

class Trie {
public:
    Trie();

    // Insert a complete word.
    void insert(const std::string& word);

    // Return true if the complete word exists.
    bool contains(const std::string& word) const;

    // Return true if at least one stored word starts with prefix.
    bool startsWith(const std::string& prefix) const;

    // Return all stored words beginning with prefix.
    std::vector<std::string> wordsWithPrefix(
        const std::string& prefix) const;

private:
    struct TrieNode {
        bool isWord = false;
        std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    };

    std::unique_ptr<TrieNode> root;

    // Helper for recursive prefix collection.
    void collectWords(
        const TrieNode* node,
        const std::string& current,
        std::vector<std::string>& results) const;
};
