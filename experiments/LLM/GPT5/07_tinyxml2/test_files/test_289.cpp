// TEST_ID: 289
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLDocumentTest_289 : public ::testing::Test {
protected:
    // Use a consistent constructor across tests.
    XMLDocument doc_{ /*processEntities=*/true, XMLDocument::Whitespace::PRESERVE_WHITESPACE };
};

TEST_F(XMLDocumentTest_289, ErrorNameMatchesErrorIDToNameOnFreshDocument_289) {
    // On a fresh document, ErrorName() should be consistent with ErrorIDToName(ErrorID()).
    const char* name = doc_.ErrorName();
    ASSERT_NE(name, nullptr);

    const char* expected = XMLDocument::ErrorIDToName(doc_.ErrorID());
    ASSERT_NE(expected, nullptr);

    EXPECT_STREQ(name, expected);
}

TEST_F(XMLDocumentTest_289, ErrorNameMatchesErrorIDToNameAfterSuccessfulParse_289) {
    const char* xml = "<root/>";
    XMLError err = doc_.Parse(xml, strlen(xml));
    EXPECT_EQ(err, XML_SUCCESS);

    const char* name = doc_.ErrorName();
    ASSERT_NE(name, nullptr);

    const char* expected = XMLDocument::ErrorIDToName(doc_.ErrorID());
    ASSERT_NE(expected, nullptr);

    EXPECT_STREQ(name, expected);
}

TEST_F(XMLDocumentTest_289, ErrorNameMatchesErrorIDToNameAfterParseError_289) {
    // Intentionally malformed XML to trigger an observable error.
    const char* badXml = "<root>";  // missing closing tag
    XMLError err = doc_.Parse(badXml, strlen(badXml));
    EXPECT_NE(err, XML_SUCCESS);

    const char* name = doc_.ErrorName();
    ASSERT_NE(name, nullptr);

    const char* expected = XMLDocument::ErrorIDToName(doc_.ErrorID());
    ASSERT_NE(expected, nullptr);

    EXPECT_STREQ(name, expected);
}

TEST_F(XMLDocumentTest_289, ErrorNameMatchesErrorIDToNameAfterClearError_289) {
    // Force an error first.
    const char* badXml = "<root>";
    XMLError err = doc_.Parse(badXml, strlen(badXml));
    ASSERT_NE(err, XML_SUCCESS);

    // Then clear it.
    doc_.ClearError();

    const char* name = doc_.ErrorName();
    ASSERT_NE(name, nullptr);

    const char* expected = XMLDocument::ErrorIDToName(doc_.ErrorID());
    ASSERT_NE(expected, nullptr);

    EXPECT_STREQ(name, expected);
    EXPECT_EQ(doc_.ErrorID(), XML_SUCCESS);
}

TEST_F(XMLDocumentTest_289, ErrorNameMatchesErrorIDToNameAfterLoadFileFailure_289) {
    // Use a very likely non-existent filename to trigger an error through the public interface.
    XMLError err = doc_.LoadFile("this_file_should_not_exist___TEST_ID_289__.xml");
    EXPECT_NE(err, XML_SUCCESS);

    const char* name = doc_.ErrorName();
    ASSERT_NE(name, nullptr);

    const char* expected = XMLDocument::ErrorIDToName(doc_.ErrorID());
    ASSERT_NE(expected, nullptr);

    EXPECT_STREQ(name, expected);
}

TEST_F(XMLDocumentTest_289, ErrorNameMatchesErrorIDToNameWithZeroBytesParseBoundary_289) {
    // Boundary: nBytes == 0 with a valid pointer (avoid nullptr).
    const char* xml = "<root/>";
    XMLError err = doc_.Parse(xml, 0);

    // We don't assume what the implementation returns for this boundary,
    // only that ErrorName() remains consistent with ErrorIDToName(ErrorID()).
    (void)err;

    const char* name = doc_.ErrorName();
    ASSERT_NE(name, nullptr);

    const char* expected = XMLDocument::ErrorIDToName(doc_.ErrorID());
    ASSERT_NE(expected, nullptr);

    EXPECT_STREQ(name, expected);
}
