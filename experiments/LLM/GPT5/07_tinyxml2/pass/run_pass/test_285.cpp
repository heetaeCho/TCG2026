// TEST_ID: 285
// File: test_xmldocument_clearerror_285.cpp

#include <gtest/gtest.h>

#include <cstring>   // strlen
#include "tinyxml2.h"

namespace {

class XMLDocumentClearErrorTest_285 : public ::testing::Test {
protected:
    static tinyxml2::XMLDocument MakeDoc() {
        // Prefer the default ctor if available (tinyxml2 typically provides defaults).
        // This keeps the test resilient to header differences in Whitespace enum exposure.
        return tinyxml2::XMLDocument();
    }

    static void ForceParseError(tinyxml2::XMLDocument& doc) {
        // Intentionally malformed XML to reliably create an observable error.
        const char* badXml = "<root><child></root>";
        const tinyxml2::XMLError err = doc.Parse(badXml, std::strlen(badXml));
        (void)err; // We don't assume a specific error code, only that an error becomes observable.
    }

    static bool IsNullOrEmpty(const char* s) {
        return (s == nullptr) || (s[0] == '\0');
    }
};

}  // namespace

TEST_F(XMLDocumentClearErrorTest_285, ClearErrorAfterParseErrorResetsObservableErrorState_285) {
    tinyxml2::XMLDocument doc = MakeDoc();

    ForceParseError(doc);

    // Precondition: error must be observable through the public interface.
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorID(), tinyxml2::XML_SUCCESS);

    // Act
    doc.ClearError();

    // Postconditions per implementation snippet: _errorID = XML_SUCCESS, _errorLineNum = 0, _errorStr.Reset()
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), tinyxml2::XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);

    // Error string should be cleared (exact representation may vary: nullptr or "").
    EXPECT_TRUE(IsNullOrEmpty(doc.ErrorStr()));

    // ErrorName should correspond to the success state.
    const char* expectedName = tinyxml2::XMLDocument::ErrorIDToName(tinyxml2::XML_SUCCESS);
    ASSERT_NE(expectedName, nullptr);
    ASSERT_NE(doc.ErrorName(), nullptr);
    EXPECT_STREQ(doc.ErrorName(), expectedName);
}

TEST_F(XMLDocumentClearErrorTest_285, ClearErrorWhenNoErrorIsIdempotent_285) {
    tinyxml2::XMLDocument doc = MakeDoc();

    // Precondition: a fresh document should not report an error.
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), tinyxml2::XML_SUCCESS);

    const int beforeLine = doc.ErrorLineNum();
    const char* beforeStr = doc.ErrorStr();
    const char* beforeName = doc.ErrorName();

    // Act: calling ClearError repeatedly should be safe and keep the same observable "no error" state.
    doc.ClearError();
    doc.ClearError();

    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), tinyxml2::XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0); // per ClearError implementation sets it to 0

    // Error string should remain cleared.
    EXPECT_TRUE(IsNullOrEmpty(doc.ErrorStr()));

    // ErrorName should still map to success.
    const char* expectedName = tinyxml2::XMLDocument::ErrorIDToName(tinyxml2::XML_SUCCESS);
    ASSERT_NE(expectedName, nullptr);
    ASSERT_NE(doc.ErrorName(), nullptr);
    EXPECT_STREQ(doc.ErrorName(), expectedName);

    // Optional: If the fresh document already had line 0 and empty string, these may match prior values.
    // We avoid strict assumptions about pointer identity; just check no-error invariants above.
    (void)beforeLine;
    (void)beforeStr;
    (void)beforeName;
}

TEST_F(XMLDocumentClearErrorTest_285, ClearErrorResetsErrorLineNumToZero_285) {
    tinyxml2::XMLDocument doc = MakeDoc();

    ForceParseError(doc);

    // If parsing reported an error, line number may be non-zero in some implementations,
    // but we only require it is observable and then reset to zero by ClearError.
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(doc.ErrorID(), tinyxml2::XML_SUCCESS);

    doc.ClearError();

    EXPECT_EQ(doc.ErrorLineNum(), 0);
    EXPECT_EQ(doc.ErrorID(), tinyxml2::XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
}

TEST_F(XMLDocumentClearErrorTest_285, ClearErrorCanBeCalledMultipleTimesAfterAnError_285) {
    tinyxml2::XMLDocument doc = MakeDoc();

    ForceParseError(doc);
    EXPECT_TRUE(doc.Error());

    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), tinyxml2::XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
    EXPECT_TRUE(IsNullOrEmpty(doc.ErrorStr()));

    // Call again to ensure stability.
    doc.ClearError();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), tinyxml2::XML_SUCCESS);
    EXPECT_EQ(doc.ErrorLineNum(), 0);
    EXPECT_TRUE(IsNullOrEmpty(doc.ErrorStr()));
}
