#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class StrPairParseNameTest_159 : public ::testing::Test {
protected:
    StrPair strPair;
};

// Test null pointer input returns null
TEST_F(StrPairParseNameTest_159, NullPointerReturnsNull_159) {
    char* result = strPair.ParseName(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test empty string returns null
TEST_F(StrPairParseNameTest_159, EmptyStringReturnsNull_159) {
    char input[] = "";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}

// Test string starting with digit returns null (not a valid name start char)
TEST_F(StrPairParseNameTest_159, StartsWithDigitReturnsNull_159) {
    char input[] = "123abc";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}

// Test string starting with a space returns null
TEST_F(StrPairParseNameTest_159, StartsWithSpaceReturnsNull_159) {
    char input[] = " name";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}

// Test valid simple name (all lowercase letters)
TEST_F(StrPairParseNameTest_159, ValidSimpleName_159) {
    char input[] = "hello world";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    // result should point to the space after "hello"
    EXPECT_EQ(result, input + 5);
}

// Test single character valid name
TEST_F(StrPairParseNameTest_159, SingleCharName_159) {
    char input[] = "a";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 1);
}

// Test name with underscore start
TEST_F(StrPairParseNameTest_159, UnderscoreStartName_159) {
    char input[] = "_myName";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 7);
}

// Test name with colon start (colon is valid XML name start char)
TEST_F(StrPairParseNameTest_159, ColonStartName_159) {
    char input[] = ":name";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 5);
}

// Test name containing digits after the first char
TEST_F(StrPairParseNameTest_159, NameWithDigits_159) {
    char input[] = "item123";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 7);
}

// Test name containing hyphens (hyphen is valid name char but not start char)
TEST_F(StrPairParseNameTest_159, NameWithHyphen_159) {
    char input[] = "my-name";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 7);
}

// Test name containing dots (dot is valid name char)
TEST_F(StrPairParseNameTest_159, NameWithDot_159) {
    char input[] = "my.name";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 7);
}

// Test string starting with hyphen returns null (hyphen is not a name start char)
TEST_F(StrPairParseNameTest_159, StartsWithHyphenReturnsNull_159) {
    char input[] = "-name";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}

// Test string starting with dot returns null (dot is not a name start char)
TEST_F(StrPairParseNameTest_159, StartsWithDotReturnsNull_159) {
    char input[] = ".name";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}

// Test name stops at special character like '='
TEST_F(StrPairParseNameTest_159, NameStopsAtEquals_159) {
    char input[] = "attr=value";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 4);
}

// Test name stops at '<'
TEST_F(StrPairParseNameTest_159, NameStopsAtAngleBracket_159) {
    char input[] = "tag<other";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 3);
}

// Test name stops at '>'
TEST_F(StrPairParseNameTest_159, NameStopsAtClosingAngleBracket_159) {
    char input[] = "tag>content";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 3);
}

// Test name stops at '/'
TEST_F(StrPairParseNameTest_159, NameStopsAtSlash_159) {
    char input[] = "tag/>";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 3);
}

// Test that GetStr returns the parsed name
TEST_F(StrPairParseNameTest_159, GetStrReturnsName_159) {
    char input[] = "myElement ";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    const char* name = strPair.GetStr();
    EXPECT_STREQ(name, "myElement");
}

// Test uppercase name
TEST_F(StrPairParseNameTest_159, UppercaseName_159) {
    char input[] = "ABC";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 3);
}

// Test mixed case name
TEST_F(StrPairParseNameTest_159, MixedCaseName_159) {
    char input[] = "MyElement123";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 12);
}

// Test single underscore name
TEST_F(StrPairParseNameTest_159, SingleUnderscoreName_159) {
    char input[] = "_";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 1);
}

// Test string starting with special XML char '!' returns null
TEST_F(StrPairParseNameTest_159, StartsWithExclamationReturnsNull_159) {
    char input[] = "!comment";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}

// Test string starting with '?' returns null
TEST_F(StrPairParseNameTest_159, StartsWithQuestionMarkReturnsNull_159) {
    char input[] = "?xml";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}

// Test name that is a typical XML element name with namespace
TEST_F(StrPairParseNameTest_159, NameWithNamespaceColon_159) {
    char input[] = "ns:element ";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 10);
    const char* name = strPair.GetStr();
    EXPECT_STREQ(name, "ns:element");
}

// Test name with underscores and digits mixed
TEST_F(StrPairParseNameTest_159, ComplexValidName_159) {
    char input[] = "_a1.b2-c3:d4 ";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result, input + 12);
}

// Test string starting with tab returns null
TEST_F(StrPairParseNameTest_159, StartsWithTabReturnsNull_159) {
    char input[] = "\tname";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}

// Test string starting with newline returns null
TEST_F(StrPairParseNameTest_159, StartsWithNewlineReturnsNull_159) {
    char input[] = "\nname";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}

// Test name stops at null terminator
TEST_F(StrPairParseNameTest_159, NameEndsAtNullTerminator_159) {
    char input[] = "name";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, '\0');
    EXPECT_EQ(result, input + 4);
}

// Test Empty() before and after ParseName
TEST_F(StrPairParseNameTest_159, EmptyBeforeAndAfterParse_159) {
    EXPECT_TRUE(strPair.Empty());
    char input[] = "test ";
    char* result = strPair.ParseName(input);
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(strPair.Empty());
}

// Test Reset clears parsed name
TEST_F(StrPairParseNameTest_159, ResetClearsParsedName_159) {
    char input[] = "element ";
    strPair.ParseName(input);
    EXPECT_FALSE(strPair.Empty());
    strPair.Reset();
    EXPECT_TRUE(strPair.Empty());
}

// Test parsing name twice (second parse should overwrite)
TEST_F(StrPairParseNameTest_159, ParseNameTwice_159) {
    char input1[] = "first ";
    char input2[] = "second ";
    strPair.ParseName(input1);
    const char* name1 = strPair.GetStr();
    EXPECT_STREQ(name1, "first");

    strPair.ParseName(input2);
    const char* name2 = strPair.GetStr();
    EXPECT_STREQ(name2, "second");
}

// Test string starting with '@' returns null (not valid name start)
TEST_F(StrPairParseNameTest_159, StartsWithAtSignReturnsNull_159) {
    char input[] = "@attr";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}

// Test string starting with '#' returns null
TEST_F(StrPairParseNameTest_159, StartsWithHashReturnsNull_159) {
    char input[] = "#ref";
    char* result = strPair.ParseName(input);
    EXPECT_EQ(result, nullptr);
}
