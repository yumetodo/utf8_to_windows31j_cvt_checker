/*=============================================================================
  Copyright (C) 2021 yumetodo <yume-wikijp@live.jp>
  Distributed under the Boost Software License, Version 1.0.
  (See https://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef UTF8_TO_WINDOWS31J_CVT_CHECKER_UTF8_TO_WINDOWS31J_CVT_CHECKER_HPP_
#define UTF8_TO_WINDOWS31J_CVT_CHECKER_UTF8_TO_WINDOWS31J_CVT_CHECKER_HPP_

#include <iconv.h>

#include <cerrno>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
class iconv_utf8_windows31j_cvt {
public:
    iconv_utf8_windows31j_cvt() {
        errno = 0;
        this->cd = iconv_open("WINDOWS-31J", "UTF-8");
        if (this->cd == (iconv_t)-1) {
            if (errno == EINVAL) {
                throw std::logic_error("unsupported convert from UTF-8 to WINDOWS-31J");
            }
            throw std::runtime_error("iconv_open failed");
        }
    }
    iconv_utf8_windows31j_cvt(const iconv_utf8_windows31j_cvt&) = delete;
    iconv_utf8_windows31j_cvt(iconv_utf8_windows31j_cvt&&) = default;
    iconv_utf8_windows31j_cvt& operator=(const iconv_utf8_windows31j_cvt&) = delete;
    iconv_utf8_windows31j_cvt& operator=(iconv_utf8_windows31j_cvt&&) = default;
    ~iconv_utf8_windows31j_cvt() noexcept { iconv_close(cd); }
    std::string operator()(std::string input) const {
        char* inbuf = input.data();
        std::size_t inbytesleft = input.size();
        std::string dest;
        dest.resize(input.size());
        for (std::size_t next_outbuf_pos = 0;;) {
            char* outbuf = dest.data() + next_outbuf_pos;
            std::size_t outbytesleft = dest.size() - next_outbuf_pos;
            errno = 0;
            std::size_t ret = iconv(this->cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
            if (ret == (size_t)-1) {
                if (errno == E2BIG) {
                    next_outbuf_pos = outbuf - dest.data();
                    dest.resize(dest.size() * 2);
                } else {
                    check_errno();
                }
            } else {
                dest.resize(outbuf - dest.data());
                return dest;
            }
        }
    }

private:
    static void check_errno() {
        switch (errno) {
            case EILSEQ:
                throw std::runtime_error(
                    "An invalid multibyte sequence is encountered in the input");
            case EINVAL:
                throw std::runtime_error(
                    "An incomplete multibyte sequence is encountered in the input, and the input "
                    "byte sequence terminates after it");
            default:
                throw std::runtime_error("unknown error");
        }
    }
    iconv_t cd;
};
#endif  // UTF8_TO_WINDOWS31J_CVT_CHECKER_UTF8_TO_WINDOWS31J_CVT_CHECKER_HPP_
