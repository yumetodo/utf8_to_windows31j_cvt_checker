#ifndef IUTEST_USE_MAIN
#define IUTEST_USE_MAIN
#endif
#include <utf8_to_windows31j_cvt_checker.hpp>
#include <iutest.hpp>
IUTEST(Basic, sucess)
{
    const char* ascii = "arikitari na sekai";
    iconv_utf8_windows31j_cvt cvt;
    IUTEST_ASSERT_EQ(ascii, cvt(ascii));
    IUTEST_ASSERT_NO_THROW(cvt(reinterpret_cast<const char*>(u8"インストールされていません")));
}
IUTEST(Basic, fail)
{
    iconv_utf8_windows31j_cvt cvt;
    IUTEST_ASSERT_THROW(cvt(reinterpret_cast<const char*>(u8"アプリケーション")), std::runtime_error);
    IUTEST_ASSERT_THROW(cvt(reinterpret_cast<const char*>(u8"が")), std::runtime_error);
}
