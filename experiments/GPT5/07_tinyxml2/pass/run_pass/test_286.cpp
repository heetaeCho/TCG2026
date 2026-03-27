// File: test_xmldocument_erroridtoname_286.cpp

#include <gtest/gtest.h>

#include <set>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDocumentErrorIDToNameTest_286 : public ::testing::Test {
protected:
    // Call via instance so it works whether ErrorIDToName is static or non-static
    // in the actual codebase.
    XMLDocument doc_{true, PRESERVE_WHITESPACE};
};

TEST_F(XMLDocumentErrorIDToNameTest_286, ReturnsNonNullNonEmptyForAllValidErrorIds_286) {
    std::set<std::string> names;

    for (int i = 0; i < XML_ERROR_COUNT; ++i) {
        const XMLError err = static_cast<XMLError>(i);
        const char* name = doc_.ErrorIDToName(err);

        ASSERT_NE(name, nullptr) << "ErrorIDToName returned nullptr for id=" << i;
        EXPECT_NE(name[0], '\0') << "ErrorIDToName returned empty string for id=" << i;

        names.insert(std::string(name));
    }

    // Observable expectation: each error ID should map to a name string, and names
    // should not all collapse to the same value.
    EXPECT_EQ(names.size(), static_cast<size_t>(XML_ERROR_COUNT));
}

TEST_F(XMLDocumentErrorIDToNameTest_286, Boundary_FirstValidId_ReturnsNonEmpty_286) {
    const char* name = doc_.ErrorIDToName(static_cast<XMLError>(0));
    ASSERT_NE(name, nullptr);
    EXPECT_NE(name[0], '\0');
}

TEST_F(XMLDocumentErrorIDToNameTest_286, Boundary_LastValidId_ReturnsNonEmpty_286) {
    const char* name = doc_.ErrorIDToName(static_cast<XMLError>(XML_ERROR_COUNT - 1));
    ASSERT_NE(name, nullptr);
    EXPECT_NE(name[0], '\0');
}

TEST_F(XMLDocumentErrorIDToNameTest_286, RepeatedCallsForSameId_ReturnSameStringContents_286) {
    const XMLError err = static_cast<XMLError>(0);

    const char* a = doc_.ErrorIDToName(err);
    const char* b = doc_.ErrorIDToName(err);

    ASSERT_NE(a, nullptr);
    ASSERT_NE(b, nullptr);

    // Don't assume pointer identity; compare observable contents.
    EXPECT_STREQ(a, b);
}

#if GTEST_HAS_DEATH_TEST
// These tests verify observable error handling when assertions are enabled.
// tinyxml2 typically implements TIXMLASSERT with assert(). In release builds
// (NDEBUG), these may not fire; guard accordingly.
#ifndef NDEBUG
TEST_F(XMLDocumentErrorIDToNameTest_286, InvalidId_Negative_TriggersAssert_286) {
    EXPECT_DEATH(
        {
            (void)doc_.ErrorIDToName(static_cast<XMLError>(-1));
        },
        ""
    );
}

TEST_F(XMLDocumentErrorIDToNameTest_286, InvalidId_EqualToCount_TriggersAssert_286) {
    EXPECT_DEATH(
        {
            (void)doc_.ErrorIDToName(static_cast<XMLError>(XML_ERROR_COUNT));
        },
        ""
    );
}

TEST_F(XMLDocumentErrorIDToNameTest_286, InvalidId_LargePositive_TriggersAssert_286) {
    EXPECT_DEATH(
        {
            (void)doc_.ErrorIDToName(static_cast<XMLError>(XML_ERROR_COUNT + 12345));
        },
        ""
    );
}
#endif  // !NDEBUG
#endif  // GTEST_HAS_DEATH_TEST
