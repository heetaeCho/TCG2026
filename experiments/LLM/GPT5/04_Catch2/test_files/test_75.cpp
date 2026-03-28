// File: tests/convert_unstreamable_75_test.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>
#include <exception>
#include <utility>

#include "catch2/catch_tostring.hpp"

// Detection trait: is convertUnstreamable(T const&) well-formed?
namespace {
template <typename T, typename = void>
struct has_convert_unstreamable : std::false_type {};

template <typename T>
struct has_convert_unstreamable<
    T,
    std::void_t<decltype(Catch::Detail::convertUnstreamable(std::declval<T const&>()))>
> : std::true_type {};
} // namespace

// ------------------------- Runtime behavior -------------------------

TEST(ConvertUnstreamableTest_75, ReturnsFallbackString_ForPlainStruct_75) {
    struct Plain {};
    Plain p{};

    // Runtime call should succeed for non-enum, non-exception types
    std::string result = Catch::Detail::convertUnstreamable(p);

    // The function's observable behavior is to return the library's fallback string.
    // We compare against the exported constant it uses.
    EXPECT_EQ(result, std::string(Catch::Detail::unprintableString));
}

TEST(ConvertUnstreamableTest_75, AcceptsConstArgument_AndReturnsFallback_75) {
    struct Plain {};
    const Plain cp{};

    std::string result = Catch::Detail::convertUnstreamable(cp);
    EXPECT_EQ(result, std::string(Catch::Detail::unprintableString));
}

// ------------------------- Compile-time constraints (SFINAE) -------------------------

TEST(ConvertUnstreamableTest_75, EnabledForNonEnumNonExceptionTypes_75) {
    struct Plain {};
    static_assert(has_convert_unstreamable<Plain>::value,
                  "convertUnstreamable should be enabled for non-enum, non-exception types");

    // Also verify the return type is std::string when enabled.
    using Ret = decltype(Catch::Detail::convertUnstreamable(std::declval<Plain const&>()));
    static_assert(std::is_same<Ret, std::string>::value,
                  "convertUnstreamable should return std::string");
}

TEST(ConvertUnstreamableTest_75, NotEnabledForEnums_75) {
    enum class E { A, B };
    static_assert(!has_convert_unstreamable<E>::value,
                  "convertUnstreamable should be disabled for enum types");
}

TEST(ConvertUnstreamableTest_75, NotEnabledForExceptionDerivedTypes_75) {
    struct MyEx : std::exception {};
    static_assert(!has_convert_unstreamable<MyEx>::value,
                  "convertUnstreamable should be disabled for std::exception-derived types");
}

// A boundary-style compile-time check: even if a type is non-default-constructible,
// detection should still report availability (constructibility is irrelevant to the interface).
TEST(ConvertUnstreamableTest_75, EnabledForNonDefaultConstructibleButEligibleTypes_75) {
    struct NoDefault {
        NoDefault() = delete;
        // (still neither enum nor exception-derived)
    };
    static_assert(has_convert_unstreamable<NoDefault>::value,
                  "convertUnstreamable availability should not depend on default constructibility");
}
