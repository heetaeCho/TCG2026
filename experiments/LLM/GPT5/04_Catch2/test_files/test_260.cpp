// File: stringmaker_string_convert_tests_260.cpp

#include <gtest/gtest.h>
#include <string>
#include "catch2/catch_tostring.hpp"

// Convenience alias for the function under test (kept fully-qualified in calls).
// We avoid relying on any internal details or behaviors.
using CatchConvertStringFn = std::string (*)(const std::string&);

// Test fixture (no shared state needed, keeps naming consistent).
class StringMakerStringConvertTest_260 : public ::testing::Test {};

// [Normal operation] Empty string should be convertible without throwing
// and the result should be deterministic for the same input.
TEST_F(StringMakerStringConvertTest_260, EmptyString_NoThrowAndDeterministic_260) {
    const std::string input;
    std::string out1;
    std::string out2;

    EXPECT_NO_THROW(out1 = Catch::StringMaker<std::string>::convert(input));
    EXPECT_NO_THROW(out2 = Catch::StringMaker<std::string>::convert(input));

    // Determinism: same input -> same output
    EXPECT_EQ(out1, out2);

    // Return type is std::string (compile-time check via decltype)
    static_assert(std::is_same_v<decltype(out1), std::string>, "Return type must be std::string");
}

// [Normal operation] Simple ASCII input converts without throwing and is deterministic.
TEST_F(StringMakerStringConvertTest_260, SimpleASCII_NoThrowAndDeterministic_260) {
    const std::string input = "hello world";
    auto out1 = Catch::StringMaker<std::string>::convert(input);
    auto out2 = Catch::StringMaker<std::string>::convert(input);
    EXPECT_EQ(out1, out2);
}

// [Boundary] String with embedded nulls should be handled without throwing and deterministically.
TEST_F(StringMakerStringConvertTest_260, EmbeddedNulls_HandledDeterministically_260) {
    std::string input = std::string("abc\0def", 7); // includes a '\0' in the middle
    std::string out1, out2;
    EXPECT_NO_THROW(out1 = Catch::StringMaker<std::string>::convert(input));
    EXPECT_NO_THROW(out2 = Catch::StringMaker<std::string>::convert(input));
    EXPECT_EQ(out1, out2);
}

// [Boundary] Very long input should not throw and should be deterministic.
TEST_F(StringMakerStringConvertTest_260, LargeInput_NoThrowAndDeterministic_260) {
    std::string input(100000, 'x'); // 100k chars
    std::string out1, out2;
    EXPECT_NO_THROW(out1 = Catch::StringMaker<std::string>::convert(input));
    EXPECT_NO_THROW(out2 = Catch::StringMaker<std::string>::convert(input));
    EXPECT_EQ(out1, out2);
}

// [Normal + Internationalization] UTF-8 content converts without throwing and deterministically.
TEST_F(StringMakerStringConvertTest_260, UTF8Content_NoThrowAndDeterministic_260) {
    const std::string input = u8"한글🔥🙂";
    auto out1 = Catch::StringMaker<std::string>::convert(input);
    auto out2 = Catch::StringMaker<std::string>::convert(input);
    EXPECT_EQ(out1, out2);
}

// [API usage] Converting from an rvalue temporary should be supported and deterministic.
TEST_F(StringMakerStringConvertTest_260, RvalueTemporary_SupportedAndDeterministic_260) {
    auto out1 = Catch::StringMaker<std::string>::convert(std::string("temp-value"));
    auto out2 = Catch::StringMaker<std::string>::convert(std::string("temp-value"));
    EXPECT_EQ(out1, out2);
}

// [Robustness] Special characters (including control chars) should not cause exceptions;
// output should remain deterministic for the same input.
TEST_F(StringMakerStringConvertTest_260, SpecialChars_NoThrowAndDeterministic_260) {
    const std::string input = std::string("line1\nline2\tend\b\r\f\v\\\"\'");
    std::string out1, out2;
    EXPECT_NO_THROW(out1 = Catch::StringMaker<std::string>::convert(input));
    EXPECT_NO_THROW(out2 = Catch::StringMaker<std::string>::convert(input));
    EXPECT_EQ(out1, out2);
}
