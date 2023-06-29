/*

Copyright (c) 2005, 2008-2009, 2013, 2016-2021, Arvid Norberg
Copyright (c) 2020, Paul-Louis Ageneau
Copyright (c) 2021, Alden Torres
All rights reserved.

You may use, distribute and modify this code under the terms of the BSD license,
see LICENSE file.
*/

#ifndef TORRENT_UTF8_HPP_INCLUDED
#define TORRENT_UTF8_HPP_INCLUDED

#include "libtorrent/aux_/export.hpp"

#include <cstdint>
#include <string>
#include "libtorrent/string_view.hpp"
#include "libtorrent/span.hpp"
#include "libtorrent/aux_/export.hpp"
#include <cwchar>
#include <string_view>
#include "libtorrent/error_code.hpp"

namespace libtorrent::aux {

    namespace utf8_errors {
        // internal
        enum error_code_enum
        {
            // conversion successful
            conversion_ok,

            // partial character in source, but hit end
            source_exhausted,

            // insufficient room in target for conversion
            target_exhausted,

            // source sequence is illegal/malformed
            source_illegal
        };

        // hidden
        TORRENT_EXPORT error_code make_error_code(error_code_enum e);
    } // namespace utf8_errors

    TORRENT_EXPORT boost::system::error_category const& utf8_category();

    // ``utf8_wchar`` converts a UTF-8 string (``utf8``) to a wide character
    // string (``wide``). ``wchar_utf8`` converts a wide character string
    // (``wide``) to a UTF-8 string (``utf8``). The return value is one of
    // the enumeration values from utf8_conv_result_t.
    TORRENT_EXTRA_EXPORT std::wstring utf8_wchar(string_view utf8, error_code& ec);
    TORRENT_EXTRA_EXPORT std::wstring utf8_wchar(string_view utf8);
    TORRENT_EXTRA_EXPORT std::string wchar_utf8(wstring_view wide, error_code& ec);
    TORRENT_EXTRA_EXPORT std::string wchar_utf8(wstring_view wide);

    // ``utf8_char32`` converts a UTF-8 string to a UTF-32 string
    // ``char32_utf8`` converts a UTF-32 string to a UTF-8 string
    // The return value is one of the enumeration values from utf8_conv_result_t.
    TORRENT_EXTRA_EXPORT std::u32string utf8_utf32(std::string_view utf8, error_code& ec);
    TORRENT_EXTRA_EXPORT std::u32string utf8_utf32(std::string_view utf8);
    TORRENT_EXTRA_EXPORT std::string utf32_utf8(std::u32string_view utf32, error_code& ec);
    TORRENT_EXTRA_EXPORT std::string utf32_utf8(std::u32string_view utf32);

    // ``latin1_utf8`` converts a ISO-8859-1 (aka latin1) span to a UTF-8 string
    // ``utf8_latin1`` converts a UTF-8 string to a ISO-8859-1 (aka latin1) string
    TORRENT_EXTRA_EXPORT std::string latin1_utf8(span<char const> s);
    TORRENT_EXTRA_EXPORT std::string utf8_latin1(std::string_view sv); // throw invalid_argument if unrepresentable

    // TODO: 3 take a string_view here
    TORRENT_EXTRA_EXPORT std::pair<std::int32_t, int>
    parse_utf8_codepoint(string_view str);

    TORRENT_EXTRA_EXPORT void append_utf8_codepoint(std::string&, std::int32_t);

} // namespace libtorrent

#endif