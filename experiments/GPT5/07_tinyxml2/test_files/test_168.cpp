// File: ./TestProjects/tinyxml2/tests/xmlutil_tostr_float_test_168.cpp

#include <gtest/gtest.h>

#include <clocale>
#include <cstdio>
#include <cstring>
#include <string>

#include "tinyxml2.h"

namespace {

class XMLUtilToStrFloatTest_168 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure decimal separator is '.' regardless of environment.
        std::setlocale(LC_NUMERIC, "C");
    }

    static std::string StdExpected(float v) {
        char expected[128] = {};
        std::snprintf(expected, sizeof(expected), "%.8g", static_cast<double>(v));
        return std::string(expected);
    }
};

TEST_F(XMLUtilToStrFloatTest_168, FormatsSimpleValues_168) {
    char buffer[64] = {};
    tinyxml2::XMLUtil::ToStr(0.0f, buffer, static_cast<int>(sizeof(buffer)));
    EXPECT_STREQ(buffer, "0");

    std::memset(buffer, 0, sizeof(buffer));
    tinyxml2::XMLUtil::ToStr(1.5f, buffer, static_cast<int>(sizeof(buffer)));
    EXPECT_STREQ(buffer, "1.5");

    std::memset(buffer, 0, sizeof(buffer));
    tinyxml2::XMLUtil::ToStr(-2.25f, buffer, static_cast<int>(sizeof(buffer)));
    EXPECT_STREQ(buffer, "-2.25");
}

TEST_F(XMLUtilToStrFloatTest_168, MatchesPrintfGWithEightSignificantDigits_168) {
    const float values[] = {
        3.1415927f,
        1234567.0f,
        0.00012345678f,
        34028235e31f  // near FLT_MAX scale without including <cfloat>
    };

    for (float v : values) {
        char buffer[128] = {};
        tinyxml2::XMLUtil::ToStr(v, buffer, static_cast<int>(sizeof(buffer)));

        const std::string expected = StdExpected(v);
        EXPECT_EQ(std::string(buffer), expected) << "v=" << v;
    }
}

TEST_F(XMLUtilToStrFloatTest_168, WritesNullTerminatorWhenBufferSizeIsOne_168) {
    char buffer[1];
    buffer[0] = 'X';

    tinyxml2::XMLUtil::ToStr(12.34f, buffer, 1);

    // With a one-byte buffer, the only safe/observable outcome is a terminator.
    EXPECT_EQ(buffer[0], '\0');
}

TEST_F(XMLUtilToStrFloatTest_168, TruncatesAndNullTerminatesWhenBufferTooSmall_168) {
    const float v = 12345.6789f;

    const std::string expectedFull = StdExpected(v);
    ASSERT_FALSE(expectedFull.empty());

    // Make a deliberately small buffer.
    char buffer[6];
    std::memset(buffer, 'Z', sizeof(buffer));

    tinyxml2::XMLUtil::ToStr(v, buffer, static_cast<int>(sizeof(buffer)));

    // Must be NUL-terminated within the provided size.
    EXPECT_EQ(buffer[sizeof(buffer) - 1], '\0');

    // The written content should match the prefix of the full expected formatting.
    const std::string got(buffer);
    EXPECT_EQ(got, expectedFull.substr(0, got.size()));
}

TEST_F(XMLUtilToStrFloatTest_168, DoesNotModifyBufferWhenBufferSizeIsZero_168) {
    // If size is zero, standard snprintf-style behavior is "write nothing".
    // This test checks the observable outcome (no modification) and that the call is safe.
    char buffer[4] = {'A', 'B', 'C', 'D'};

    tinyxml2::XMLUtil::ToStr(9.8765f, buffer, 0);

    EXPECT_EQ(buffer[0], 'A');
    EXPECT_EQ(buffer[1], 'B');
    EXPECT_EQ(buffer[2], 'C');
    EXPECT_EQ(buffer[3], 'D');
}

}  // namespace
