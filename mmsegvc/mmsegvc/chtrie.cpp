#include "chtrie.h"

void ChTrie::insert(const ChString& word) {




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

std::vector<ChStringItP> ChTrie::match_all(ChStringIt start, ChStringIt end) {
    std::vector<ChStringItP> ret;
    Node *current = &root_;
    ChStringIt _start = start;
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

size_t ChTrie::size() const { return root_.trans_.size(); }