// File: test_xmlutil_stringequal_40.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

using tinyxml2::XMLUtil;

class XMLUtilStringEqualTest_40 : public ::testing::Test {};

// Normal operation: exact equality / inequality
TEST_F(XMLUtilStringEqualTest_40, SamePointersReturnTrue_40) {
    const char* p = "abc";
    EXPECT_TRUE(XMLUtil::StringEqual(p, p));
    EXPECT_TRUE(XMLUtil::StringEqual(p, p, 0));
    EXPECT_TRUE(XMLUtil::StringEqual(p, p, 1));
    EXPECT_TRUE(XMLUtil::StringEqual(p, p, 3));
}

TEST_F(XMLUtilStringEqualTest_40, IdenticalContentDifferentPointersReturnTrue_40) {
    const char p[] = "tinyxml2";
    const char q[] = "tinyxml2";
    ASSERT_NE(static_cast<const void*>(p), static_cast<const void*>(q)); // different storage
    EXPECT_TRUE(XMLUtil::StringEqual(p, q));
}

TEST_F(XMLUtilStringEqualTest_40, DifferentContentReturnFalse_40) {
    EXPECT_FALSE(XMLUtil::StringEqual("abc", "abd"));
    EXPECT_FALSE(XMLUtil::StringEqual("abc", "abC"));
    EXPECT_FALSE(XMLUtil::StringEqual("abc", "abcd"));
    EXPECT_FALSE(XMLUtil::StringEqual("abcd", "abc"));
}

// Boundary conditions: nChar behavior (0, partial compare, beyond length)
TEST_F(XMLUtilStringEqualTest_40, ZeroNCharReturnsTrueForNonNullInputs_40) {
    // With nChar == 0, the comparison is for zero characters; observable result should be "equal".
    EXPECT_TRUE(XMLUtil::StringEqual("abc", "xyz", 0));
    EXPECT_TRUE(XMLUtil::StringEqual("", "nonempty", 0));
    EXPECT_TRUE(XMLUtil::StringEqual("nonempty", "", 0));
}

TEST_F(XMLUtilStringEqualTest_40, PartialCompareRespectsNChar_40) {
    EXPECT_TRUE(XMLUtil::StringEqual("abcdef", "abcXYZ", 3));   // first 3 match
    EXPECT_FALSE(XMLUtil::StringEqual("abcdef", "abcXYZ", 4));  // first 4 differ
}

TEST_F(XMLUtilStringEqualTest_40, NCharLongerThanCommonPrefixDetectsDifference_40) {
    EXPECT_FALSE(XMLUtil::StringEqual("abc", "abcd", 4));
    EXPECT_FALSE(XMLUtil::StringEqual("abcd", "abc", 4));
}

TEST_F(XMLUtilStringEqualTest_40, ExactLengthCompareMatchesWhenAllCharsMatch_40) {
    EXPECT_TRUE(XMLUtil::StringEqual("abc", "abc", 3));
    EXPECT_TRUE(XMLUtil::StringEqual("abc", "abc", 100)); // large nChar shouldn't break equality
}

TEST_F(XMLUtilStringEqualTest_40, ComparesIncludingEmbeddedNullWithinNChar_40) {
    // Using explicit buffers to include '\0' before the end.
    const char p[] = {'a', 'b', '\0', 'c', '\0'};
    const char q[] = {'a', 'b', '\0', 'd', '\0'};

    // First 2 chars equal
    EXPECT_TRUE(XMLUtil::StringEqual(p, q, 2));

    // First 3 bytes include '\0' which matches too
    EXPECT_TRUE(XMLUtil::StringEqual(p, q, 3));

    // At 4th byte, 'c' vs 'd' differs
    EXPECT_FALSE(XMLUtil::StringEqual(p, q, 4));
}

// Exceptional / error cases (observable through death/assert behavior).
// NOTE: tinyxml2 uses TIXMLASSERT; in debug builds this typically aborts.
// These tests are guarded to avoid failing on builds where asserts are compiled out.
#if !defined(NDEBUG)
TEST_F(XMLUtilStringEqualTest_40, NullFirstPointerTriggersAssertDeath_40) {
    EXPECT_DEATH({ (void)XMLUtil::StringEqual(nullptr, "abc"); }, "");
}

TEST_F(XMLUtilStringEqualTest_40, NullSecondPointerTriggersAssertDeath_40) {
    EXPECT_DEATH({ (void)XMLUtil::StringEqual("abc", nullptr); }, "");
}

TEST_F(XMLUtilStringEqualTest_40, NegativeNCharTriggersAssertDeath_40) {
    EXPECT_DEATH({ (void)XMLUtil::StringEqual("abc", "abc", -1); }, "");
}
#endif
