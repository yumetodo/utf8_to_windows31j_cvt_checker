/*=============================================================================
  Copyright (C) 2021 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef UTF8_TO_WINDOWS31J_CVT_CHECKER_LINTER_HPP_
#define UTF8_TO_WINDOWS31J_CVT_CHECKER_LINTER_HPP_
#include "utf8_to_windows31j_cvt_checker.hpp"
enum class ascii_color : int {
    reset = 0,
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    magenta = 35,
    cyan = 36,
    white = 37,
    bright_black = 90,
    bright_red = 91,
    bright_green = 92,
    bright_yellow = 93,
    bright_blue = 94,
    bright_magenta = 95,
    bright_cyan = 96,
    bright_white = 97,
};
inline std::ostream& operator<<(std::ostream& os, ascii_color c) {
    return os << "\033[" << static_cast<int>(c) << 'm';
}
inline bool lint(std::istream& is, std::ostream& os, const char* path = nullptr) {
    iconv_utf8_windows31j_cvt cvt;
    std::size_t line{};
    bool has_error = false;
    for (std::string buf; std::getline(is, buf); ++line) {
        try {
            cvt(buf);
        } catch (const std::runtime_error& er) {
            if (!std::exchange(has_error, true)) {
                os << ascii_color::bright_red << "invalid input(s) has detected. see blow:\n";
                if (path) {
                    os << ascii_color::reset << "In file " << path << '\n';
                }
            }
            os << ascii_color::bright_cyan << "line " << line << ascii_color::reset << '\n'
               << buf << std::endl;
        }
    }
    return true;
}
inline bool lint(std::istream& is, const char* path = nullptr) { return lint(is, std::cerr, path); }
#endif  // UTF8_TO_WINDOWS31J_CVT_CHECKER_LINTER_HPP_
