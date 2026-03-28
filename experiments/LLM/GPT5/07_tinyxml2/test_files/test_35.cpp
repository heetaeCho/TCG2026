// TEST_ID: 35
#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

class XMLUtilSkipWhiteSpaceTest_35 : public ::testing::Test {
protected:
    // Helper to compute offset in a C-string buffer (assumes result points inside buffer).
    static ptrdiff_t Offset(const char* base, const char* p) { return p - base; }
};

TEST_F(XMLUtilSkipWhiteSpaceTest_35, NoLeadingWhitespace_ReturnsSamePointer_35) {
    const char* text = "abc";
    int line = 1;

    const char* out = tinyxml2::XMLUtil::SkipWhiteSpace(text, &line);

    EXPECT_EQ(out, text);
    EXPECT_EQ(*out, 'a');
    EXPECT_EQ(line, 1);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, LeadingSpacesTabs_SkipsToNonWhitespace_35) {
    const char* text = " \t\t  xyz";
    int line = 1;

    const char* out = tinyxml2::XMLUtil::SkipWhiteSpace(text, &line);

    ASSERT_NE(out, nullptr);
    EXPECT_EQ(*out, 'x');
    EXPECT_GT(out, text);  // Should move forward for leading whitespace.
    EXPECT_EQ(line, 1);    // No newlines here.
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, LeadingNewlines_IncrementsLineNumber_35) {
    const char* text = "\n\n  A";
    int line = 10;

    const char* out = tinyxml2::XMLUtil::SkipWhiteSpace(text, &line);

    ASSERT_NE(out, nullptr);
    EXPECT_EQ(*out, 'A');
    EXPECT_GT(out, text);
    // Observable expectation: skipping '\n' advances the line counter accordingly.
    EXPECT_EQ(line, 12);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, MixedWhitespaceAndText_SkipsCorrectly_35) {
    const char* text = " \n\t\r\nZ";
    int line = 1;

    const char* out = tinyxml2::XMLUtil::SkipWhiteSpace(text, &line);

    ASSERT_NE(out, nullptr);
    EXPECT_EQ(*out, 'Z');
    EXPECT_GE(line, 1);
    // At least one newline is present; line should not decrease.
    EXPECT_GT(line, 1);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, AllWhitespace_ReturnsPointerToNullTerminator_35) {
    const char* text = " \t\r\n\n";
    int line = 1;

    const char* out = tinyxml2::XMLUtil::SkipWhiteSpace(text, &line);

    ASSERT_NE(out, nullptr);
    EXPECT_EQ(*out, '\0');   // Reached end of string.
    EXPECT_GE(line, 1);      // Line should not decrease.
    EXPECT_GT(out, text);    // Should advance through whitespace.
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, EmptyString_ReturnsBegin_35) {
    const char* text = "";
    int line = 7;

    const char* out = tinyxml2::XMLUtil::SkipWhiteSpace(text, &line);

    EXPECT_EQ(out, text);
    EXPECT_EQ(*out, '\0');
    EXPECT_EQ(line, 7);
}

TEST_F(XMLUtilSkipWhiteSpaceTest_35, MutableOverload_MatchesConstOverloadAndPointsIntoSameBuffer_35) {
    char buf[] = " \n  hello";
    int line1 = 1;
    int line2 = 1;

    // Call both overloads on the same underlying buffer.
    const char* outConst = tinyxml2::XMLUtil::SkipWhiteSpace(static_cast<const char*>(buf), &line1);
    char* outMutable = tinyxml2::XMLUtil::SkipWhiteSpace(buf, &line2);

    ASSERT_NE(outConst, nullptr);
    ASSERT_NE(outMutable, nullptr);

    // The mutable overload is specified (in provided code) to delegate to the const overload.
    EXPECT_EQ(outConst, static_cast<const char*>(outMutable));
    EXPECT_EQ(line1, line2);

    // Returned pointer should be within the original buffer range (including pointing at '\0').
    const char* base = buf;
    const char* end = buf + sizeof(buf) - 1;  // points at '\0'
    EXPECT_GE(outConst, base);
    EXPECT_LE(outConst, end);

    // Basic sanity about where it lands for this input.
    EXPECT_EQ(*outMutable, 'h');
    EXPECT_EQ(Offset(base, outConst), Offset(base, static_cast<const char*>(outMutable)));
}

}  // namespace
