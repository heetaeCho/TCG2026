// File: catch_convert_charptr_tests_81.cpp

#include <gtest/gtest.h>
#include <string>

// Include the header under test (path based on the prompt)
#include "catch2/catch_tostring.hpp"

// We purposefully avoid relying on or re-implementing internals.
// Tests only check observable outputs from the public interface.

namespace {

TEST(CatchConvertTest_81, ConvertsBasicCString_81) {
    const char* input = "hello";
    std::string out = Catch::convert(input);
    EXPECT_EQ(out, "hello");
}

TEST(CatchConvertTest_81, ConvertsEmptyCString_81) {
    const char* input = "";
    std::string out = Catch::convert(input);
    EXPECT_TRUE(out.empty());
    EXPECT_EQ(out, "");
}

TEST(CatchConvertTest_81, StopsAtFirstNullTerminator_81) {
    // Buffer with an embedded '\0' followed by extra bytes that should be ignored
    const char buf[] = { 'a', 'b', '\0', 'x', 'y', 'z' };
    const char* input = buf; // decays to pointer
    std::string out = Catch::convert(input);
    EXPECT_EQ(out, "ab"); // observable: C-string ends at first '\0'
}

TEST(CatchConvertTest_81, PreservesUTF8Bytes_81) {
    // Confirm non-ASCII/UTF-8 data is passed through unchanged as bytes
    const char* input = u8"안녕하세요"; // UTF-8 literal
    std::string out = Catch::convert(input);
    EXPECT_EQ(out, std::string(input));
}

TEST(CatchConvertTest_81, HandlesModerateLengthStrings_81) {
    // A moderately long string that should be well within any reasonable safety cap
    // (We do not assert truncation behavior; we only check the observable echo.)
    std::string big(256, 'A'); // 256 'A's
    std::string out = Catch::convert(big.c_str());
    EXPECT_EQ(out, big);
}

} // namespace
