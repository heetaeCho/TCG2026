#include <gtest/gtest.h>

#include <cctype>
#include <cstdint>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

class XMLUtilIsNameCharTest_38 : public ::testing::Test {
protected:
    static bool ExpectedIsNameChar(unsigned char ch) {
        // Mirror the inline definition from the provided interface.
        return tinyxml2::XMLUtil::IsNameStartChar(ch) ||
               (std::isdigit(static_cast<unsigned char>(ch)) != 0) ||
               ch == static_cast<unsigned char>('.') ||
               ch == static_cast<unsigned char>('-');
    }
};

TEST_F(XMLUtilIsNameCharTest_38, MatchesDefinitionForAllByteValues_38) {
    for (int i = 0; i <= 255; ++i) {
        const unsigned char ch = static_cast<unsigned char>(i);
        const bool expected = ExpectedIsNameChar(ch);
        const bool actual = tinyxml2::XMLUtil::IsNameChar(ch);
        EXPECT_EQ(actual, expected) << "Mismatch at byte value: " << i;
    }
}

TEST_F(XMLUtilIsNameCharTest_38, AcceptsDotDashAndDigits_38) {
    EXPECT_TRUE(tinyxml2::XMLUtil::IsNameChar(static_cast<unsigned char>('.')));
    EXPECT_TRUE(tinyxml2::XMLUtil::IsNameChar(static_cast<unsigned char>('-')));

    for (unsigned char ch = static_cast<unsigned char>('0');
         ch <= static_cast<unsigned char>('9');
         ++ch) {
        EXPECT_TRUE(tinyxml2::XMLUtil::IsNameChar(ch)) << "Digit rejected: " << ch;
    }
}

TEST_F(XMLUtilIsNameCharTest_38, IfIsNameStartCharThenIsNameChar_38) {
    // Don’t assume which characters are valid start chars; just verify the implication.
    const unsigned char candidates[] = {
        static_cast<unsigned char>('A'),
        static_cast<unsigned char>('Z'),
        static_cast<unsigned char>('a'),
        static_cast<unsigned char>('z'),
        static_cast<unsigned char>('_'),
        static_cast<unsigned char>(':'),
        static_cast<unsigned char>('\xC0'), // extended byte, behavior is implementation-defined
        static_cast<unsigned char>(0),
        static_cast<unsigned char>(255),
    };

    for (unsigned char ch : candidates) {
        if (tinyxml2::XMLUtil::IsNameStartChar(ch)) {
            EXPECT_TRUE(tinyxml2::XMLUtil::IsNameChar(ch))
                << "IsNameStartChar true but IsNameChar false for byte: "
                << static_cast<int>(ch);
        }
    }
}

}  // namespace
