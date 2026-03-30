// TEST_ID: 283
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLDocumentParseTest_283 : public ::testing::Test {
protected:
    XMLDocument doc;
};

TEST_F(XMLDocumentParseTest_283, ParseNullptrZeroBytesReturnsEmptyDocumentError_283) {
    const XMLError err = doc.Parse(nullptr, 0);
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, err);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, doc.ErrorID());
}

TEST_F(XMLDocumentParseTest_283, ParseNullptrMinusOneBytesReturnsEmptyDocumentError_283) {
    const XMLError err = doc.Parse(nullptr, static_cast<size_t>(-1));
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, err);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, doc.ErrorID());
}

TEST_F(XMLDocumentParseTest_283, ParseEmptyStringNonZeroBytesReturnsEmptyDocumentError_283) {
    const char* xml = "";
    const XMLError err = doc.Parse(xml, 1);
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, err);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(XML_ERROR_EMPTY_DOCUMENT, doc.ErrorID());
}

TEST_F(XMLDocumentParseTest_283, ParseValidXmlMinusOneSucceedsAndCreatesRoot_283) {
    const char* xml = "<root/>";
    const XMLError err = doc.Parse(xml, static_cast<size_t>(-1));

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());

    XMLElement* root = doc.RootElement();
    ASSERT_NE(nullptr, root);
    EXPECT_STREQ("root", root->Name());
}

TEST_F(XMLDocumentParseTest_283, ParseValidXmlExplicitByteCountSucceeds_283) {
    const char xml[] = "<root></root>";
    const size_t nBytes = sizeof(xml) - 1; // exclude terminator

    const XMLError err = doc.Parse(xml, nBytes);

    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FALSE(doc.Error());
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Name());
}

TEST_F(XMLDocumentParseTest_283, ParseMalformedXmlReportsError_283) {
    const char* xml = "<root>"; // missing end tag
    const XMLError err = doc.Parse(xml, static_cast<size_t>(-1));

    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(XML_SUCCESS, doc.ErrorID());
    EXPECT_EQ(err, doc.ErrorID());
}

TEST_F(XMLDocumentParseTest_283, ParseClearsPreviousErrorStateWhenParsingValidXml_283) {
    const char* bad = "<root>";
    ASSERT_NE(XML_SUCCESS, doc.Parse(bad, static_cast<size_t>(-1)));
    ASSERT_TRUE(doc.Error());

    const char* good = "<root/>";
    const XMLError err2 = doc.Parse(good, static_cast<size_t>(-1));

    EXPECT_EQ(XML_SUCCESS, err2);
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("root", doc.RootElement()->Name());
}

TEST_F(XMLDocumentParseTest_283, ParseReplacesPreviousDocumentContent_283) {
    ASSERT_EQ(XML_SUCCESS, doc.Parse("<a/>", static_cast<size_t>(-1)));
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("a", doc.RootElement()->Name());

    ASSERT_EQ(XML_SUCCESS, doc.Parse("<b/>", static_cast<size_t>(-1)));
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("b", doc.RootElement()->Name());
}

}  // namespace
