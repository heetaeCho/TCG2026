// TEST_ID: 205
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLUnknownParseDeepTest_205 : public ::testing::Test {};

// ParseDeep() is an internal parsing routine for XMLUnknown nodes.
// We treat it as a black box and verify only *observable* behavior through
// the public XMLDocument::Parse() API (error codes / success, and presence
// of an XMLUnknown node when input is well-formed).

TEST_F(XMLUnknownParseDeepTest_205, WellFormedUnknownParsesWithoutError_205)
{
    XMLDocument doc;

    // A minimal "unknown" construct in TinyXML2 is typically something starting with "<!"
    // and ending with ">" (represented as XMLUnknown in the DOM).
    const char* xml = "<root><!SOME_UNKNOWN_STUFF></root>";

    XMLError err = doc.Parse(xml);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    // Verify an XMLUnknown node exists as a child of <root>.
    const XMLNode* child = root->FirstChild();
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->ToUnknown() != nullptr, true);
}

TEST_F(XMLUnknownParseDeepTest_205, MissingClosingAngleBracketSetsParsingUnknownError_205)
{
    XMLDocument doc;

    // Missing the terminating '>' for the unknown node should cause an "unknown parsing" error.
    const char* xml = "<root><!SOME_UNKNOWN_STUFF</root>";

    XMLError err = doc.Parse(xml);

    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());

    // Observable error code set by the document.
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_PARSING_UNKNOWN);
}

TEST_F(XMLUnknownParseDeepTest_205, UnknownAtEndWithoutClosingAngleBracketErrors_205)
{
    XMLDocument doc;

    // Another malformed case: unknown node is last thing and never closes.
    const char* xml = "<root><!UNFINISHED";

    XMLError err = doc.Parse(xml);

    EXPECT_NE(err, XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_PARSING_UNKNOWN);
}

TEST_F(XMLUnknownParseDeepTest_205, DocumentRemainsUsableAfterUnknownParseError_205)
{
    XMLDocument doc;

    // First parse fails due to malformed unknown.
    const char* badXml = "<root><!BAD_UNKNOWN</root>";
    EXPECT_NE(doc.Parse(badXml), XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), XML_ERROR_PARSING_UNKNOWN);

    // Then parsing a valid document should succeed (public observable behavior).
    doc.Clear();
    const char* goodXml = "<root><child/></root>";
    EXPECT_EQ(doc.Parse(goodXml), XML_SUCCESS);
    EXPECT_FALSE(doc.Error());

    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    EXPECT_NE(root->FirstChildElement("child"), nullptr);
}
