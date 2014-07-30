// MMSEG C++ 11
// Copyright (C) 2014 Jack Deng <jackdeng@gmail.com>
// MIT LICENSE
//
// Based on http://yongsun.me/2013/06/simple-implementation-of-mmseg-with-python/
// Data files from mmseg4j https://code.google.com/p/mmseg4j/
// Compile with: g++ -Ofast -march=native -funroll-loops -DMMSEG_MAIN -x c++ -o mmseg -std=c++11 mmseg.h
// UTF-8 input only
#ifndef _SEGMENT_H_
#define _SEGMENT_H_
#pragma once

#include "trie.h"
#include "chunck.h"


class MMSeg {
public:

    inline static std::string trim(const std::string& s, const std::string& whitespace = "\r\n \t")
    {
        const auto first = s.find_first_not_of(whitespace);
        if (first == std::string::npos) return "";

        const auto last = s.find_last_not_of(whitespace);
        const auto range = last - first + 1;
        return s.substr(first, range);
    }


private:

    std::unordered_map<Char, int> char_freqs_;
    Trie dict_;

    std::vector<Chunk> get_chunks(StringIt _start, StringIt _end, int depth);

public:
    std::vector<String> segment(const String& s, int depth = 3);
    int load(const std::string& dict, const std::string& char_freqs = "");
};


#endif