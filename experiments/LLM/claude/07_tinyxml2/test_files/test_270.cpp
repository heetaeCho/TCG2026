#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument::Clear tests
class XMLDocumentClearTest_270 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that Clear on a freshly constructed document works without errors
TEST_F(XMLDocumentClearTest_270, ClearOnEmptyDocument_270) {
    XMLDocument doc;
    doc.Clear();
    EXPECT_FALSE(doc.Error());
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(nullptr, doc.RootElement());
}

// Test that Clear removes all children after parsing XML
TEST_F(XMLDocumentClearTest_270, ClearAfterParsingRemovesAllChildren_270) {
    XMLDocument doc;
    XMLError err = doc.Parse("<root><child1/><child2/><child3/></root>");
    ASSERT_EQ(XML_SUCCESS, err);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_FALSE(doc.NoChildren());

    doc.Clear();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(nullptr, doc.RootElement());
    EXPECT_FALSE(doc.Error());
}

// Test that Clear resets error state
TEST_F(XMLDocumentClearTest_270, ClearResetsErrorState_270) {
    XMLDocument doc;
    // Parse invalid XML to produce an error
    XMLError err = doc.Parse("<root><unclosed>");
    EXPECT_NE(XML_SUCCESS, err);
    EXPECT_TRUE(doc.Error());

    doc.Clear();
    EXPECT_FALSE(doc.Error());
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
}

// Test that Clear allows the document to be reused for new parsing
TEST_F(XMLDocumentClearTest_270, ClearAllowsReuse_270) {
    XMLDocument doc;
    XMLError err = doc.Parse("<first><a/><b/></first>");
    ASSERT_EQ(XML_SUCCESS, err);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("first", doc.RootElement()->Name());

    doc.Clear();

    err = doc.Parse("<second><c/></second>");
    ASSERT_EQ(XML_SUCCESS, err);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("second", doc.RootElement()->Name());
}

// Test that calling Clear multiple times in succession is safe
TEST_F(XMLDocumentClearTest_270, MultipleClearCallsSafe_270) {
    XMLDocument doc;
    doc.Parse("<root>text</root>");
    doc.Clear();
    doc.Clear();
    doc.Clear();
    EXPECT_FALSE(doc.Error());
    EXPECT_TRUE(doc.NoChildren());
}

// Test that Clear handles document with deeply nested elements
TEST_F(XMLDocumentClearTest_270, ClearDeeplyNestedDocument_270) {
    XMLDocument doc;
    const char* xml = "<a><b><c><d><e><f>deep</f></e></d></c></b></a>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(XML_SUCCESS, err);
    ASSERT_NE(nullptr, doc.RootElement());

    doc.Clear();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(nullptr, doc.RootElement());
    EXPECT_FALSE(doc.Error());
}

// Test that Clear handles document with mixed content (elements, text, comments)
TEST_F(XMLDocumentClearTest_270, ClearMixedContentDocument_270) {
    XMLDocument doc;
    const char* xml = "<?xml version=\"1.0\"?><!-- comment --><root>text<child attr=\"val\"/></root>";
    XMLError err = doc.Parse(xml);
    ASSERT_EQ(XML_SUCCESS, err);

    doc.Clear();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(nullptr, doc.RootElement());
    EXPECT_FALSE(doc.Error());
}

// Test that Clear handles unlinked nodes (nodes created but not inserted)
TEST_F(XMLDocumentClearTest_270, ClearWithUnlinkedNodes_270) {
    XMLDocument doc;
    // Create nodes without inserting them into the tree
    XMLElement* elem = doc.NewElement("unlinked");
    XMLComment* comment = doc.NewComment("unlinked comment");
    XMLText* text = doc.NewText("unlinked text");
    (void)elem;
    (void)comment;
    (void)text;

    // Clear should clean up unlinked nodes as well
    doc.Clear();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_FALSE(doc.Error());
}

