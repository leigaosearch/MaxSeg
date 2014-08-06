#ifndef _TRIE_H_
#define _TRIE_H_
#include "common.h"

class ChTrie {
private:
    struct Node {
      std::unordered_map<Chchar, Node*> trans_;
      bool val_ = false;

      ~Node() {
        for (auto& it: trans_) delete it.second;
        trans_.clear();
      }
    };

    Node root_;
public:
    void insert(const ChString& word);
    std::vector<ChStringItP> match_all(ChStringIt start, ChStringIt end);
    size_t size() const;
  };
#endif