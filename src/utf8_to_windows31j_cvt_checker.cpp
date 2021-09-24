#include <iostream>
#include <fstream>
#include <utf8_to_windows31j_cvt_checker.hpp>
void lint(std::istream& is)
{
    iconv_utf8_windows31j_cvt cvt;
    std::size_t line{};
    bool has_error = false;
    for(std::string buf; std::getline(is, buf); ++line){
        try {
            cvt(buf);
        }
        catch(const std::runtime_error& er) {
            if (!std::exchange(has_error, true)) {
                std::cerr << ascii_color::bright_red << "invalid input(s) has detected. see blow:\n";
            }
            std::cerr << ascii_color::bright_cyan << "line " << line << ascii_color::reset << '\n' << buf << std::endl;
        }
    }
}
int main(int argc, char** argv)
{
    if (argc == 2) {
        std::ifstream ifs(argv[1]);
        lint(ifs);
    }
    else {
        lint(std::cin);
    }
}
