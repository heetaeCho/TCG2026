// File: convertUnstreamable_enum_tests_77.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <string>

// Header under test
#include "Catch2/src/catch2/catch_tostring.hpp"

// We place our test enum in its own namespace so that ADL can find
// our test-only overload of convertUnknownEnumToString for interaction verification.
namespace TestEnums77 {

enum class Color77 : unsigned long long {
    Red = 1ULL,
    Blue = 0xDEADBEEFCAFEBABEULL >> 4 // some large-ish value, just to be "boundary-ish"
};

// Simple test helper to verify that Catch::Detail::convertUnstreamable
// forwards to an unqualified call to convertUnknownEnumToString via ADL.
//
// We record the last value we were called with and how many times it was called.
static int g_called_count_77 = 0;
static Color77 g_last_value_77 = static_cast<Color77>(0);

// This free function intentionally matches the unqualified name used inside
// convertUnstreamable. Because our argument type is Color77 (an associated type),
// ADL will make this candidate visible when convertUnstreamable(Color77) is called.
inline std::string convertUnknownEnumToString(Color77 v) {
    ++g_called_count_77;
    g_last_value_77 = v;
    // Return a sentinel string so tests can assert on observable output.
    return std::string("ADL_CONVERTED_77");
}

} // namespace TestEnums77

// A tiny trait to check if Catch::Detail::convertUnstreamable(T) is callable.
// This verifies the SFINAE constraint (enabled only for enums) purely at compile-time.
namespace {
template <typename T, typename = void>
struct is_convertUnstreamable_callable_77 : std::false_type {};

template <typename T>
struct is_convertUnstreamable_callable_77<
    T,
    std::void_t<decltype(Catch::Detail::convertUnstreamable(std::declval<const T&>()))>
> : std::true_type {};
} // namespace

// ---------- Tests ----------

TEST(ConvertUnstreamableEnum_77, DelegatesViaADLAndReturnsString_77) {
    using namespace TestEnums77;

    // Reset test hooks
    g_called_count_77 = 0;
    g_last_value_77 = static_cast<Color77>(0);

    // Call the function under test (black-box).
    const auto out = Catch::Detail::convertUnstreamable(Color77::Blue);

    // Observable effects:
    // 1) Our ADL-targeted function should have been called exactly once.
    EXPECT_EQ(g_called_count_77, 1);

    // 2) The value should be forwarded intact to the collaborator.
    EXPECT_EQ(g_last_value_77, Color77::Blue);

    // 3) The function returns a std::string. We assert on our sentinel value.
    EXPECT_EQ(out, "ADL_CONVERTED_77");
}

TEST(ConvertUnstreamableEnum_77, EnabledOnlyForEnumsAndReturnsStdString_77) {
    using TestTypeEnum = TestEnums77::Color77;

    // SFINAE: should be callable for enums…
    static_assert(is_convertUnstreamable_callable_77<TestTypeEnum>::value,
                  "convertUnstreamable must be enabled for enum types");

    // …and not callable for non-enum types (e.g., int, double).
    static_assert(!is_convertUnstreamable_callable_77<int>::value,
                  "convertUnstreamable must NOT be enabled for non-enum types");
    static_assert(!is_convertUnstreamable_callable_77<double>::value,
                  "convertUnstreamable must NOT be enabled for non-enum types");

    // Return type is std::string for enums.
    static_assert(std::is_same<
                      decltype(Catch::Detail::convertUnstreamable(std::declval<const TestTypeEnum&>())),
                      std::string
                  >::value,
                  "convertUnstreamable should return std::string for enum types");
}
