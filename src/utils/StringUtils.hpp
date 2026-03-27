#pragma once

#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

namespace NewTCG::utils {
    inline bool ends_with(const std::string& str, const std::string& suffix) {
        if (suffix.size() > str.size()) {
            return false; // 접미사가 문자열보다 길면 false
        }
        return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
    }

    inline bool starts_with(const std::string& str, const std::string& prefix) {
        if (str.size() < prefix.size()) {
            return false; // 접미사가 문자열보다 길면 false
        }
        return str.compare(0, prefix.length(), prefix) == 0;
    }
    
    inline std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end;

        while ((end = str.find(delimiter, start)) != std::string::npos) {
            tokens.push_back(str.substr(start, end - start));
            start = end + delimiter.length();
        }

        tokens.push_back(str.substr(start)); // 마지막 토큰
        return tokens;
    }

    inline std::string ltrim(const std::string& s) {
        return std::string(std::find_if_not(s.begin(), s.end(), ::isspace), s.end());
    }

    inline std::string rtrim(const std::string& s) {
        return std::string(s.begin(), std::find_if_not(s.rbegin(), s.rend(), ::isspace).base());
    }

}