//
// Created by László Molnár on 2017-11-15.
//

#ifndef CPP_LIGHTNING_FAST_WORD_FINDER_DOJO_LIGHTNINGWORDFINDER_HPP
#define CPP_LIGHTNING_FAST_WORD_FINDER_DOJO_LIGHTNINGWORDFINDER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

class LightningWordFinder
{
public:
    std::string getLongestWord(const std::string& text) {
        std::istringstream iss(text);
        std::vector<std::string> words{std::istream_iterator<std::string>{iss},
                                       std::istream_iterator<std::string>{}};
        //for(auto& word : words) std::cout << word << std::endl;
        std::sort(
                words.begin(),
                words.end(),
                [](const std::string &a, const std::string &b) {
                    return a.size() > b.size() || a.size() == b.size() && a > b;
                });
        for (auto &word : words) {
            bool ok = true;
            for (auto &c : word) {
                if (!isalpha(c)) {
                    ok = false;
                }
            }
            if (ok) {
                //std::cout << word << std::endl;
                return word;
            }
        }
    }
};

#endif //CPP_LIGHTNING_FAST_WORD_FINDER_DOJO_LIGHTNINGWORDFINDER_HPP

//Average Running Time: 2940723.000000ns