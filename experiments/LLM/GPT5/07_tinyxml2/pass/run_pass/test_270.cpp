// File: ./TestProjects/tinyxml2/tests/XMLDocumentClearTest_270.cpp

#include <gtest/gtest.h>
#include <cstring>

#include "tinyxml2.h"

namespace tinyxml2 {

class XMLDocumentClearTest_270 : public ::testing::Test {
protected:
    XMLDocumentClearTest_270()
        : doc_(true, PRESERVE_WHITESPACE) {}

    static size_t Len(const char* s) { return s ? std::strlen(s) : 0u; }

    XMLDocument doc_;
};

TEST_F(XMLDocumentClearTest_270, ClearOnEmptyDocument_LeavesNoRootAndNoError_270) {
    EXPECT_FALSE(doc_.Error());
    EXPECT_EQ(doc_.RootElement(), nullptr);

    doc_.Clear();

    EXPECT_FALSE(doc_.Error());
    EXPECT_EQ(doc_.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc_.RootElement(), nullptr);
    EXPECT_TRUE(doc_.NoChildren());

    // Idempotent: calling Clear multiple times should be safe.
    doc_.Clear();
    EXPECT_FALSE(doc_.Error());
    EXPECT_EQ(doc_.RootElement(), nullptr);
    EXPECT_TRUE(doc_.NoChildren());
}

TEST_F(XMLDocumentClearTest_270, ClearAfterSuccessfulParse_RemovesAllChildrenAndRoot_270) {
    const char* xml = "<root><child/><child2>text</child2></root>";
    ASSERT_EQ(doc_.Parse(xml, Len(xml)), XML_SUCCESS);
    ASSERT_FALSE(doc_.Error());
    ASSERT_NE(doc_.RootElement(), nullptr);
    ASSERT_FALSE(doc_.NoChildren());

    // Sanity: structure exists pre-clear.
    EXPECT_STREQ(doc_.RootElement()->Name(), "root");
    EXPECT_EQ(doc_.RootElement()->ChildElementCount(), 2);

    doc_.Clear();

    EXPECT_FALSE(doc_.Error());
    EXPECT_EQ(doc_.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc_.RootElement(), nullptr);
    EXPECT_TRUE(doc_.NoChildren());

    // After Clear(), document should be reusable.
    const char* xml2 = "<again><x/></again>";
    EXPECT_EQ(doc_.Parse(xml2, Len(xml2)), XML_SUCCESS);
    EXPECT_FALSE(doc_.Error());
    ASSERT_NE(doc_.RootElement(), nullptr);
    EXPECT_STREQ(doc_.RootElement()->Name(), "again");
}

TEST_F(XMLDocumentClearTest_270, ClearAfterParseError_ClearsErrorState_270) {
    const char* badXml = "<root><unclosed></root>";
    ASSERT_NE(doc_.Parse(badXml, Len(badXml)), XML_SUCCESS);
    ASSERT_TRUE(doc_.Error());
    EXPECT_NE(doc_.ErrorID(), XML_SUCCESS);

    doc_.Clear();

    EXPECT_FALSE(doc_.Error());
    EXPECT_EQ(doc_.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc_.RootElement(), nullptr);
    EXPECT_TRUE(doc_.NoChildren());

    // Should be able to parse valid XML after clearing error.
    const char* goodXml = "<root/>";
    EXPECT_EQ(doc_.Parse(goodXml, Len(goodXml)), XML_SUCCESS);
    EXPECT_FALSE(doc_.Error());
    EXPECT_NE(doc_.RootElement(), nullptr);
}

TEST_F(XMLDocumentClearTest_270, ClearAfterCreatingUnlinkedNodes_DoesNotBreakSubsequentOperations_270) {
    // Create nodes but do not link them into the document tree.
    // Observable requirement here: Clear() should be safe and document remains usable.
    XMLNode* e = doc_.NewElement("temp");
    XMLNode* c = doc_.NewComment("comment");
    XMLNode* t = doc_.NewText("text");
    XMLNode* d = doc_.NewDeclaration("xml version=\"1.0\"");

    ASSERT_NE(e, nullptr);
    ASSERT_NE(c, nullptr);
    ASSERT_NE(t, nullptr);
    ASSERT_NE(d, nullptr);

    // Document still has no root since nothing was linked.
    EXPECT_EQ(doc_.RootElement(), nullptr);
    EXPECT_TRUE(doc_.NoChildren());

    doc_.Clear();

    EXPECT_FALSE(doc_.Error());
    EXPECT_EQ(doc_.ErrorID(), XML_SUCCESS);
    EXPECT_EQ(doc_.RootElement(), nullptr);
    EXPECT_TRUE(doc_.NoChildren());

    // Reuse after Clear.
    XMLElement* root = doc_.NewElement("root");
    ASSERT_NE(root, nullptr);
    doc_.InsertEndChild(root);

    ASSERT_NE(doc_.RootElement(), nullptr);
    EXPECT_STREQ(doc_.RootElement()->Name(), "root");

    doc_.Clear();
    EXPECT_EQ(doc_.RootElement(), nullptr);
    EXPECT_TRUE(doc_.NoChildren());
}

}  // namespace tinyxml2
