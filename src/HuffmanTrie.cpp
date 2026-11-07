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

    if (frequencies.empty()) {
        return nullptr;
    }

    auto compare = [](const std::shared_ptr<HuffmanNode>& a,
                      const std::shared_ptr<HuffmanNode>& b) {
        return a->frequency > b->frequency;
    };

    std::priority_queue<
        std::shared_ptr<HuffmanNode>,
        std::vector<std::shared_ptr<HuffmanNode>>,
        decltype(compare)> nodes(compare);

    for (const auto& entry : frequencies) {
        nodes.push(std::make_shared<HuffmanNode>(entry.first, entry.second));
    }

    while (nodes.size() > 1) {
        auto left = nodes.top();
        nodes.pop();

        auto right = nodes.top();
        nodes.pop();

        auto parent = std::make_shared<HuffmanNode>(
            left->frequency + right->frequency,
            left,
            right);

        nodes.push(parent);
    }

    return nodes.top();
}

std::unordered_map<char, std::string> generateHuffmanCodes(
    const std::shared_ptr<HuffmanNode>& root) {

    std::unordered_map<char, std::string> codes;

    if (!root) {
        return codes;
    }

    std::vector<std::pair<std::shared_ptr<HuffmanNode>, std::string>> pending;
    pending.push_back({root, ""});

    while (!pending.empty()) {
        auto current = pending.back();
        pending.pop_back();

        if (current.first->isLeaf()) {
            // A single-character tree needs a non-empty code.
            codes[current.first->character] =
                current.second.empty() ? "0" : current.second;
        } else {
            if (current.first->right) {
                pending.push_back({current.first->right, current.second + "1"});
            }
            if (current.first->left) {
                pending.push_back({current.first->left, current.second + "0"});
            }
        }
    }

    return codes;
}

std::string huffmanEncode(
    const std::string& text,
    const std::unordered_map<char, std::string>& codes) {

    std::string encoded;

    for (char ch : text) {
        auto it = codes.find(ch);
        if (it == codes.end()) {
            throw std::invalid_argument("No Huffman code for input character");
        }
        encoded += it->second;
    }

    return encoded;
}

std::string huffmanDecode(
    const std::string& encoded,
    const std::shared_ptr<HuffmanNode>& root) {

    if (!root) {
        throw std::invalid_argument("Cannot decode without a Huffman tree");
    }

    std::string decoded;

    if (root->isLeaf()) {
        for (char bit : encoded) {
            if (bit != '0') {
                throw std::invalid_argument("Invalid bit for single-character tree");
            }
            decoded += root->character;
        }
        return decoded;
    }

    auto current = root;

    for (char bit : encoded) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        } else {
            throw std::invalid_argument("Encoded string contains a non-bit character");
        }

        if (!current) {
            throw std::invalid_argument("Encoded string follows an invalid tree path");
        }

        if (current->isLeaf()) {
            decoded += current->character;
            current = root;
        }
    }

    if (current != root) {
        throw std::invalid_argument("Encoded string ends partway through a code");
    }

    return decoded;
}



// --------------------------------------------------
// Trie
// --------------------------------------------------

Trie::Trie()
    : root(std::make_unique<TrieNode>()) {
}

void Trie::insert(const std::string& word) {
    TrieNode* node = root.get();

    for (char ch : word) {
        auto& child = node->children[ch];
        if (!child) {
            child = std::make_unique<TrieNode>();
        }
        node = child.get();
    }

    node->isWord = true;
}

bool Trie::contains(const std::string& word) const {
    const TrieNode* node = root.get();

    for (char ch : word) {
        auto it = node->children.find(ch);
        if (it == node->children.end()) {
            return false;
        }
        node = it->second.get();
    }

    return node->isWord;
}

bool Trie::startsWith(const std::string& prefix) const {
    const TrieNode* node = root.get();

    for (char ch : prefix) {
        auto it = node->children.find(ch);
        if (it == node->children.end()) {
            return false;
        }
        node = it->second.get();
    }

    return true;
}

std::vector<std::string> Trie::wordsWithPrefix(
    const std::string& prefix) const {

    const TrieNode* node = root.get();

    for (char ch : prefix) {
        auto it = node->children.find(ch);
        if (it == node->children.end()) {
            return {};
        }
        node = it->second.get();
    }

    std::vector<std::string> results;
    collectWords(node, prefix, results);
    return results;
}

void Trie::collectWords(
    const TrieNode* node,
    const std::string& current,
    std::vector<std::string>& results) const {

    if (!node) {
        return;
    }

    if (node->isWord) {
        results.push_back(current);
    }

    for (const auto& child : node->children) {
        collectWords(child.second.get(), current + child.first, results);
    }
}