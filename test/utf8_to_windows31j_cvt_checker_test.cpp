/*=============================================================================
  Copyright (C) 2021 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef IUTEST_USE_MAIN
#define IUTEST_USE_MAIN
#endif
#include <iutest.hpp>
#include <utf8_to_windows31j_cvt_checker.hpp>
IUTEST(Cvt, success) {
    const char* ascii = "arikitari na sekai";
    iconv_utf8_windows31j_cvt cvt;
    IUTEST_ASSERT_EQ(ascii, cvt(ascii));
    IUTEST_ASSERT_NO_THROW(cvt(reinterpret_cast<const char*>(u8"インストールされていません")));
}
IUTEST(Cvt, fail) {
    iconv_utf8_windows31j_cvt cvt;
    IUTEST_ASSERT_THROW(
        cvt(reinterpret_cast<const char*>(u8"アプリケーション")), std::runtime_error);
    IUTEST_ASSERT_THROW(cvt(reinterpret_cast<const char*>(u8"が")), std::runtime_error);
}
