// File: ./TestProjects/tinyxml2/tinyxml2_vscprintf_test_153.cpp

#include <gtest/gtest.h>

#include <cstdarg>
#include <cstdio>
#include <string>

// NOTE:
// The function under test is `static inline` inside tinyxml2.cpp, so it has internal linkage.
// To test it strictly through the provided interface, we include the implementation file
// in this test translation unit.
#include "tinyxml2.cpp"

namespace {

int Call_TIXML_VSCPRINTF_And_Std_153(const char* format, int* stdLenOut, ...) {
    va_list va1;
    va_start(va1, stdLenOut);

    va_list va2;
    va_copy(va2, va1);

    const int tinyLen = TIXML_VSCPRINTF(format, va1);
    const int stdLen = std::vsnprintf(nullptr, 0, format, va2);

    va_end(va2);
    va_end(va1);

    if (stdLenOut) {
        *stdLenOut = stdLen;
    }
    return tinyLen;
}

}  // namespace

TEST(TIXML_VSCPRINTF_Test_153, PlainString_NoArgs_MatchesVsnprintf_153) {
    int stdLen = -1;
    const int tinyLen = Call_TIXML_VSCPRINTF_And_Std_153("hello", &stdLen);
    EXPECT_EQ(tinyLen, stdLen);
    EXPECT_EQ(tinyLen, 5);
}

TEST(TIXML_VSCPRINTF_Test_153, IntegerFormatting_MatchesVsnprintf_153) {
    int stdLen = -1;
    const int tinyLen = Call_TIXML_VSCPRINTF_And_Std_153("value=%d", &stdLen, 42);
    EXPECT_EQ(tinyLen, stdLen);
    EXPECT_EQ(tinyLen, 8);  // "value=42"
}

TEST(TIXML_VSCPRINTF_Test_153, MultipleArguments_MatchesVsnprintf_153) {
    int stdLen = -1;
    const int tinyLen =
        Call_TIXML_VSCPRINTF_And_Std_153("%s:%d:%0.2f", &stdLen, "a", 7, 3.5);
    EXPECT_EQ(tinyLen, stdLen);

    // Also sanity-check against an expected rendering length.
    // "a:7:3.50" => 8 chars
    EXPECT_EQ(tinyLen, 8);
}

TEST(TIXML_VSCPRINTF_Test_153, EmptyFormat_ReturnsZero_153) {
    int stdLen = -1;
    const int tinyLen = Call_TIXML_VSCPRINTF_And_Std_153("", &stdLen);
    EXPECT_EQ(tinyLen, stdLen);
    EXPECT_EQ(tinyLen, 0);
}

TEST(TIXML_VSCPRINTF_Test_153, LongStringArgument_Boundary_MatchesVsnprintf_153) {
    // Boundary-ish: a reasonably long formatted result.
    std::string s(4096, 'x');

    int stdLen = -1;
    const int tinyLen = Call_TIXML_VSCPRINTF_And_Std_153("%s", &stdLen, s.c_str());
    EXPECT_EQ(tinyLen, stdLen);
    EXPECT_EQ(tinyLen, static_cast<int>(s.size()));
}

TEST(TIXML_VSCPRINTF_Test_153, PrecisionAndWidth_Boundary_MatchesVsnprintf_153) {
    int stdLen = -1;
    const int tinyLen = Call_TIXML_VSCPRINTF_And_Std_153("[%10.3s]", &stdLen, "abcdef");
    EXPECT_EQ(tinyLen, stdLen);
    // "%10.3s" prints 3 chars right-justified in width 10 => 10 chars inside brackets => 12 total
    EXPECT_EQ(tinyLen, 12);
}
