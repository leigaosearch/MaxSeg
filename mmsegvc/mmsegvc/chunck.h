#ifndef _CHUNCK_H_
#define _CHUNCK_H_
#include "trie.h"
struct Chunk {
    std::vector<StringItP> words_;
    size_t length_ = 0;
    float mean_ = 0, var_ = 0, degree_ = 0;

    Chunk(std::vector<StringItP> words, const std::unordered_map<Char, int>& chars) : words_(std::move(words)) {
        length_ = std::accumulate(words_.begin(), words_.end(), size_t(0), [&](size_t n, const StringItP& w) { return n + sementlength(w); });
        mean_ = float(length_) / words_.size();
        var_ = -std::accumulate(words_.begin(), words_.end(), float(0), [&](size_t n, const StringItP& w) { return  n + (sementlength(w) - mean_) * (sementlength(w) - mean_); }) / words_.size();

        for (auto& w : words_) {
            if (sementlength(w) != 1) continue;
            auto it = chars.find(*w.first);
            if (it != chars.end())
                degree_ += log(float(it->second));
        }
    }

    std::string to_string() const {
        std::string s;
        for (auto& w : words_) { s += to_utf8(String(w.first, w.second)) + " "; }
        s += "(" + std::to_string(length_) + " " + std::to_string(mean_) + " " + std::to_string(var_) + " " + std::to_string(degree_) + ")";
        return s;
    }

};
#endif