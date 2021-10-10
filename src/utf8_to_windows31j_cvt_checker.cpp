/*=============================================================================
  Copyright (C) 2021 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <fstream>
#include <iostream>
#include <linter.hpp>
#include <string_view>
#include <utf8_to_windows31j_cvt_checker.hpp>

constexpr auto help_text = R"(utf8_to_windows31j_cvt_checker

Usage:
    utf8_to_windows31j_cvt_checker <some files>
    cat <some file> | utf8_to_windows31j_cvt_checker
)";

int main(int argc, char** argv) {
    using namespace std::string_view_literals;
    if (argc < 1) {
        return 2;
    }
    if (argc == 1) {
        return lint(std::cin) ? 0 : 1;
    }
    if (argc == 2) {
        const std::string_view maybe_help_request = argv[1];
        if (maybe_help_request == "--help"sv || maybe_help_request == "-h"sv) {
            std::cerr << help_text << std::flush;
            return 0;
        }
    }

    int ret = 0;
    bool lint_has_performed = false;
    for (int i = 1; i < argc; i++) {
        std::ifstream ifs(argv[i]);
        if (ifs) lint_has_performed = true;
        if (!lint(ifs, argv[i])) ret = 1;
    }
    if (!lint_has_performed) {
        std::cerr << help_text << std::flush;
        return 2;
    }
    return ret;
}
