export module atom_core:io;

import std;
import :core;
import :filesystem;
import :strings;

export namespace atom::io
{
    filesystem::file stdin{ std::stdin, filesystem::file::open_flags::read };
    filesystem::file stdout{ std::stdout, filesystem::file::open_flags::write };
    filesystem::file stderr{ std::stderr, filesystem::file::open_flags::write };

    template <typename... arg_types>
    inline auto print(format_string<arg_types...> fmt, arg_types&&... args)
    {
        stdout.write_fmt(fmt, forward<arg_types>(args)...);
    }

    template <typename... arg_types>
    inline auto println(format_string<arg_types...> fmt, arg_types&&... args)
    {
        stdout.write_line_fmt(fmt, forward<arg_types>(args)...);
    }
}
