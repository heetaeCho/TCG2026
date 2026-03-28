#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLDocument tests
class XMLDocumentTest_117 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = new XMLDocument();
    }

    void TearDown() override {
        delete doc;
    }

    XMLDocument* doc;
};

// Test that ShallowEqual always returns false when given nullptr
TEST_F(XMLDocumentTest_117, ShallowEqualWithNullptrReturnsFalse_117) {
    EXPECT_FALSE(doc->ShallowEqual(nullptr));
}

// Test that ShallowEqual returns false when comparing document with itself
TEST_F(XMLDocumentTest_117, ShallowEqualWithSelfReturnsFalse_117) {
    EXPECT_FALSE(doc->ShallowEqual(doc));
}

// Test that ShallowEqual returns false when comparing two different documents
TEST_F(XMLDocumentTest_117, ShallowEqualWithAnotherDocumentReturnsFalse_117) {
    XMLDocument otherDoc;
    EXPECT_FALSE(doc->ShallowEqual(&otherDoc));
}

// Test that ShallowEqual returns false when comparing with a child element node
TEST_F(XMLDocumentTest_117, ShallowEqualWithChildElementReturnsFalse_117) {
    doc->InsertEndChild(doc->NewElement("root"));
    XMLNode* root = doc->FirstChild();
    ASSERT_NE(root, nullptr);
    EXPECT_FALSE(doc->ShallowEqual(root));
}

// Test that ShallowEqual returns false for documents with identical content
TEST_F(XMLDocumentTest_117, ShallowEqualWithIdenticalContentReturnsFalse_117) {
    doc->Parse("<root><child/></root>");
    
    XMLDocument otherDoc;
    otherDoc.Parse("<root><child/></root>");
    
    EXPECT_FALSE(doc->ShallowEqual(&otherDoc));
}

// Test that ShallowEqual returns false for empty documents
TEST_F(XMLDocumentTest_117, ShallowEqualWithEmptyDocumentsReturnsFalse_117) {
    XMLDocument emptyDoc1;
    XMLDocument emptyDoc2;
    EXPECT_FALSE(emptyDoc1.ShallowEqual(&emptyDoc2));
}

// Test that ShallowEqual returns false when comparing with a text node
TEST_F(XMLDocumentTest_117, ShallowEqualWithTextNodeReturnsFalse_117) {
    doc->Parse("<root>text</root>");
    XMLNode* root = doc->FirstChild();
    ASSERT_NE(root, nullptr);
    XMLNode* textNode = root->FirstChild();
    ASSERT_NE(textNode, nullptr);
    EXPECT_FALSE(doc->ShallowEqual(textNode));
}

// Test that ShallowEqual returns false when comparing with a comment node
TEST_F(XMLDocumentTest_117, ShallowEqualWithCommentNodeReturnsFalse_117) {
    doc->Parse("<!-- comment --><root/>");
    XMLNode* comment = doc->FirstChild();
    ASSERT_NE(comment, nullptr);
    EXPECT_FALSE(doc->ShallowEqual(comment));
}

// Test that ShallowEqual returns false when comparing with a declaration node
TEST_F(XMLDocumentTest_117, ShallowEqualWithDeclarationNodeReturnsFalse_117) {
    doc->Parse("<?xml version=\"1.0\"?><root/>");
    XMLNode* declaration = doc->FirstChild();
    ASSERT_NE(declaration, nullptr);
    EXPECT_FALSE(doc->ShallowEqual(declaration));
}

// Test basic document creation and parsing does not affect ShallowEqual result
TEST_F(XMLDocumentTest_117, ShallowEqualAfterParsingComplexDocReturnsFalse_117) {
    const char* xml = 
        "<?xml version=\"1.0\"?>"
        "<root attr=\"value\">"
        "  <child1>text1</child1>"
        "  <child2>text2</child2>"
        "</root>";
    doc->Parse(xml);
    
    XMLDocument otherDoc;
    otherDoc.Parse(xml);
    
    EXPECT_FALSE(doc->ShallowEqual(&otherDoc));
}