// Test that Clear on a document with inserted children works correctly
TEST_F(XMLDocumentClearTest_270, ClearAfterManualTreeConstruction_270) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);
    XMLElement* child1 = doc.NewElement("child1");
    root->InsertEndChild(child1);
    XMLElement* child2 = doc.NewElement("child2");
    root->InsertEndChild(child2);
    XMLComment* comment = doc.NewComment("a comment");
    root->InsertEndChild(comment);

    EXPECT_FALSE(doc.NoChildren());
    ASSERT_NE(nullptr, doc.RootElement());

    doc.Clear();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(nullptr, doc.RootElement());
    EXPECT_FALSE(doc.Error());
}

// Test that Clear properly resets BOM state is not necessarily guaranteed,
// but we can check doc is usable after Clear
TEST_F(XMLDocumentClearTest_270, ClearAndReparseWithBOM_270) {
    XMLDocument doc;
    doc.SetBOM(true);
    doc.Parse("<root/>");
    EXPECT_TRUE(doc.HasBOM());

    doc.Clear();
    // After clear, parse new content
    XMLError err = doc.Parse("<newroot/>");
    ASSERT_EQ(XML_SUCCESS, err);
    ASSERT_NE(nullptr, doc.RootElement());
    EXPECT_STREQ("newroot", doc.RootElement()->Name());
}

// Test that Clear handles an empty XML string parse gracefully
TEST_F(XMLDocumentClearTest_270, ClearAfterEmptyParse_270) {
    XMLDocument doc;
    XMLError err = doc.Parse("");
    // Parsing empty string might result in an error
    // Regardless, Clear should work
    doc.Clear();
    EXPECT_FALSE(doc.Error());
    EXPECT_TRUE(doc.NoChildren());
}

// Test that Clear handles a document with many siblings
TEST_F(XMLDocumentClearTest_270, ClearDocumentWithManySiblings_270) {
    XMLDocument doc;
    XMLElement* root = doc.NewElement("root");
    doc.InsertEndChild(root);
    for (int i = 0; i < 100; ++i) {
        XMLElement* child = doc.NewElement("child");
        root->InsertEndChild(child);
    }
    EXPECT_EQ(100, root->ChildElementCount());

    doc.Clear();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_EQ(nullptr, doc.RootElement());
    EXPECT_FALSE(doc.Error());
}

// Test that ErrorID is XML_SUCCESS after Clear following a parse error
TEST_F(XMLDocumentClearTest_270, ErrorIDResetAfterClear_270) {
    XMLDocument doc;
    doc.Parse("<<<invalid>>>");
    EXPECT_TRUE(doc.Error());
    EXPECT_NE(XML_SUCCESS, doc.ErrorID());

    doc.Clear();
    EXPECT_EQ(XML_SUCCESS, doc.ErrorID());
    EXPECT_FALSE(doc.Error());
}

// Test that Clear followed by DeepCopy to another document works
TEST_F(XMLDocumentClearTest_270, ClearThenDeepCopy_270) {
    XMLDocument doc;
    doc.Parse("<root><child/></root>");
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());

    XMLDocument target;
    doc.DeepCopy(&target);
    ASSERT_NE(nullptr, target.RootElement());
    EXPECT_STREQ("root", target.RootElement()->Name());

    doc.Clear();
    EXPECT_TRUE(doc.NoChildren());

    // target should still be intact
    ASSERT_NE(nullptr, target.RootElement());
    EXPECT_STREQ("root", target.RootElement()->Name());
}

// Test that processEntities constructor parameter doesn't affect Clear behavior
TEST_F(XMLDocumentClearTest_270, ClearWithProcessEntitiesFalse_270) {
    XMLDocument doc(false);
    doc.Parse("<root>&amp;</root>");
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());

    doc.Clear();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_FALSE(doc.Error());
}

// Test that Clear works correctly with COLLAPSE_WHITESPACE mode
TEST_F(XMLDocumentClearTest_270, ClearWithCollapseWhitespace_270) {
    XMLDocument doc(true, COLLAPSE_WHITESPACE);
    doc.Parse("<root>  text  with  spaces  </root>");
    ASSERT_EQ(XML_SUCCESS, doc.ErrorID());

    doc.Clear();
    EXPECT_TRUE(doc.NoChildren());
    EXPECT_FALSE(doc.Error());
}
