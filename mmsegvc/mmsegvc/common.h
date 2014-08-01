#ifndef _COMMON_H_
#define _COMMON_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>
#if defined(_LIBCPP_BEGIN_NAMESPACE_STD)
#include <codecvt>
#else // gcc has no <codecvt>
#include "utf8cpp/utf8.h"
#endif
using Char = char16_t;
using String = std::u16string;
using StringIt = String::const_iterator;
using StringItP = std::pair < StringIt, StringIt >;
static size_t sementlength(const StringItP& w) { return std::distance(w.first, w.second); }
#if defined(_LIBCPP_BEGIN_NAMESPACE_STD)
inline static std::string to_utf8(const std::u16string& in) {
    std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> cv;
    return cv.to_bytes(in.data());
}

inline static std::u16string from_utf8(const std::string& in) {
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> cv;
    return cv.from_bytes(in.data());
}
#else // gcc has no <codecvt>
inline static std::string to_utf8(const std::u16string& in) {
    std::string out;
    utf8::utf16to8(in.begin(), in.end(), std::back_inserter(out));
    return out;
}

inline static std::u16string from_utf8(const std::string& in) {
    std::u16string out;
    utf8::utf8to16(in.begin(), in.end(), std::back_inserter(out));
    return out;
}
#endif
#endif