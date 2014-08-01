#include "Segment.h"
#include "mmseg.h"
#include <vld.h> 
std::vector<String>MMSeg::segment(const String& s, int depth) {
    std::vector<String> ret;
    auto start = s.begin(), end = s.end();
    while (start != end) {
        auto chunks = get_chunks(start, end, depth);
        auto best = std::max_element(chunks.begin(), chunks.end(), [&](const Chunk& x, const Chunk& y) {
            return std::tie(x.length_, x.mean_, x.var_, x.degree_) < std::tie(y.length_, y.mean_, y.var_, y.degree_);
        });

        for (auto& c : chunks) std::cout << c.to_string() << std::endl; std::cout << std::endl;
        auto& word = best->words_.front();
        start += sementlength(word);
        ret.emplace_back(String(word.first, word.second));
    }

    return ret;
}

int MMSeg::load(const std::string& dict, const std::string& char_freqs) {
    std::ifstream din(dict);
    if (!din.is_open()) return -1;
    while (din.good()) {
        std::string line;
        if (!std::getline(din, line)) break;
        std::u16string word = from_utf8(trim(line));
        dict_.add(word);
    }
    din.close();

    if (char_freqs.empty()) return 0;

    std::ifstream fin(char_freqs);
    if (!fin.is_open()) return -1;
    while (fin.good()) {
        std::string line;
        if (!std::getline(fin, line)) break;
        auto s = trim(line);
        size_t pos = s.find(' ');
        if (pos != std::string::npos) {
            auto word = from_utf8(s.substr(0, pos));
            int freq = std::stoi(s.substr(pos + 1));
            char_freqs_.emplace(word[0], freq);
        }
    }
    fin.close();

    std::cout << "Loaded Dict: " << dict_.size() << ", Freq: " << char_freqs_.size() << std::endl;
    return 0;
}

std::vector<Chunk>  MMSeg::get_chunks(StringIt _start, StringIt _end, int depth) {
    std::vector<Chunk> ret;
    std::function<void(StringIt, StringIt, int, std::vector<StringItP>)> get_chunks_it = [&](StringIt start, StringIt end, int n, std::vector<StringItP> segs) {
        if (n == 0 || start == end) {
            ret.emplace_back(std::move(segs), char_freqs_);
        } else {
            auto m = dict_.match_all(start, end);
            for (auto& w : m) {
                auto nsegs = segs;
                auto len = sementlength(w);
                nsegs.emplace_back(std::move(w));
                get_chunks_it(start + len, end, n - 1, std::move(nsegs));
            }
            segs.emplace_back(start, start + 1);
            get_chunks_it(start + 1, end, n - 1, std::move(segs));
        }
    };

    get_chunks_it(_start, _end, depth, std::vector<StringItP>{});
    return ret;
}