#include "trie.h"

void Trie::add(const String& word) {
    Node *current = &root_;
    for (auto ch : word) {
        auto it = current->trans_.find(ch);
        if (it == current->trans_.end()) {
            auto ret = current->trans_.emplace(ch, new Node{});
            current = ret.first->second;
        } else {
            current = it->second;
        }
    }
    current->val_ = true;
}

std::vector<StringItP> Trie::match_all(StringIt start, StringIt end) {
    std::vector<StringItP> ret;
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

size_t Trie::size() const { return root_.trans_.size(); }