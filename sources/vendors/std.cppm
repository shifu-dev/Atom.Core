module;

#include <cerrno>
#include <cstdio>
#include <istream>
#include <ostream>
#include <cstdlib>
#include <unistd.h>
#include <array>
#include <iterator>
#include <bitset>
#include <cstddef>
#include <limits>
#include <optional>
#include <tuple>
#include <variant>
#include <iostream>
#include <source_location>
#include <string_view>
#include <type_traits>
#include <random>
#include <algorithm>
#include <unordered_map>
#include <typeinfo>
#include <string_view>
#include <string>
#include <concepts>
#include <cstdint>
#include <cmath>
#include <numeric>
#include <atomic>
#include <memory>
#include <mutex>
#include <initializer_list>
#include <cstring>
#include <functional>
#include <chrono>
#include <unordered_map>
#include <exception>
#include <filesystem>

export module std;

export
{
    using ::fflush;
    using ::FILE;
    using ::fwrite;

    const auto _stderr = stderr;
    const auto _stdin = stdin;
    const auto _stdout = stdout;

#undef stderr
#undef stdin
#undef stdout

    const auto stderr = _stderr;
    const auto stdin = _stdin;
    const auto stdout = _stdout;

    const bool feat_cpp_lib_ranges_contains =
#ifdef __cpp_lib_ranges_contains
        true;
#else
        false;
#endif
}

export namespace std
{
    using std::abs;
    using std::ceil;
    using std::clamp;
    using std::floor;
    using std::int16_t;
    using std::int32_t;
    using std::int64_t;
    using std::int8_t;
    using std::int_fast16_t;
    using std::int_fast32_t;
    using std::int_fast64_t;
    using std::int_fast8_t;
    using std::intmax_t;
    using std::is_floating_point_v;
    using std::is_integral_v;
    using std::is_signed_v;
    using std::numeric_limits;
    using std::ptrdiff_t;
    using std::round;
    using std::size_t;
    using std::uint16_t;
    using std::uint32_t;
    using std::uint64_t;
    using std::uint8_t;
    using std::uint_fast16_t;
    using std::uint_fast32_t;
    using std::uint_fast64_t;
    using std::uint_fast8_t;
    using std::uintmax_t;

    using std::initializer_list;
    using std::nullptr_t;

    using ::stderr;
    using ::stdin;
    using ::stdout;

    using std::cerr;
    using std::cin;
    using std::cout;
    using std::endl;
    using std::ifstream;
    using std::ios;
    using std::iostream;
    using std::istream;
    using std::ofstream;
    using std::ostream;

    using std::add_const_t;
    using std::add_lvalue_reference_t;
    using std::add_pointer_t;
    using std::add_rvalue_reference_t;
    using std::add_volatile_t;
    using std::conditional_t;
    using std::enable_if_t;
    using std::equality_comparable;
    using std::equality_comparable_with;
    using std::false_type;
    using std::is_assignable_v;
    using std::is_base_of_v;
    using std::is_const_v;
    using std::is_constructible_v;
    using std::is_convertible_v;
    using std::is_copy_assignable_v;
    using std::is_copy_constructible_v;
    using std::is_default_constructible_v;
    using std::is_destructible_v;
    using std::is_empty_v;
    using std::is_enum_v;
    using std::is_invocable_r_v;
    using std::is_lvalue_reference_v;
    using std::is_move_assignable_v;
    using std::is_move_constructible_v;
    using std::is_reference_v;
    using std::is_rvalue_reference_v;
    using std::is_same_v;
    using std::is_swappable_v;
    using std::is_trivially_assignable_v;
    using std::is_trivially_constructible_v;
    using std::is_trivially_copy_assignable_v;
    using std::is_trivially_copy_constructible_v;
    using std::is_trivially_default_constructible_v;
    using std::is_trivially_destructible_v;
    using std::is_trivially_move_assignable_v;
    using std::is_trivially_move_constructible_v;
    using std::is_void_v;
    using std::is_volatile_v;
    using std::remove_const_t;
    using std::remove_cv_t;
    using std::remove_cvref_t;
    using std::remove_pointer_t;
    using std::remove_reference_t;
    using std::remove_volatile_t;
    using std::true_type;
    using std::type_identity_t;

    using std::convertible_to;
    using std::copyable;
    using std::default_initializable;
    using std::derived_from;
    using std::destructible;
    using std::is_constant_evaluated;
    using std::movable;
    using std::same_as;

    using std::array;
    using std::bitset;
    using std::get;
    using std::hash;
    using std::optional;
    using std::pair;
    using std::basic_string;
    using std::string;
    using std::basic_string_view;
    using std::string_view;
    using std::tuple;
    using std::tuple_element;
    using std::tuple_size;
    using std::unordered_map;
    using std::variant;
    using std::vector;

    using std::make_shared;
    using std::make_unique;
    using std::shared_ptr;
    using std::unique_ptr;
    using std::weak_ptr;

    using std::bidirectional_iterator;
    using std::bidirectional_iterator_tag;
    using std::contiguous_iterator;
    using std::contiguous_iterator_tag;
    using std::forward_iterator;
    using std::forward_iterator_tag;
    using std::input_iterator;
    using std::input_iterator_tag;
    using std::iterator_traits;
    using std::output_iterator;
    using std::output_iterator_tag;
    using std::random_access_iterator;
    using std::random_access_iterator_tag;

    using std::construct_at;
    using std::copy;
    using std::copy_backward;
    using std::destroy;
    using std::destroy_at;
    using std::equal;
    using std::fill;
    using std::find;
    using std::find_if;
    using std::find_if_not;
    using std::forward;
    using std::max;
    using std::min;
    using std::move;
    using std::move_backward;
    using std::rotate;
    using std::search;
    using std::shift_left;
    using std::shift_right;
    using std::strlen;

    namespace ranges
    {
        using ranges::begin;
        using ranges::bidirectional_range;
        using ranges::cbegin;
        using ranges::cend;
        using ranges::common_range;
        using ranges::contiguous_range;
        using ranges::end;
        using ranges::forward_range;
        using ranges::input_range;
        using ranges::iterator_t;
        using ranges::output_range;
        using ranges::random_access_range;
        using ranges::range;
        using ranges::range_value_t;
        using ranges::sentinel_t;
        using ranges::contains;
    }

    using std::atomic;
    using std::declval;
    using std::free;
    using std::function;
    using std::malloc;
    using std::mutex;
    using std::realloc;
    using std::type_info;

    auto get_errno() -> int
    {
        return errno;
    }

    auto set_errno(int value) -> void
    {
        errno = value;
    }

    using std::exception;
    using std::fclose;
    using std::fflush;
    using std::fopen;
    using std::freopen;
    using std::fseek;
    using std::ftell;
    using std::source_location;
    using std::strerror;
    using std::terminate;

    using namespace std::filesystem;

    namespace chrono
    {
        using chrono::system_clock;
    }

    using std::operator>;
    using std::operator<<;
    using std::operator>>;
    using std::operator>=;
    using std::operator<;
    using std::operator<=;
    using std::operator==;
    using std::operator+;
    using std::operator-;

    using std::chrono::operator>;
    using std::chrono::operator>=;
    using std::chrono::operator<;
    using std::chrono::operator<=;
    using std::chrono::operator==;
    using std::chrono::operator+;
    using std::chrono::operator-;
}
