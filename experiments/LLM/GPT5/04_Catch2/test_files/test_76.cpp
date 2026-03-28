// File: convert_unstreamable_tests_76.cpp

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

// Header under test (path from the prompt)
#include "catch2/catch_tostring.hpp"

// Helper: detection idiom to check whether convertUnstreamable is well-formed for T
template <typename T, typename = void>
struct has_convert_unstreamable_76 : std::false_type {};

template <typename T>
struct has_convert_unstreamable_76<
    T,
    std::void_t<decltype(Catch::Detail::convertUnstreamable(std::declval<const T&>()))>
> : std::true_type {};

template <typename T>
constexpr bool has_convert_unstreamable_v_76 = has_convert_unstreamable_76<T>::value;

// A simple custom exception type to exercise polymorphic what()
struct CustomEx76 : public std::exception {
    const char* what() const noexcept override {
        return "custom-what-76";
    }
};

// An enum type to verify SFINAE exclusion
enum class DummyEnum76 { A, B };

TEST(ConvertUnstreamableTest_76, ReturnsWhatForStdRuntimeError_76) {
    const std::string msg = "hello world 76";
    const std::runtime_error ex(msg);
    const std::string out = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(out, msg);
}

TEST(ConvertUnstreamableTest_76, ReturnsWhatForCustomException_76) {
    const CustomEx76 ex;
    const std::string out = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(out, std::string("custom-what-76"));
}

TEST(ConvertUnstreamableTest_76, HandlesEmptyMessage_76) {
    const std::runtime_error ex("");
    const std::string out = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(out, "");
}

TEST(ConvertUnstreamableTest_76, HandlesLongMessage_76) {
    // Create a reasonably long message to ensure no truncation occurs
    std::string long_msg(4096, 'x');  // 4KB of 'x'
    const std::runtime_error ex(long_msg);
    const std::string out = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(out, long_msg);
}

TEST(ConvertUnstreamableTest_76, SFINAE_EnabledForExceptionTypes_76) {
    // Should be well-formed for types derived from std::exception and not enums
    EXPECT_TRUE((has_convert_unstreamable_v_76<std::runtime_error>));
    EXPECT_TRUE((has_convert_unstreamable_v_76<CustomEx76>));
}

TEST(ConvertUnstreamableTest_76, SFINAE_DisabledForEnumsAndNonException_76) {
    // Should NOT be well-formed for enums or non-exception, non-enum types
    EXPECT_FALSE((has_convert_unstreamable_v_76<DummyEnum76>));
    EXPECT_FALSE((has_convert_unstreamable_v_76<int>));
    struct NotAnException76 {};
    EXPECT_FALSE((has_convert_unstreamable_v_76<NotAnException76>));
}
