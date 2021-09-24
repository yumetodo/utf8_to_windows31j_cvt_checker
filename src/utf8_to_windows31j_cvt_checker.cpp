/*=============================================================================
  Copyright (C) 2021 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <fstream>
#include <iostream>
#include <utf8_to_windows31j_cvt_checker.hpp>
bool lint(std::istream& is, const char* path = nullptr) {
    iconv_utf8_windows31j_cvt cvt;
    std::size_t line{};
    bool has_error = false;
    for (std::string buf; std::getline(is, buf); ++line) {
        try {
            cvt(buf);
        } catch (const std::runtime_error& er) {
            if (!std::exchange(has_error, true)) {
                std::cerr << ascii_color::bright_red
                          << "invalid input(s) has detected. see blow:\n";
                if (path) {
                    std::cerr << ascii_color::reset << "In file " << path << '\n';
                }
            }
            std::cerr << ascii_color::bright_cyan << "line " << line << ascii_color::reset << '\n'
                      << buf << std::endl;
        }
    }
    return true;
}
int main(int argc, char** argv) {
    if (argc == 1) {
        return lint(std::cin) ? 0 : 1;
    }

    int ret = 0;
    for (int i = 1; i < argc; i++) {
        std::ifstream ifs(argv[i]);
        if (lint(ifs, argv[i])) ret = 1;
    }
    return ret;
}
