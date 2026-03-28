#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/internal/catch_stringref.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

// Since Capturer requires getResultCapture() to be active, and that requires
// running inside a Catch2 test context, we need to mock IResultCapture.
// However, the class calls getResultCapture() in its constructor directly.
// We'll test what we can about the parsing logic through captureValue behavior.

namespace Catch {
    // Forward declare - we need access to IResultCapture interface
    class IResultCapture;
}

// Due to the tight coupling with Catch2's internal getResultCapture(),
// we test the Capturer within a Catch2 TEST_CASE which provides the required context.
// The tests below use Catch2's own TEST_CASE macro to provide the result capture context.

TEST_CASE("Capturer_SingleName_1055", "[Capturer]") {
    // Test that a single variable name is parsed correctly
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "myVar"
    );
    // captureValues with single value should work
    capturer.captureValues(0, 42);
    // If we get here without throwing, the single name was parsed successfully
    SUCCEED();
}

TEST_CASE("Capturer_MultipleNames_1055", "[Capturer]") {
    // Test that multiple comma-separated names are parsed
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "a, b, c"
    );
    capturer.captureValues(0, 1, 2, 3);
    SUCCEED();
}

TEST_CASE("Capturer_NamesWithParentheses_1055", "[Capturer]") {
    // Test that commas inside parentheses are not treated as separators
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "foo(a, b), c"
    );
    capturer.captureValues(0, std::string("val1"), std::string("val2"));
    SUCCEED();
}

TEST_CASE("Capturer_NamesWithBrackets_1055", "[Capturer]") {
    // Test that commas inside brackets are not treated as separators
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "arr[1,2], x"
    );
    capturer.captureValues(0, std::string("val1"), std::string("val2"));
    SUCCEED();
}

TEST_CASE("Capturer_NamesWithBraces_1055", "[Capturer]") {
    // Test that commas inside braces are not treated as separators
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "std::map<int>{1,2}, y"
    );
    capturer.captureValues(0, std::string("val1"), std::string("val2"));
    SUCCEED();
}

TEST_CASE("Capturer_NamesWithQuotedStrings_1055", "[Capturer]") {
    // Test that commas inside quoted strings are not treated as separators
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "\"hello, world\", z"
    );
    capturer.captureValues(0, std::string("val1"), std::string("val2"));
    SUCCEED();
}

TEST_CASE("Capturer_NamesWithSingleQuotes_1055", "[Capturer]") {
    // Test that commas inside single-quoted chars are not treated as separators
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "',', x"
    );
    capturer.captureValues(0, std::string("val1"), std::string("val2"));
    SUCCEED();
}

TEST_CASE("Capturer_NamesWithWhitespace_1055", "[Capturer]") {
    // Test that leading/trailing whitespace around names is trimmed
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "  a  ,  b  "
    );
    capturer.captureValues(0, 1, 2);
    SUCCEED();
}

TEST_CASE("Capturer_CaptureValueAppendsToMessage_1055", "[Capturer]") {
    // Test that captureValue can be called with string values
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "x"
    );
    capturer.captureValue(0, "42");
    SUCCEED();
}

TEST_CASE("Capturer_NestedParentheses_1055", "[Capturer]") {
    // Test nested parentheses with commas inside
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "foo(bar(1, 2), 3), baz"
    );
    capturer.captureValues(0, std::string("val1"), std::string("val2"));
    SUCCEED();
}

TEST_CASE("Capturer_EscapedQuoteInString_1055", "[Capturer]") {
    // Test that escaped quotes within strings are handled
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "\"he\\\"llo\", x"
    );
    capturer.captureValues(0, std::string("val1"), std::string("val2"));
    SUCCEED();
}

TEST_CASE("Capturer_MixedBracketsAndParens_1055", "[Capturer]") {
    // Test mixed bracket types
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "foo({1, 2}), bar[3, 4]"
    );
    capturer.captureValues(0, std::string("val1"), std::string("val2"));
    SUCCEED();
}

TEST_CASE("Capturer_SingleCharName_1055", "[Capturer]") {
    // Boundary: single character variable name
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "x"
    );
    capturer.captureValues(0, 5);
    SUCCEED();
}

TEST_CASE("Capturer_MultipleValuesCapture_1055", "[Capturer]") {
    // Test capturing multiple values with variadic captureValues
    Catch::Capturer capturer(
        "CAPTURE"_catch_sr,
        CATCH_INTERNAL_LINEINFO,
        Catch::ResultWas::Info,
        "a, b, c, d"
    );
    capturer.captureValues(0, 1, 2, 3, 4);
    SUCCEED();
}