#include <iostream>

#include <fstream>
#include <string>
#include <cerrno>
#include <chrono>
#include "LightningWordFinder.hpp"

std::string getFileContents(const std::string& filename)
{
    std::string contents;
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
    if(in) {
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
    }else{
        std::cout << "File reading was not successful: " << filename << std::endl;
    }
    return contents;
}

double runParserPerformanceTests(const std::string& text, const unsigned numOfRuns)
{
    unsigned penalty = 0;
    std::string longestWord;
    auto begin = std::chrono::high_resolution_clock::now();
    for(unsigned i = 0; i < numOfRuns; ++i)
    {
        //std::cout << "Run: " << i << std::endl;
        LightningWordFinder parser;
        longestWord = parser.getLongestWord(text);

        if (longestWord != "Constantinopolitan")
        {
            std::cout << "The longest word is not what I wanted to see.. '" << longestWord << "'" << std::endl;
            penalty += 20;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    return duration / numOfRuns + penalty;
}

int main() {
    std::string text = getFileContents("../txt/history-of-egypt-chaldea-syria-babylonia-assyria.txt");
    std::cout << "Text length: " << text.size() << std::endl;
    if(text.empty()) return 1;

    double avgRuntime = runParserPerformanceTests(text, 1000);
    std::cout << "Average Running Time: " << std::fixed << avgRuntime << "ns" << std::endl;

    return 0;
}