#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>


std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}


std::string removePunctuation(const std::string& str) {
    std::string result;
    for (char c : str) {
        if (!std::ispunct(c)) {
            result += c;
        }
    }
    return result;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::ofstream outputFile("output.txt");
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    std::map<std::string, int> wordFrequency;
    std::string line, word;

    // Reading input text from file
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            word = toLower(removePunctuation(word));
            wordFrequency[word]++;
        }
    }

    // Output information about all words
    std::cout << "Frequency dictionary:" << std::endl;
    for (const auto& pair : wordFrequency) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // Output information about the most frequently used word
    auto mostFrequentWord = std::max_element(wordFrequency.begin(), wordFrequency.end(),
                                             [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                                                 return a.second < b.second;
                                             });
    if (mostFrequentWord != wordFrequency.end()) {
        std::cout << "Most frequently used word: " << mostFrequentWord->first << " (" << mostFrequentWord->second << " times)" << std::endl;
    }

    // Write result to file
    outputFile << "Frequency dictionary:" << std::endl;
    for (const auto& pair : wordFrequency) {
        outputFile << pair.first << ": " << pair.second << std::endl;
    }
    if (mostFrequentWord != wordFrequency.end()) {
        outputFile << "Most frequently used word: " << mostFrequentWord->first << " (" << mostFrequentWord->second << " times)" << std::endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
