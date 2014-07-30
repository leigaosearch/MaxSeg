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

    void add(const String& word) {
      Node *current = &root_;
      for (auto ch: word) {
        auto it = current->trans_.find(ch);
        if (it == current->trans_.end()) {
          auto ret = current->trans_.emplace(ch, new Node{});
          current = ret.first->second;
        }
        else {
          current = it->second;
        }
      }
      current->val_ = true;
    }

    std::vector<StringP> match_all(StringIt start, StringIt end) {
      std::vector<StringP> ret;
      Node *current = &root_;
      StringIt _start = start;
      for (; start != end; ++start) {
        auto ch = *start;
        auto it = current->trans_.find(ch);
        if (it == current->trans_.end())
          break;
        current = it->second;
        if (current->val_) ret.emplace_back(_start, start + 1);
      }

      return ret;
    }

    size_t size() const { return root_.trans_.size(); }
  };
#endif