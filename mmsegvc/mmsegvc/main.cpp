#include "segment.h"
#include <ctime>
#include <clocale>

#ifdef __GNUC__

#define CSET_GBK	"GBK"
#define CSET_UTF8	"UTF-8"
#define LC_NAME_zh_CN	"zh_CN"

#elif defined(_MSC_VER)

#define CSET_GBK	"936"
#define CSET_UTF8	"65001"
#define LC_NAME_zh_CN	"Chinese_People's Republic of China"
// ifdef _MSC_VER
#endif

#define LC_NAME_zh_CN_GBK		LC_NAME_zh_CN "." CSET_GBK
#define LC_NAME_zh_CN_UTF8		LC_NAME_zh_CN "." CSET_UTF8
#define LC_NAME_zh_CN_DEFAULT	LC_NAME_zh_CN_GBK

int main(int argc, const char *argv[]) {
    //printf("Locale is: %s\n", std::setlocale(LC_ALL, "zh_CN.UTF-8"));
    printf("Locale is: %s\n", std::setlocale(LC_ALL, LC_NAME_zh_CN_GBK));
    MMSeg mmseg;
    mmseg.load("words.dic", "chars.dic");
    if (argc >= 2) {
        std::ifstream ifs(argv[1]);
        if (!ifs.good()) {
            std::cerr << "Failed to open " << argv[1] << std::endl;
            return -1;
        }
        std::stringstream ss;
        ss << ifs.rdbuf();
        auto s = from_utf8(ss.str());
        time_t now = time(0);
        auto w = mmseg.segment(s);
        std::cout << "Done in " << time(0) - now << " seconds, " << w.size() << " words from " << s.size() << " chars" << std::endl;
        return 0;
    }
#ifdef test
    setlocale(LC_ALL, "chs");
    std::string s = "ÄãºÃabc";
    std::wstring ws = L"ÄãºÃabc";
    printf("%s\n", s.c_str());
    wprintf(L"%s\n", ws.c_str());
#endif // test
    std::wstring ws = L"ÄãºÃabc";



    std::string line;
    std::ifstream input("input.txt");
    std::ofstream output("result.txt");
    //std::ifstream input("words1.dic");
    if (!input.is_open()) return -1;
    while (input.good()) {
        if (!std::getline(input, line)) break;

        //if (!std::getline(std::cin, line)) break;
        std::u16string s = from_utf8(MMSeg::trim(line));
        for (auto& w : mmseg.segment(s))
        {

            std::wcout << ws << "  "; std::cout << std::endl;
            output << to_utf8(w) << "  "; output << std::endl;
        }


    }
    input.close();
    output.close();
    return 0;
}
