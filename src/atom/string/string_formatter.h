#pragma once
#include "string_arg_formatters.h"

namespace atom
{
    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    class _fmt_string_view_cnvter
    {
    public:
        constexpr auto from_fmt(_fmt_string_view str) -> string_view
        {
            const uchar* begin = _from_std_char_ptr(str.data());
            usize count = str.size();
            return string_view{ make_range(begin, count) };
        }

        constexpr auto to_fmt(string_view str) -> _fmt_string_view
        {
            const char* begin = _to_std_char_ptr(str.data().unwrap());
            const _usize count = str.count().unwrap();
            return _fmt_string_view{ begin, count };
        }
    };

    /// --------------------------------------------------------------------------------------------
    /// wrapper over {string_view} to represent format string. this_type is done to avoid compile
    /// time checks.
    /// --------------------------------------------------------------------------------------------
    class run_fmt_string
    {
    public:
        string_view str;
    };

    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    template <rstring_fmt_arg_fmtable... args_type>
    using fmt_string = _fmt_fmt_string<args_type...>;

    //     class fmt_string
    //     {
    //     public:
    //         template <typename type>
    //         consteval fmt_string(const type& strv) { }
    //             _fmt{ _fmt_string_view_cnvter().to_fmt(strv) } { }
    //
    //         fmt_string(run_fmt_string str) { }
    //             _fmt{ _fmt_run_fmt_string{ _fmt_string_view_cnvter().to_fmt(str.str) } } { }
    //
    //     public:
    //         _fmt_fmt_string<args_type...> _fmt;
    //     };

    /// --------------------------------------------------------------------------------------------
    ///
    /// --------------------------------------------------------------------------------------------
    class string_fmter
    {
    public:
        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <typename tout, rstring_fmt_arg_fmtable... args_type>
        auto fmt_to(tout out, fmt_string<args_type...> fmt, args_type&&... args)
            requires routput<tout, uchar>
        {
            class _out_iter_wrap
            {
            public:
                auto operator++(int) -> _out_iter_wrap&
                {
                    return *this;
                }

                auto operator*() -> _out_iter_wrap&
                {
                    return *this;
                }

                auto operator=(char ch) -> _out_iter_wrap&
                {
                    *out += uchar(ch);
                    return *this;
                }

            public:
                tout* out;
            };

            fmt::detail::iterator_buffer<_out_iter_wrap, char> buf{ _out_iter_wrap{ &out } };

            try
            {
                fmt::detail::vformat_to<char>(buf, fmt,
                    fmt::make_format_args<fmt::buffer_context<char>>(args...),
                    fmt::detail::locale_ref{});
            }
            catch (const _fmt_fmt_ex& err)
            {
                throw string_fmt_err(err);
            }
        }

        /// ----------------------------------------------------------------------------------------
        ///
        /// ----------------------------------------------------------------------------------------
        template <rstring_fmt_arg_fmtable... args_type>
        auto fmt(fmt_string<args_type...> fmt, args_type&&... args) -> string
        {
            string out;
            fmt_to(out, fmt, forward<args_type>(args)...);

            return out;
        }
    };
}
