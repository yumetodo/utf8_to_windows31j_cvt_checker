/*=============================================================================
  Copyright (C) 2021 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <iutest.hpp>
#include <linter.hpp>
#include <sstream>
IUTEST(Linter, success) {
    std::stringstream iss;
    iss << reinterpret_cast<const char*>(u8"インストールされていません");
    std::ostringstream oss;
    IUTEST_ASSERT_EQ(true, lint(iss, oss));
}
IUTEST(Linter, fail) {
    std::stringstream iss;
    iss << reinterpret_cast<const char*>(u8"アプリケーション");
    std::ostringstream oss;
    IUTEST_ASSERT_EQ(false, lint(iss, oss));
}
IUTEST(Linter, OneBasedIndex) {
    constexpr auto input = u8R"(1人,👨
2人,👨‍👩‍
3人,👨‍👩‍👦
4人,👨‍👩‍👧‍👦)";
    std::stringstream iss;
    iss << reinterpret_cast<const char*>(input);
    std::stringstream oss;
    lint(iss, oss);
    std::string buf;
    IUTEST_ASSERT(std::getline(oss, buf)); // skip
    IUTEST_ASSERT(std::getline(oss, buf));
    IUTEST_ASSERT(std::string::npos != buf.find("line 1"));
    IUTEST_ASSERT(std::getline(oss, buf)); // skip
    IUTEST_ASSERT(std::getline(oss, buf));
    IUTEST_ASSERT(std::string::npos != buf.find("line 2"));
    IUTEST_ASSERT(std::getline(oss, buf)); // skip
    IUTEST_ASSERT(std::getline(oss, buf));
    IUTEST_ASSERT(std::string::npos != buf.find("line 3"));
    IUTEST_ASSERT(std::getline(oss, buf)); // skip
    IUTEST_ASSERT(std::getline(oss, buf));
    IUTEST_ASSERT(std::string::npos != buf.find("line 4"));
}
