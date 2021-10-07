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
    IUTEST_ASSERT_EQ(0, lint(iss, oss));
}
IUTEST(Linter, fail) {
    std::stringstream iss;
    iss << reinterpret_cast<const char*>(u8"アプリケーション");
    std::ostringstream oss;
    IUTEST_ASSERT_EQ(1, lint(iss, oss));
}
