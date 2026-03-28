// File: ./TestProjects/tinyxml2/tests/test_xmldocument_errorstr_287.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLDocumentErrorStrTest_287 : public ::testing::Test {
protected:
    // Use a concrete constructor signature that exists in the provided header.
    XMLDocumentErrorStrTest_287()
        : doc_(/*processEntities=*/true, /*whitespaceMode=*/PRESERVE_WHITESPACE) {}

    XMLDocument doc_;
};

TEST_F(XMLDocumentErrorStrTest_287, DefaultState_NoError_ReturnsEmptyString_287) {
    const XMLDocument& cdoc = doc_;

    const char* err = cdoc.ErrorStr();
    ASSERT_NE(err, nullptr);
    EXPECT_STREQ(err, "");
    EXPECT_EQ(std::strlen(err), 0u);
}

TEST_F(XMLDocumentErrorStrTest_287, ParseInvalidXml_WhenErrorOccurs_ErrorStrIsNonEmpty_287) {
    // Intentionally malformed / incomplete XML to trigger an error.
    const char* xml = "<root>";
    XMLError result = doc_.Parse(xml, std::strlen(xml));

    // Black-box friendly: if Parse reports success, ErrorStr should be empty; otherwise non-empty.
    const char* err = doc_.ErrorStr();
    ASSERT_NE(err, nullptr);

    if (result == XML_SUCCESS && !doc_.Error()) {
        EXPECT_STREQ(err, "");
        EXPECT_EQ(std::strlen(err), 0u);
    } else {
        EXPECT_STRNE(err, "");
        EXPECT_GT(std::strlen(err), 0u);
    }
}

TEST_F(XMLDocumentErrorStrTest_287, ClearError_AfterParseError_ErrorStrBecomesEmpty_287) {
    const char* badXml = "<root>";
    (void)doc_.Parse(badXml, std::strlen(badXml));

    const char* before = doc_.ErrorStr();
    ASSERT_NE(before, nullptr);

    // Only assert non-empty if an error is actually reported by the implementation.
    if (doc_.Error()) {
        EXPECT_STRNE(before, "");
        EXPECT_GT(std::strlen(before), 0u);
    }

    doc_.ClearError();

    const char* after = doc_.ErrorStr();
    ASSERT_NE(after, nullptr);
    EXPECT_STREQ(after, "");
    EXPECT_EQ(std::strlen(after), 0u);

    // If the implementation exposes error state, it should be cleared as well.
    EXPECT_FALSE(doc_.Error());
}

TEST_F(XMLDocumentErrorStrTest_287, ErrorStr_IsStableAcrossMultipleCalls_287) {
    const char* badXml = "<root>";
    (void)doc_.Parse(badXml, std::strlen(badXml));

    const char* e1 = doc_.ErrorStr();
    const char* e2 = doc_.ErrorStr();

    ASSERT_NE(e1, nullptr);
    ASSERT_NE(e2, nullptr);

    // Compare content, not pointer identity.
    EXPECT_EQ(std::string(e1), std::string(e2));
}

TEST_F(XMLDocumentErrorStrTest_287, ParseNullInput_ThenErrorStrIsValidCStrAndMatchesErrorState_287) {
    // Exercise boundary-like input. We do not assume success/failure; we assert consistency.
    XMLError result = doc_.Parse(nullptr, 0);

    const char* err = doc_.ErrorStr();
    ASSERT_NE(err, nullptr);

    // Must be a valid C-string (strlen must not crash and should be finite).
    const size_t len = std::strlen(err);

    // Black-box friendly consistency checks:
    // - If XML_SUCCESS and no error flagged, expect empty string.
    // - Otherwise allow either empty/non-empty depending on implementation, but if doc_.Error()
    //   is true, ErrorStr should not be empty per observable intent of API.
    if (result == XML_SUCCESS && !doc_.Error()) {
        EXPECT_EQ(len, 0u);
        EXPECT_STREQ(err, "");
    } else if (doc_.Error()) {
        EXPECT_GT(len, 0u);
        EXPECT_STRNE(err, "");
    }
}

}  // namespace
