/*=============================================================================
  Copyright (C) 2021 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <fstream>
#include <iostream>
#include <utf8_to_windows31j_cvt_checker.hpp>
#include <linter.hpp>
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
