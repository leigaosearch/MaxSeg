#ifndef _TRIE_H_
#define _TRIE_H_
#include "common.h"

struct Trie {
    struct Node {
      std::unordered_map<Char, Node*> trans_;
      bool val_ = false;

      ~Node() {
        for (auto& it: trans_) delete it.second;
        trans_.clear();
      }
    };

    Node root_;

    void add(const String& word);
    std::vector<StringItP> match_all(StringIt start, StringIt end);
    size_t size() const;
  };
#endif