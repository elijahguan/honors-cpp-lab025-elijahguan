#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "project/HuffmanTrie.hpp"

#include <string>
#include <unordered_map>
#include <vector>

TEST_CASE("Huffman tree combines frequencies correctly") {
    std::unordered_map<char, std::size_t> frequencies = {
        {'a', 5},
        {'b', 9},
        {'c', 12},
        {'d', 13},
        {'e', 16},
        {'f', 45}
    };

    auto root = buildHuffmanTree(frequencies);

    REQUIRE(root != nullptr);
    REQUIRE(root->frequency == 100);
    REQUIRE(!root->isLeaf());
}

TEST_CASE("Huffman codes are prefix-free") {
    std::unordered_map<char, std::size_t> frequencies = {
        {'a', 5},
        {'b', 9},
        {'c', 12},
        {'d', 13},
        {'e', 16},
        {'f', 45}
    };

    auto root = buildHuffmanTree(frequencies);
    auto codes = generateHuffmanCodes(root);

    REQUIRE(codes.size() == frequencies.size());

    for (const auto& first : codes) {
        REQUIRE(!first.second.empty());

        for (const auto& second : codes) {
            if (first.first == second.first) {
                continue;
            }

            REQUIRE(
                second.second.rfind(first.second, 0) != 0);
        }
    }
}

TEST_CASE("Huffman encoding and decoding round trip") {
    std::string text = "this is an example";

    std::unordered_map<char, std::size_t> frequencies;

    for (char c : text) {
        ++frequencies[c];
    }

    auto root = buildHuffmanTree(frequencies);
    auto codes = generateHuffmanCodes(root);

    std::string encoded = huffmanEncode(text, codes);
    std::string decoded = huffmanDecode(encoded, root);

    REQUIRE(decoded == text);
    REQUIRE(encoded.size() >= text.size());
}

TEST_CASE("Huffman handles a single unique character") {
    std::unordered_map<char, std::size_t> frequencies = {
        {'x', 5}
    };

    auto root = buildHuffmanTree(frequencies);
    auto codes = generateHuffmanCodes(root);

    REQUIRE(codes.at('x') == "0");

    std::string encoded = huffmanEncode("xxxxx", codes);
    REQUIRE(encoded == "00000");
    REQUIRE(huffmanDecode(encoded, root) == "xxxxx");
}

TEST_CASE("Trie inserts and searches complete words") {
    Trie trie;

    trie.insert("cat");
    trie.insert("car");
    trie.insert("cart");

    REQUIRE(trie.contains("cat"));
    REQUIRE(trie.contains("car"));
    REQUIRE(trie.contains("cart"));

    REQUIRE_FALSE(trie.contains("ca"));
    REQUIRE_FALSE(trie.contains("can"));
}

TEST_CASE("Trie distinguishes prefixes from complete words") {
    Trie trie;

    trie.insert("algorithm");

    REQUIRE(trie.startsWith("alg"));
    REQUIRE(trie.startsWith("algorithm"));
    REQUIRE_FALSE(trie.startsWith("data"));

    REQUIRE_FALSE(trie.contains("alg"));
    REQUIRE(trie.contains("algorithm"));
}

TEST_CASE("Trie returns all words with a prefix") {
    Trie trie;

    trie.insert("app");
    trie.insert("apple");
    trie.insert("application");
    trie.insert("banana");

    std::vector<std::string> results =
        trie.wordsWithPrefix("app");

    REQUIRE(results.size() == 3);
    REQUIRE(
        std::find(results.begin(), results.end(), "app")
        != results.end());
    REQUIRE(
        std::find(results.begin(), results.end(), "apple")
        != results.end());
    REQUIRE(
        std::find(results.begin(), results.end(), "application")
        != results.end());
}

TEST_CASE("Trie returns no words for a missing prefix") {
    Trie trie;

    trie.insert("tree");
    trie.insert("trie");

    REQUIRE(trie.wordsWithPrefix("xyz").empty());
}

TEST_CASE("Huffman handles empty input gracefully") {
    std::unordered_map<char, std::size_t> frequencies = {};

    auto root = buildHuffmanTree(frequencies);
    auto codes = generateHuffmanCodes(root);

    REQUIRE(root == nullptr);
    REQUIRE(codes.empty());
    REQUIRE(huffmanEncode("", codes) == "");
}

TEST_CASE("Huffman rejects unknown characters during encoding") {
    std::unordered_map<char, std::size_t> frequencies = {
        {'a', 2},
        {'b', 3}
    };

    auto root = buildHuffmanTree(frequencies);
    auto codes = generateHuffmanCodes(root);

    REQUIRE_THROWS_AS(huffmanEncode("abz", codes), std::invalid_argument);
}

TEST_CASE("Trie handles empty string and repeated inserts") {
    Trie trie;

    trie.insert("");
    REQUIRE(trie.contains(""));
    REQUIRE(trie.startsWith(""));
    REQUIRE(trie.wordsWithPrefix("").size() == 1);

    trie.insert("cat");
    trie.insert("cat");
    REQUIRE(trie.contains("cat"));
    REQUIRE(trie.wordsWithPrefix("ca").size() == 1);
}

TEST_CASE("Trie supports multiple branches and nested prefixes") {
    Trie trie;

    trie.insert("car");
    trie.insert("cart");
    trie.insert("care");
    trie.insert("dog");

    REQUIRE(trie.startsWith("car"));
    REQUIRE(trie.startsWith("ca"));
    REQUIRE(trie.startsWith("dog"));
    REQUIRE_FALSE(trie.startsWith("doe"));

    auto carWords = trie.wordsWithPrefix("car");
    REQUIRE(carWords.size() == 3);
    REQUIRE(std::find(carWords.begin(), carWords.end(), "car") != carWords.end());
    REQUIRE(std::find(carWords.begin(), carWords.end(), "cart") != carWords.end());
    REQUIRE(std::find(carWords.begin(), carWords.end(), "care") != carWords.end());
}

TEST_CASE("Trie preserves word order only within prefix collections") {
    Trie trie;

    trie.insert("zebra");
    trie.insert("zero");
    trie.insert("zen");

    auto results = trie.wordsWithPrefix("z");
    REQUIRE(results.size() == 3);
    REQUIRE(std::find(results.begin(), results.end(), "zen") != results.end());
    REQUIRE(std::find(results.begin(), results.end(), "zero") != results.end());
    REQUIRE(std::find(results.begin(), results.end(), "zebra") != results.end());
}
